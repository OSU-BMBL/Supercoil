/* #ifndef checks whether the given token has been #defined earlier in the file or in an included file; if not, it includes the code between it and the closing #else or, if no #else is present, #endif statement. 
 * #ifndef is often used to make header files idempotent by defining a token once the file has been included and checking that the token was not set at the top of that file.*/

#ifndef _MAIN_H
#define _MAIN_H

#include "struct.h"

/*get_option subroutine prototypes */
void 		get_options (int argc, char* argv[]);

/* read_array subroutine prototypes  */
extern char** 	alloc2c (int rows, int cols);
extern void 	write_imported (const char* stream_nm);
extern void 	get_matrix_size (FILE* fp);
extern void 	read_labels (FILE* fp);
extern void 	read_discrete (FILE* fp);
extern void 	read_continuous (FILE* fp);
extern void 	discretize (const char* stream_nm);
extern void 	read_list (FILE* fp);
extern void 	read_density (FILE* fp);
extern void 	read_ptt (FILE* fp);
extern void	read_heg (FILE* fp);
extern void 	read_NAP (FILE* fp);
extern void 	get_gene_num (FILE* fp);
extern void 	get_operon_num (FILE* fp);
extern void 	get_nap_num (FILE* fp);
extern void 	read_operon (FILE* fp);
extern void	get_pathway_num (FILE* fp);
extern void	get_palindromic_num (FILE* fp);
extern void 	read_pathway (FILE* fp);
extern void 	get_pathway_freq();
extern void 	get_regulon_freq();
extern void 	read_regulon (FILE* fp);
extern void	get_regulon_num (FILE* fp);
extern void	DyProgramming_single (const char* fn);
extern void	DyProgramming (FILE *fw);
extern void 	print_gene_info (const char* fn);
extern void	read_AT_rich (FILE* fp);
extern void	read_palindromic (FILE* fp);

/*make_graph subroutine prototypes */
extern void 	expression_parse (const char* fn, const char* fn1, const char* fn2, const char* fn3, const char* fn4);
/* expand subroutine prototypes */
extern void 	read_and_solve_blocks(FILE *fb, const char *fn);
extern void 	read_expression (FILE* fp);

#endif
