#ifndef _READ_ARRAY_H
#define _READ_ARRAY_H

/************************************************************************/

#include "struct.h"

/***********************************************************************/

/* prototypes  */
continuous 	**alloc2d (int rr, int cc);
discrete 	**alloc2c (int rr, int cc);
char** 		alloc2C(int rr, int cc);
void 		write_imported (const char *stream_nm);
void 		get_matrix_size (FILE *fp);
void 		read_labels (FILE *fp);
void 		read_discrete (FILE *fp);
void 		read_continuous (FILE *fp);
void 		discretize (const char *stream_nm);
discrete 	dis_value(float current, int divided, float *small, int cntl, float *big, int cntu);
void 		read_list (FILE* fp);
void 		read_density (FILE* fp);
continuous 	get_KL (discrete *array, discrete *array_background, int a, int b);
int 		compare_continuous (const void *a, const void *b);
void 		read_ptt (FILE* fp);
void		read_heg (FILE* fp);
void 		get_gene_num (FILE* fp);
void 		get_operon_num (FILE* fp);
void 		get_nap_num (FILE* fp);
int 		which_gi_in_ptt(long int pid);
int 		which_gi_in_microarray(long int pid);
void 		read_operon (FILE* fp);
void 		read_NAP (FILE* fp);
void 		get_pathway_num (FILE* fp);
void 		read_pathway (FILE* fp);
void 		get_regulon_num (FILE* fp);
void 		read_regulon (FILE* fp);
int 		which_synonym_in_ptt(char *synonym);
void 		get_pathway_freq();
void 		get_regulon_freq();
int 		is_appear_in_pathway(Pathway *p, int num, char *atom);
int 		is_appear_in_operon_pathway(int operon_id, int num, int current_id);
int 		is_appear_in_regulon(Regulon *p, int num, char *atom);
int 		is_appear_in_operon_regulon(int operon_id, int num, int current_id);
void     	print_gene_info (const char* fn);
void 		read_expression (FILE* fp);
void 		read_AT_rich (FILE* fp);
void 		get_palindromic_num (FILE* fp);
void 		read_palindromic (FILE* fp);

extern int 	searchwhichgene(int gauge, Gene **node);
extern char     *check_nap(int gene_order, int dis);
extern char     *check_heg(int gene_order, int dis);

/***********************************************************************/

#endif
