/* Author:Qin Ma <maqin@csbl.bmb.uga.edu>, Jan. 22, 2010
 * Usage: This is part of bicluster package. Use, redistribution, modify without limitations
 * Process the options for the commandline tool
 */

/***************************************************************************/ 

#include "get_options.h"

/***************************************************************************/ 
static const char USAGE[] = 
"===================================================================\n\
[Usage]\n\
$ ./supercoil -i microarray -j ptt -o operon -p pathway[argument list]\n\
===================================================================\n\
[Input]\n\
-i : input file must be one of two tab-delimited formats\n\
  A) continuous data (default, use pre-set discretization (see -q and -r))\n\
     -------------------------------------\n\
     o        cond1    cond2    cond3\n\
     gene1      2.4      3.5     -2.4\n\
     gene2     -2.1      0.0      1.2\n\
     -------------------------------------\n\
  B) discrete data with arbitray classes (turn on -d)\n\
     use '0' for missing or insignificant data\n\
     -------------------------------------\n\
     o        cond1    cond2    cond3\n\
     gene1        1        2        2\n\
     gene2       -1        2        0\n\
     -------------------------------------\n\
-j : the standard ptt file\n\
-o : operon file from DOOR\n\
     -------------------------------------\n\
     1: 16127995 16127996 16127997 16127998\n\
     2: 16127999\n\
     3: 16128000\n\
     -------------------------------------\n\
-p : pathway file (pathway-gene mapping)\n\
     -------------------------------------\n\
     Phage packaging machinery       16129112 16129114\n\
     Phage tail fiber proteins       16129333 16129334 16129505 16128544\n\
     -------------------------------------\n\
-a : NAP binding sites information (optional)\n\
     -------------------------------------\n\
     fis     151\n\
     ihf     5219\n\
     fis     29361\n\
     -------------------------------------\n\
-e : HEG file (optional)\n\
     the standard ptt file format\n\
-A : AT-rich file (optional)\n\
     -------------------------------------\n\
     0       0.62    0.9\n\
     1       0.506172839506173       0.7\n\
     -------------------------------------\n\
-q : use quantile discretization for continuous data\n\
     default: 0.25 (see details in Method section in paper)\n\
-r : the number of ranks as which we treat the up(down)-regulated value\n\
     when discretization\n\
     default: 1\n\
-n : the proportion of pathway frequency base on current folding\n\
     default: .7\n\
-g : the proportion of pathway density base on current folding\n\
     default: .9\n\
-t : the proportion of expression level base on current folding\n\
     default: 60\n\
-c : the cutoff of spearman correlation coefficient\n\
     default: 0.6. [.4,.8)\n\
-S : the cutoff of cnt\n\
     default: 6\n\
-d : discrete data, where user should send their processed data\n\
     to different value classes, see above\n\
-m : the flag to descretize the continuous value considering kernel density estimation\n\
-M : the flag to identify the weight parameters for two kind of information: pathway and expression\n\
     default: FALSE\n\
===================================================================\n";

static void init_options ()
{
	/* default parameters */
	/* strcpy: Copies the C string pointed by source into the array pointed by destination, including the terminating null character.
	 * To avoid overflows, the size of the array pointed by destination shall be long enough to contain the same C string as source (including the terminating null character), and should not overlap in memory with source
	 */
	strcpy(po->FN, " ");
	strcpy(po->TN, " ");
	/*strcpy(po->BN, " ");*/
	strcpy(po->LN, " ");
	strcpy(po->ON, " ");
	strcpy(po->PN, " ");
	strcpy(po->AN, " ");
	strcpy(po->EN, " ");
	strcpy(po->GN, " ");
	strcpy(po->TFname, " ");
	po->IS_DISCRETE = FALSE;
	po->IS_TFname = FALSE;
	po->COL_WIDTH = 5;
	po->DIVIDED = 1;
	/*.06 is set as default for its best performance for ecoli and yeast functional analysis*/
	po->QUANTILE = .25;
	po->SPEARMAN = .6;
	po->FF = NULL;
	po->FB = NULL;
	po->FT = NULL;
	po->FO = NULL;
	po->FP = NULL;
	po->FA = NULL;
	po->FE = NULL;
	po->FG = NULL;
	po->FILTER = 1;
	po->IS_SWITCH = FALSE;
	po->CNT = 6;
	po->IS_list = FALSE;
	po->IS_density = FALSE;
	po->IS_spearman = FALSE;
	po->IS_add_nap = FALSE;
	po->IS_add_heg = FALSE;
	po->IS_add_regulon = FALSE;
	po->IS_AT_rich = FALSE;
	po->IS_palindromic = FALSE;
	po->High = FALSE;
	po->dynamicParameter =FALSE;
	po->parameter = 1;
	po->parameter1 = 1;
	po->parameter2 = 1;
	po->parameter3 = 0;
	po->parameter4 = 0;
	po->uplimit = 110000;
}

/*argc is a count of the arguments supplied to the program and argc[] is an array of pointers to the strings which are those arguments-its type is array of pointer to char
 */
