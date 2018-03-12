#ifndef CONSTANTS_H_GUARD
#define CONSTANTS_H_GUARD

#include "glbopts.h"


#ifdef __cplusplus
extern "C" {
#endif

    /* SCS VERSION NUMBER ----------------------------------------------    */
    /* string literals automatically null-terminated */
    /**
     * Version of SCS
     */
#define SCS_VERSION                                                            \
    ("1.2.6-KUL-SuperMann") 


    /* SCS returns one of the following integers:                           */
#define SCS_INFEASIBLE_INACCURATE (-7)
#define SCS_UNBOUNDED_INACCURATE (-6)
#define SCS_SIGINT (-5)
#define SCS_FAILED (-4)
#define SCS_INDETERMINATE (-3)
#define SCS_INFEASIBLE (-2) /* primal infeasible, dual unbounded   */
#define SCS_UNBOUNDED (-1)  /* primal unbounded, dual infeasible   */
#define SCS_UNFINISHED (0)  /* never returned, used as placeholder */
#define SCS_SOLVED (1)
#define SCS_SOLVED_INACCURATE (2)

    /* DEFAULT SOLVER PARAMETERS AND SETTINGS --------------------------    */
#define MAX_ITERS_DEFAULT (2500)
#define EPS_DEFAULT (1E-3)
#define ALPHA_DEFAULT (1.5)
#define RHO_X_DEFAULT (0.001)
#define SCALE_DEFAULT (1.0)
#define CG_RATE_DEFAULT (2.0)
#define VERBOSE_DEFAULT (1)
#define NORMALIZE_DEFAULT (1)
#define DO_RECORD_PROGRESS_DEFAULT (0)
#define WARM_START_DEFAULT (0)

    /* Parameters for Superscs*/
#define DO_SUPERSCS_DEFAULT (1)
#define K0_DEFAULT (0)
#define K1_DEFAULT (1)
#define K2_DEFAULT (1)    
#define NOMINAL_DEFAULT (1)
#define C_BL_DEFAULT (0.999)
#define C1_DEFAULT (1.0-1E-4)
#define SSE_DEFAULT (1.0-1E-3) 

    /* Line-search defaults */
#define LS_DEFAULT  (10)
#define BETA_DEFAULT (0.5)
#define SIGMA_DEFAULT (1E-2)

    /* Direction Defaults */
#define DIRECTION_DEFAULT (restarted_broyden)
#define TRULE_DEFAULT (3)
#define DELTA_DEFAULT (0.5)
#define THETABAR_DEFAULT (1E-1)
#define ALPHAC_DEFAULT (1E-2) 
#define MEMORY_DEFAULT (10)
#define SC_INIT_DEFAULT (0)
#define BROYDEN_ISCALE_DEFAULT (1)
#define OVERRIDE_STREAMS_DEFAULT (0)
    
    /* Other */
#define OUT_STREAM_DEFAULT (stdout)
#define PMAXITER_DEFAULT (-1)
#ifdef __cplusplus
}
#endif
#endif
