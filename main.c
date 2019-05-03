/* Author: Qin Ma <maqin@csbl.bmb.uga.edu>, Jan. 22, 2010
 * Usage: This is part of bicluster package. Use, redistribution, modify without limitations
 * show how does the whole program work
 */

/***********************************************************************/

#include "main.h"

/***********************************************************************/

int main(int argc, char* argv[])
{
	/* Start the timer */
	uglyTime(NULL);
	printf("\nSupercoil %.1f: Detect boundaries of supercoil for bacterial genome (compiled "__DATE__" "__TIME__")\n\n", VER);
	rows = cols = 0;

	/* get the program options defined in get_options.c */
	get_options(argc, argv);
	
	printf ("**************************************\nDATA:\n");
	int	infile_id = 1;
	/*get the gene information in PTT file*/
	get_gene_num(po->FT);
	progress("%d: PTT File %s contains %d genes", infile_id, po -> TN, geneNum);
	read_ptt(po->FT);
	infile_id++;
	
	/*get the operon information in opr file*/
	get_operon_num(po->FO);
	progress("%d: OPERON File %s contains %d operons", infile_id, po -> ON, operonNum);
	read_operon(po->FO);
	infile_id++;
	
	/*printf ("%d\t%d\n", operon[54]->gene_id[0], operon[54]->gene_id[operon[54]->gene_num-1]);*/
	/*get the pathway information in .gi file*/
	get_pathway_num(po->FP);
	progress("%d: PATHWAY File %s contains %d pathways", infile_id, po -> PN, pathwayNum);
	read_pathway(po->FP);
	infile_id++;
	
	/*get the regulatory network information in network file*/
	if (po->IS_add_regulon)
	{
		get_regulon_num(po->FR);
		progress("%d: REGULON File %s contains %d regulons", infile_id, po -> RN, regulonNum);
		read_regulon(po->FR);
		infile_id++;
		/*get regulon freq base on current microarray data*/
		get_regulon_freq();
	}
	
	/*get the NAP binding sites information*/
	if (po->IS_add_nap)
	{
		get_nap_num(po->FA);
		progress("%d: NAP File %s contains %d binding sites", infile_id, po -> AN, napNum);
		read_NAP(po->FA);
		infile_id++;
	}
	
	/*get the HEGs information*/
	if (po->IS_add_heg)
	{
		read_heg(po->FE);
		progress("%d: HEG File %s contains %d highly expressed genes", infile_id, po -> EN, hegNum);
		infile_id++;
	}
	
	/*get the palindromic information*/
	if (po->IS_palindromic)
	{
		get_palindromic_num(po->FG);
		read_palindromic(po->FG);
		progress("%d: Palindromic File %s contains %d Palindromic patterns", infile_id, po -> GN, palindromicNum);
		infile_id++;
	}

	/*get the AT-rich information*/
	if (po->IS_AT_rich)
	{
		read_AT_rich (po->FC);
		progress("%d: AT-rich File %s contains %d inter-genetic regions", infile_id, po -> EN, geneNum);
		infile_id++;
	}

	int i;

	/*initial the expression signals*/
	AllocArray(expression_score, geneNum);
	AllocArray(expression_score_1, geneNum);
	AllocArray(expression_num, geneNum);
	for (i=0; i<geneNum; i++)
	{
		expression_score[i] = 0; 
		expression_score_1[i] = 0; 
		expression_num[i] = 0; 
	}
	
	/*get the size of input expression matrix*/
	get_matrix_size(po->FF);	
	progress("%d: Expression file %s contains %d genes by %d conditions", infile_id, po -> FN, rows, cols);
	if (rows < 3 || cols < 3)
	{
		/*neither rows number nor cols number can be too small*/
		errAbort("Not enough genes or conditions to make inference");
	}
	genes_n = alloc2c(rows, LABEL_LEN);
	conds = alloc2c(cols, LABEL_LEN);

	printf ("\n**************************************\nRESULTS:\n");
	/*read dentisy*/
	if (po->IS_density)
		read_density (po->FM);

	/* Read in the gene names and condition names */
	read_labels(po -> FF);	

    	/* Read in the expression data */
	if (po->IS_DISCRETE)
		read_discrete(po -> FF);
	else
	{
		read_continuous(po -> FF);
		
		/* formatting rules */
		discretize(addSuffix(po->FN, ".rules"));
	}
	fclose(po->FF);

	/*get pathway freq base on current microarray data*/
	get_pathway_freq();
	/*get regulon freq base on current microarray data*/
	if(po->IS_add_regulon)
		get_regulon_freq();
	
	/* formatted file */
	write_imported(addSuffix(po->FN, ".chars"));
	print_gene_info(addSuffix(po->FN, ".info"));
	
	/* analysis the expression data and detect boundaries (valleys)*/
	if(po->IS_expression)
		read_expression(po->FD);
	else
		expression_parse(addSuffix(po->FN, ".expression"), addSuffix(po->FN, ".detail"), addSuffix(po->FN, ".valley"), addSuffix(po->FN, ".nap"), addSuffix(po->FN, ".valleyO") );

	/*identify the weight parameter for pathway and expression information dynamically or with experience*/
	if (po->dynamicParameter)
	{
		FILE    *fw = mustOpen(addSuffix(po->FN, ".dynamic"), "w");
        
		for (po->parameter=0.15; po->parameter<=1; po->parameter+=.1)
                	for (po->parameter1=0.15;po->parameter1<=1; po->parameter1+=.1)
                        	for (po->parameter2=5;po->parameter2<=50; po->parameter2+=5)
                                	DyProgramming (fw);
		fclose(fw);
		uglyTime("Final: Dynamic programming results are writen to %s", addSuffix(po->FN, ".dynamic"));
	}
	else
	{
		DyProgramming_single (addSuffix(po->FN, ".dynamic"));
	}
	free(po);
	free (sublist);
	return 0;
}

/***********************************************************************/
