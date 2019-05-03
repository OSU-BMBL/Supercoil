#ifndef _DYNAMIC_PROGRAMMING_H
#define _DYNAMIC_PROGRAMMING_H

#include "struct.h"
void		DyProgramming_single (const char* fn);
void		DyProgramming (FILE *fw);
int 		searchwhichoperon(int gauge, Operon **nodes);
int 		searchwhichnewoperon(int gauge, Operon **nodes);
float 		ob_function_pathway (int headindex,int rearindex, Operon **node);
float 		ob_function_regulon (int headindex,int rearindex, Operon **node);
extern void	read_operon (FILE* fp);
extern char**   alloc2C(int rr, int cc);
void 		print_results(FILE *fw, DPSOLVE **DPsolve, int circleNum);
int 		searchwhichgene(int gauge, Gene **node);
char 		*check_heg(int gene_order, int dis);
char 		*check_nap(int gene_order, int dis);
char 		*check_palin(int gene_order, int dis);
int     	which_smallest (int stat, int end, double *expression);
int     	which_nap (int start, int end, double *expression);
int     	which_palin (int start, int end, double *expression);
int     	*uniq_integer(int num, int NUM);
static int 	DP_cmpr(const void *a, const void *b);
static void 	sort_DP_list(DPSOLVE **el, int n);
#endif
