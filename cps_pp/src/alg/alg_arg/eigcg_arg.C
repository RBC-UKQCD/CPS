/*
 * Please do not edit this file.
 * It was generated using PAB's VML system.
 */

#include <alg/eigcg_arg.h>
CPS_START_NAMESPACE
	 bool EigCGArg::Encode(char *filename,char *instance){
		 VML vmls;
		 if ( !vmls.Create(filename,VML_ENCODE)) return false;
		 if ( !Vml(&vmls,instance) ) return false;
		 vmls.Destroy(); return true;
	 }

	 bool EigCGArg::Decode(char *filename,char *instance){
		 VML vmls;
		 if ( !vmls.Create(filename,VML_DECODE)) return false;
		 if ( !Vml(&vmls,instance)) return false;
		 vmls.Destroy(); return true;
	 }
	 bool EigCGArg::Vml(VML *vmls,char *instance){
		 if(!vml_EigCGArg(vmls,instance,this)) return false;
	 return true;
	}


bool_t
vml_EigCGArg (VML *vmls, char *name,EigCGArg *objp)
{
	 vml_class_begin(vmls,"EigCGArg",name);
	int i;
	 if (!vml_int (vmls, "nev", &objp->nev))
		 return FALSE;
	 if (!vml_int (vmls, "m", &objp->m))
		 return FALSE;
	 if (!vml_int (vmls, "max_def_len", &objp->max_def_len))
		 return FALSE;
	 if (!vml_Float (vmls, "max_eig_cut", &objp->max_eig_cut))
		 return FALSE;
	 if (!vml_bool (vmls, "always_restart", &objp->always_restart))
		 return FALSE;
	 if (!vml_int (vmls, "restart_len", &objp->restart_len))
		 return FALSE;
	 if (!vml_vector (vmls, "restart", (char *)objp->restart, 10,
		sizeof (Float), (vmlproc_t) vml_Float))
		 return FALSE;
	 vml_class_end(vmls,"EigCGArg",name);
	return TRUE;
}
CPS_END_NAMESPACE
