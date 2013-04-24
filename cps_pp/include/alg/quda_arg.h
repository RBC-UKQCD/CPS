/*
 * Please do not edit this file.
 * It was generated using PAB's VML system.
 */

#ifndef _QUDA_ARG_H_RPCGEN
#define _QUDA_ARG_H_RPCGEN

#include <config.h>
#include <util/vml/types.h>
#include <util/vml/vml.h>
#include <util/enum.h>
#include <util/defines.h>
CPS_START_NAMESPACE

enum CudaPrecision {
	CUDA_HALF_PRECISION = 0,
	CUDA_SINGLE_PRECISION = 1,
	CUDA_DOUBLE_PRECISION = 2,
};
typedef enum CudaPrecision CudaPrecision;
extern struct vml_enum_map CudaPrecision_map[];

enum CudaReconstructType {
	CUDA_RECONSTRUCT_NO = 0,
	CUDA_RECONSTRUCT_8 = 1,
	CUDA_RECONSTRUCT_12 = 2,
};
typedef enum CudaReconstructType CudaReconstructType;
extern struct vml_enum_map CudaReconstructType_map[];

class VML;
class QudaArg {
public:
	 bool Encode(char *filename,char *instance);
	 bool Decode(char *filename,char *instance);
	 bool Vml(VML *vmls,char *instance);
	CudaPrecision gauge_prec;
	CudaPrecision spinor_prec;
	CudaReconstructType reconstruct;
	CudaPrecision gauge_prec_sloppy;
	CudaPrecision spinor_prec_sloppy;
	CudaReconstructType reconstruct_sloppy;
	Float reliable_delta;
	int max_restart;
	int device;
	   QudaArg (  ) ;
};

/* the xdr functions */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t vml_CudaPrecision (VML *, char *instance, CudaPrecision*);
extern  bool_t vml_CudaReconstructType (VML *, char *instance, CudaReconstructType*);
extern  bool_t vml_QudaArg (VML *, char *instance, QudaArg*);

#else /* K&R C */
extern  bool_t vml_CudaPrecision (VML *, char *instance, CudaPrecision*);
extern  bool_t vml_CudaReconstructType (VML *, char *instance, CudaReconstructType*);
extern  bool_t vml_QudaArg (VML *, char *instance, QudaArg*);

#endif /* K&R C */

#ifdef __cplusplus
}
#endif
CPS_END_NAMESPACE

#endif /* !_QUDA_ARG_H_RPCGEN */
