/*
 * Please do not edit this file.
 * It was generated using PAB's VML system.
 */

#ifndef _CG_ARG_H_RPCGEN
#define _CG_ARG_H_RPCGEN

#include <config.h>
#include <util/vml/types.h>
#include <util/vml/vml.h>
#include <util/enum.h>
#include <util/defines.h>
CPS_START_NAMESPACE

class VML;
class CgArg {
public:
	 bool Encode(char *filename,char *instance);
	 bool Decode(char *filename,char *instance);
	 bool Vml(VML *vmls,char *instance);
	Float mass;
	Float epsilon;
	int max_num_iter;
	Float stop_rsd;
	Float true_rsd;
	enum RitzMatType RitzMatOper;
	enum InverterType Inverter;
	int bicgstab_n;
	   CgArg (  ) ;
};

class VML;
class MdwfArg {
public:
	 bool Encode(char *filename,char *instance);
	 bool Decode(char *filename,char *instance);
	 bool Vml(VML *vmls,char *instance);
	struct {
		u_int b5_len;
		Float *b5_val;
	} b5;
	struct {
		u_int c5_len;
		Float *c5_val;
	} c5;
	Float M5;
	CgArg cg_arg;
	struct {
		u_int rsd_vec_len;
		Float *rsd_vec_val;
	} rsd_vec;
	int use_single_precision;
	int use_mdwf_for_dwf;
};

class VML;
class C5State {
public:
	 bool Encode(char *filename,char *instance);
	 bool Decode(char *filename,char *instance);
	 bool Vml(VML *vmls,char *instance);
	Float val;
	int dwf_cg;
};

class VML;
class MdwfTuning {
public:
	 bool Encode(char *filename,char *instance);
	 bool Decode(char *filename,char *instance);
	 bool Vml(VML *vmls,char *instance);
	int stage;
	int ls_min;
	int ls_max;
	int index;
	int opti_index;
	Float opti_time;
	struct {
		u_int mdwf_arg_len;
		MdwfArg *mdwf_arg_val;
	} mdwf_arg;
	struct {
		u_int c5_len;
		C5State *c5_val;
	} c5;
	Float rsd_val;
	Float rsd_time;
	Float rsd_granularity;
	Float c5_range;
	int rc_max;
	int rc_val;
	Float rc_time;
};

class VML;
class MdwfTuningInitArg {
public:
	 bool Encode(char *filename,char *instance);
	 bool Decode(char *filename,char *instance);
	 bool Vml(VML *vmls,char *instance);
	int ls_min;
	int ls_max;
	int rc_max;
	int use_mdwf_for_dwf;
	int use_single_precision;
	Float c5_range;
	Float rsd_granularity;
	char *tuning_fn;
	char *tuning_record_fn;
};

/* the xdr functions */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t vml_CgArg (VML *, char *instance, CgArg*);
extern  bool_t vml_MdwfArg (VML *, char *instance, MdwfArg*);
extern  bool_t vml_C5State (VML *, char *instance, C5State*);
extern  bool_t vml_MdwfTuning (VML *, char *instance, MdwfTuning*);
extern  bool_t vml_MdwfTuningInitArg (VML *, char *instance, MdwfTuningInitArg*);

#else /* K&R C */
extern  bool_t vml_CgArg (VML *, char *instance, CgArg*);
extern  bool_t vml_MdwfArg (VML *, char *instance, MdwfArg*);
extern  bool_t vml_C5State (VML *, char *instance, C5State*);
extern  bool_t vml_MdwfTuning (VML *, char *instance, MdwfTuning*);
extern  bool_t vml_MdwfTuningInitArg (VML *, char *instance, MdwfTuningInitArg*);

#endif /* K&R C */

#ifdef __cplusplus
}
#endif
CPS_END_NAMESPACE

#endif /* !_CG_ARG_H_RPCGEN */
