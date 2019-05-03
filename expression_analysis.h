#ifndef _MAKE_GRAPH_H
#define _MAKE_GRAPH_H

#include "struct.h"

/* global data */
int col_width;
Edge **edge_list;
Edge *edge_ptr;

/* from cluster */
extern bits16 	**profile;
extern int 	compare_continuous (const void *a, const void *b);

/* global functions */
extern int 	cluster (FILE *fw, Edge **el, int n);

/* prototypes */
extern char     *check_heg(int gene_order, int dis);
extern void 	verboseDot();
extern char 	*check_nap(int gene_order, int dis);
extern int     	which_smallest (int start, int end, double *expression);
extern int      which_nap (int start, int end, double *expression);
void 		seed_update (const discrete *s);
static int 	str_intersect_r (const discrete *s1, const discrete *s2);
static int 	str_negative_intersect_r (const discrete *s1, const discrete *s2);
void 		seed_deduct (const discrete *s);
void 		expression_parse (const char* fn, const char* fn1, const char* fn2, const char* fn3, const char* fn4);
int 		which_gene_in_ptt(int num);
double 		getDelta(double *expression);
void 		detectValleyG(double *expression_score_input, FILE *fw);
void 		detectValleyO(double *expression_score_input, FILE *fw);
int 		detect_peak(
        const double*   data, /* the data */
        int             data_count, /* row count of data */
        int*            emi_peaks, /* emission peaks will be put here */
        int*            num_emi_peaks, /* number of emission peaks found */
        int             max_emi_peaks, /* maximum number of emission peaks */
        int*            absop_peaks, /* absorption peaks will be put here */
        int*            num_absop_peaks, /* number of absorption peaks found */
        int             max_absop_peaks, /* maximum number of absorption peaks */
        double          delta, /* delta used for distinguishing peaks */
        int             emi_first /* should we search emission peak first of absorption peak first? */
        );
#endif
