/*-------------------------------------------------------------------------
 *
 * cost.h
 *	  prototypes for costsize.c and clausesel.c.
 *
 *
 * Portions Copyright (c) 1996-2000, PostgreSQL, Inc
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $Id: cost.h,v 1.34 2000/06/08 22:37:51 momjian Exp $
 *
 *-------------------------------------------------------------------------
 */
#ifndef COST_H
#define COST_H

#include "nodes/relation.h"

/* defaults for costsize.c's Cost parameters */
/* NB: cost-estimation code should use the variables, not these constants! */
#define DEFAULT_EFFECTIVE_CACHE_SIZE  1000.0	/* measured in pages */
#define DEFAULT_RANDOM_PAGE_COST  4.0
#define DEFAULT_CPU_TUPLE_COST	0.01
#define DEFAULT_CPU_INDEX_TUPLE_COST 0.001
#define DEFAULT_CPU_OPERATOR_COST  0.0025

/* defaults for function attributes used for expensive function calculations */
#define BYTE_PCT 100
#define PERBYTE_CPU 0
#define PERCALL_CPU 0
#define OUTIN_RATIO 100


/*
 * prototypes for costsize.c
 *	  routines to compute costs and sizes
 */

/* parameter variables and flags */
extern double effective_cache_size;
extern double random_page_cost;
extern double cpu_tuple_cost;
extern double cpu_index_tuple_cost;
extern double cpu_operator_cost;
extern Cost disable_cost;
extern bool enable_seqscan;
extern bool enable_indexscan;
extern bool enable_tidscan;
extern bool enable_sort;
extern bool enable_nestloop;
extern bool enable_mergejoin;
extern bool enable_hashjoin;

extern void cost_seqscan(Path *path, RelOptInfo *baserel);
extern void cost_index(Path *path, Query *root,
		   RelOptInfo *baserel, IndexOptInfo *index,
		   List *indexQuals, bool is_injoin);
extern void cost_tidscan(Path *path, RelOptInfo *baserel, List *tideval);
extern void cost_sort(Path *path, List *pathkeys, double tuples, int width);
extern void cost_nestloop(Path *path, Path *outer_path, Path *inner_path,
			  List *restrictlist);
extern void cost_mergejoin(Path *path, Path *outer_path, Path *inner_path,
			   List *restrictlist,
			   List *outersortkeys, List *innersortkeys);
extern void cost_hashjoin(Path *path, Path *outer_path, Path *inner_path,
			  List *restrictlist, Selectivity innerdisbursion);
extern Cost cost_qual_eval(List *quals);
extern void set_baserel_size_estimates(Query *root, RelOptInfo *rel);
extern void set_joinrel_size_estimates(Query *root, RelOptInfo *rel,
						   RelOptInfo *outer_rel,
						   RelOptInfo *inner_rel,
						   List *restrictlist);

/*
 * prototypes for clausesel.c
 *	  routines to compute clause selectivities
 */
extern Selectivity restrictlist_selectivity(Query *root,
						 List *restrictinfo_list,
						 int varRelid);
extern Selectivity clauselist_selectivity(Query *root,
					   List *clauses,
					   int varRelid);

#endif	 /* COST_H */
