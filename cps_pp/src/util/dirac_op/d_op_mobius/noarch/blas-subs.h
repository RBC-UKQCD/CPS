#ifndef BLAS_SUBS_H
#define BLAS_SUBS_H

//#define USE_BLAS
#ifdef USE_BLAS
#if TARGET == BGL
#define cblas_dcopy dcopy
#define cblas_dscal dscal
#define cblas_daxpy daxpy
#include <essl.h>
#else
#include <util/qblas_extend.h>
#endif
#endif

#include<util/time_cps.h>

//#define DEBUG_DWF_DSLASH(msg,a ...) do \
//     printf("[%05d] %s:%d:QMP/%s(): " msg, UniqueID(), \
//                             __FILE__,__LINE__,__FUNCTION__,##a); \
//  while(0);

//#define DEBUG_MOBIUS_DSLASH
//#undef DEBUG_MOBIUS_DSLASH
//moved zmobius.h

#ifndef USE_BLAS
#define MOVE_FLOAT( pa, pb, n )  moveFloat(pa, pb, n)
#define VEC_TIMESEQU_FLOAT(py, fact, n ) vecTimesEquFloatSingle( py, fact, n)
#define AXPY(n, fact, px, py)  fTimesV1PlusV2Single(py, fact, px, py, n)
#else
#define MOVE_FLOAT( pa, pb, n )  cblas_dcopy(n, pb, 1, pa, 1)
#define VEC_TIMESEQU_FLOAT(py, fact, n ) cblas_dscal( n,  fact, py,1 )
#define AXPY(n, fact, px, py)  cblas_daxpy(n, fact, px,1,py,1)
#endif

#endif

