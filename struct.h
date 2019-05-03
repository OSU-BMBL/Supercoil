#ifndef _STRUCT_H
#define _STRUCT_H

#ifndef _GNU_SOURCE 
#define _GNU_SOURCE 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>

/***** Useful macros *****/

/* Compatibility of __attribute__ with non-GNU */
#ifndef __GNUC__
#  define __attribute__(x) /* Nothing */
#endif

/* Pretend that C has boolean type */
#define TRUE 1
#define FALSE 0
#define boolean unsigned char
#ifndef __cplusplus
#ifndef bool
#define bool unsigned char
#endif
#endif

#define MAX(a,b)  ((a)>(b)?(a):(b))
#define MIN(a,b)  ((a)<(b)?(a):(b))
#define ABS(x)    ((x)>0?(x):-(x))

/* Variable and array allocation */
#define AllocVar(pt) (pt = xmalloc(sizeof(*pt)))
#define AllocArray(pt, size) (pt = xmalloc(sizeof(*pt) * (size)))
#define ReAllocArray(pt, size) (pt = xrealloc(pt, sizeof(*pt) * (size)))

/* Strings */
/* strcmp: a zero value indicates that both strings are equal.
 * a value greater than zero indicates that the first character that does not match has a greater value in str1 than in str2; 
 * And a value less than zero indicates the opposite.
 */
#define sameString(a, b) (strcmp((a), (b))==0)
/* Returns TRUE if two strings are same */

/* Debugging */
#define internalErr() errAbort("Internal error %s %d", __FILE__, __LINE__)

/* Constants */
#define LABEL_LEN 120
			       
#ifndef NULL
#define NULL 0
#endif

#define MAX_SOLUTION 300

#define lowlimit 10000
/*#define uplimit	 110000*/
			       
/* Two major data types */
typedef float continuous;
typedef short discrete;

/* global data */
continuous 	**arr;
discrete 	**arr_c;
discrete 	*symbols;
char 		**genes_n;
char 		**conds;
char 		**sub_genes;
bool 		*sublist;
int 		rows;
int		cols;
int		geneNum;
int		hegNum;
int		palindromicNum;
int 		operonNum;
int 		napNum;
int		operonInPathwayNum;
int 		pathwayNum;
int		regulonNum;
int		sigma;
int 		TFindex;
int 		sub_genes_row;
continuous 	*density;

/*expression signal*/
double 	*expression_score;
double 	*expression_score_1;
double 	*expression_num;

/*valley detection*/
#define MAX_PEAK    2000


/***** Structures *****/

struct dyStack
/* dynamically allocated stack */
{	
	int 	top;             /* top element index */
  	int 	items[];		   /* data storage */
};

/* edge between two genes */
typedef struct Edge{
	int 	gene_one;
	int 	gene_two;
	int 	score;
} Edge;

typedef struct solve{
        float 	edgevalue;
        int 	precurrentfold;
	int	boundaryNum;
        int 	previoussolve;
        float 	currentpwaysum;
	double	currentExpression;
} solve;

/* structure for gene*/
typedef struct Gene{
	int 		id;
	int		expression_id;
	int		nap_id;
	int		operon_id;
	int		pathway_id[20];
	int		pathway_num;
	int		regulon_id[20];
	int		regulon_num;
	long int 	start;
	long int 	end;
	int 		length;
	char 		strand;
	long int 	pid;
	char 		name[20];
	char 		synonym[10];
	bool		IS_operonEnd;
	bool		IS_in_pathway;
	bool		IS_in_regulon;
	bool		IS_heg;
	double		AT;
	double		ATlocal;
} Gene;	
Gene 	**gene;

/* structure for operon*/
typedef struct Operon{
	int 		id;
	long int 	start;
	long int 	startnew;
	long int 	end;
	long int 	endnew;
	char 		strand;
	int		gene_num;
	long int 	pid[30];
	int		gene_id[30];
	int		pathway_num;
	int		pathway_id[20];
	bool		IS_in_pathway;
	int		regulon_num;
	int		regulon_id[20];
	bool		IS_in_regulon;
	int		solvesum;
	/*solve 		*allSolution[MAX_SOLUTION];*/
	float   	edgevalue[MAX_SOLUTION];
        int     	precurrentfold[MAX_SOLUTION];
        int     	previoussolve[MAX_SOLUTION];
	int		boundaryNum[MAX_SOLUTION];
        float   	currentpwaysum[MAX_SOLUTION];
	double		currentExpression[MAX_SOLUTION];		
} Operon;	
Operon 	**operon;

/* structure for pathway*/
typedef struct Pathway{
	int 	id;
	double	freq;
	int	capacity;
	int	*gene_id[50];
	char	name[200];
	char 	**component;
} Pathway;	
Pathway	 **pathway;