void get_options (int argc, char* argv[])
{
	int op;
	bool is_valid = TRUE;

	/*set memory for the point which is decleared in struct.h*/
	AllocVar(po);
	/*Initialize the point*/
	init_options();
	
	/*The getopt function gets the next option argument from the argument list specified by the argv and argc arguments. 
	 *Normally these values come directly from the arguments received by main
	 */
	/*An option character in this string can be followed by a colon (:) to indicate that it takes a required argument.
	 *If an option character is followed by two colons (::), its argument is optional
	 *if an option character is followed by no colons, it does not need argument
	 */
	while ((op = getopt(argc, argv, "i:j:o:p:a:e:R:D:A:P:q:r:dsf:k:c:v:S:l:m:n:g:N:G:t:U:hHM")) >0)
	{
		switch (op)
		{
			/*optarg is set by getopt to point at the value of the option argument, for those options that accept arguments*/
			case 'i': strcpy(po->FN, optarg); break;
			case 'j': strcpy(po->TN, optarg); break;
			case 'o': strcpy(po->ON, optarg); break;
			case 'p': strcpy(po->PN, optarg); break;
	
		        /*case 'b': strcpy(po->BN, optarg); break;*/
			case 'a': strcpy(po->AN, optarg); po->IS_add_nap =TRUE; break;
			case 'e': strcpy(po->EN, optarg); po->IS_add_heg =TRUE; break;
			case 'R': strcpy(po->RN, optarg); po->IS_add_regulon = TRUE; break;
			case 'D': strcpy(po->DN, optarg); po->IS_expression = TRUE; break;
			case 'A': strcpy(po->CN, optarg); po->IS_AT_rich = TRUE; break;
			case 'P': strcpy(po->GN, optarg); po->IS_palindromic = TRUE; break;
			/*atof can convert string to double*/
			case 'q': po->QUANTILE = atof(optarg); break;
			/*atoi can convert string to integer*/
			case 'r': po->DIVIDED = atoi(optarg); break;
			case 'd': po->IS_DISCRETE = TRUE; break;
			case 's': po->IS_SWITCH = TRUE; break;
			case 'f': po->FILTER = atof(optarg); break; 
			case 'k': po->COL_WIDTH = atoi(optarg); break;
			case 'c': po->SPEARMAN = atof(optarg); break;
			/*puts writes the C string pointed by str to stdout and appends a newline character ('\n')*/
			/*exit(0) causes the program to exit with a successful termination
			 *break is normally used to jump to the end of the current block of code
			 *exit is normally used to shut down the current process
			 */
			case 'S': po->CNT = atoi(optarg); break; 
			case 'l': strcpy(po->LN, optarg); po->IS_list =TRUE; break;
			case 'm': strcpy(po->MN, optarg); po->IS_density =TRUE; break;
			case 'n': po->parameter = atof(optarg); break;
			case 'g': po->parameter1 = atof(optarg); break;
			case 'N': po->parameter3 = atof(optarg); break;
			case 'G': po->parameter4 = atof(optarg); break;
			case 't': po->parameter2 = atof(optarg); break;
			case 'U': po->uplimit = atoi(optarg); break;
			case 'h': puts(USAGE); exit(0); 
			case 'H': po->High = TRUE; break; 
			case 'M': po->dynamicParameter = TRUE; break; 
			/*if expression does not match any constant-expression, control is transferred to the statement(s) that follow the optional default label*/
			default : is_valid = FALSE;
		}
	}
	/* basic sanity check */
        if (is_valid && po->FN[0] == ' ') 
	{
		/*errAbort("You must specify input file (-i)");*/
		puts(USAGE); 
		exit(0);
	}
	if (is_valid)
		po->FF = mustOpen(po->FN, "r");
	if (is_valid)
		po->FT = mustOpen(po->TN, "r");
	if (is_valid)
		po->FO = mustOpen(po->ON, "r");
	if (is_valid)
		po->FP = mustOpen(po->PN, "r");
	if (po->IS_add_nap)
		po->FA = mustOpen(po->AN, "r");
	if (po->IS_add_heg)
		po->FE = mustOpen(po->EN, "r");
	if (po->IS_add_regulon)
		po->FR = mustOpen(po->RN, "r");
	if (po->IS_expression)
		po->FD = mustOpen(po->DN, "r");
	if (po->IS_AT_rich)
		po->FC = mustOpen(po->CN, "r");
	if (po->IS_palindromic)
		po->FG = mustOpen(po->GN, "r");
	if (po->IS_SWITCH) 
	{	
		po->IS_DISCRETE = TRUE; 
		po->FB = mustOpen(po->BN, "r");
	}
	if (po->IS_list)
		po->FL = mustOpen(po->LN, "r");
	if (po->IS_density)
		po->FM = mustOpen(po->MN, "r");
	
	/* option value range check */
	if ((po->QUANTILE >.5) || (po->QUANTILE <= 0))
	{
		err("-q quantile discretization should be (0,.5]");
		is_valid = FALSE;
	}
	if (po->IS_SWITCH) 
	{	
		po->IS_DISCRETE = TRUE; 
		po->FB = mustOpen(po->BN, "r");
	}
	if (po->IS_list)
		po->FL = mustOpen(po->LN, "r");
	if (po->IS_density)
		po->FM = mustOpen(po->MN, "r");
	
	/* option value range check */
	if ((po->QUANTILE >.5) || (po->QUANTILE <= 0))
	{
		err("-q quantile discretization should be (0,.5]");
		is_valid = FALSE;
	}
	if (!is_valid)
		errAbort("Type -h to view possible options");

}
/***************************************************************************/ 