/* structure for regulon*/
typedef struct Regulon{
	int 	id;
	double	freq;
	int	capacity;
	int	*gene_id[50];
	char	name[200];
	char 	**component;
} Regulon;	
Regulon	 **regulon;

/* structure for NAP binding sites*/
typedef struct NAP{
	int	id;
	int	gene_id;
	int	operon_id;
	char	name[20];
	long int position;	
	bool	IS_interGene;
	bool	IS_interOpern;
} NAP;
NAP	**nap;

/* structure for palindromic patterns*/
typedef struct Palindromic{
	int	id;
	long int position;	
	int	gene_id;
	int	operon_id;
	bool	IS_interGene;
	bool	IS_interOpern;
} Palindromic;
Palindromic	**palin;

/* structure for dynamic programming results*/
typedef struct DPSOLVE{
	int	startOperonId;
	int	boundaryNum;
	int	bgene[1000];
	char	**heg;
	char	**heg_s;
	char	**nap;
	char	**nap_s;
	char	**palin;
	char	**palin_s;
	double	expression[1000];
	double	obvalue;
	int	score;
	double	perturbation;
}DPSOLVE;
DPSOLVE	**DPsolve;	

/* holds running options */
typedef struct Prog_options{
	char 	FN[LABEL_LEN];
	char 	TN[LABEL_LEN];
	char 	ON[LABEL_LEN];
	char 	PN[LABEL_LEN];
	char 	AN[LABEL_LEN];
	char 	BN[LABEL_LEN];
	char 	LN[LABEL_LEN];
	char 	MN[LABEL_LEN];
	char 	EN[LABEL_LEN];
	char 	RN[LABEL_LEN];
	char 	DN[LABEL_LEN];
	char 	CN[LABEL_LEN];
	char 	GN[LABEL_LEN];
	bool 	IS_SWITCH;
	bool 	IS_DISCRETE;
	bool 	IS_TFname;
	bool 	IS_cond;
	bool 	IS_list;
	bool 	IS_density;
	bool 	IS_spearman;
	bool	IS_add_regulon;
	bool	IS_add_nap;
	bool	IS_add_heg;
	bool	IS_expression;
	bool	IS_AT_rich;
	bool	IS_palindromic;
	bool	High;
	bool	dynamicParameter;
	int 	COL_WIDTH;
	int 	DIVIDED;
	int	CNT;
	int	uplimit;
	double 	FILTER;
	double 	QUANTILE;
	double	SPEARMAN; 	
	double	parameter; 	
	double	parameter1; 	
	double	parameter2; 	
	double	parameter3; 	
	double	parameter4; 	
	char 	TFname[LABEL_LEN];
	FILE* 	FF;
	FILE* 	FT;
	FILE* 	FO;
	FILE* 	FP;
	FILE* 	FB;
	FILE* 	FL;
	FILE* 	FM;
	FILE* 	FA;
	FILE* 	FE;
	FILE* 	FR;
	FILE* 	FD;
	FILE*	FC;
	FILE*	FG;
} Prog_options;

typedef unsigned short int bits16;
enum {UP=1, DOWN=2, IGNORE=3};

Prog_options* po;
/***** Helper functions *****/

void progress(char *format, ...)
/* Print progress message */
     __attribute__((format(printf, 1, 2)));

void verboseDot();
/* Print "i-am-alive" dot */

void err(char *format, ...)
/* Print error message but do not exit */
     __attribute__((format(printf, 1, 2)));

void errAbort(char *format, ...)
/* Print error message to stderr and exit */
     __attribute__((noreturn, format(printf, 1, 2)));

void uglyTime(char *label, ...);
/* Print label and how long it's been since last call.  Call with 
 * a NULL label to initialize. */

void *xmalloc ( int size );
/* Wrapper for memory allocations */

void *xrealloc ( void* ptr, int size );
/* Wrapper for memory re-allocations */

/* Stack-related operations */
struct dyStack *dsNew(int size);
void dsPrint(struct dyStack *ds);
void dsPush(struct dyStack *ds,int element);

#define dsFree free
/* Release the stack data structure */

#define dsClear(pds) ((pds)->top = -1)
/* Remove all the data in the stack */

#define dsSize(pds) ((pds)->top + 1)
/* Return the size of the stack */

#define dsItem(pds, j) ((pds)->items[j])
/* Return the j-th item in the stack */

bool isInStack(struct dyStack *ds, int element);
int dsIntersect(struct dyStack *ds1, struct dyStack *ds2);

/* File-related operations */
void *addSuffix();
/* Return a string containing headsuffix */

FILE *mustOpen(const char *fileName, char *mode);
/* Open a file or die */

#endif
