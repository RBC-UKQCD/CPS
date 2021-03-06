/*
 * Please do not edit this file.
 * It was generated using PAB's VML system.
 */

#include <alg/ghb_arg.h>
CPS_START_NAMESPACE
	 bool GhbArg::Encode(char *filename,char *instance){
		 VML vmls;
		 if ( !vmls.Create(filename,VML_ENCODE)) return false;
		 if ( !Vml(&vmls,instance) ) return false;
		 vmls.Destroy(); return true;
	 }

	 bool GhbArg::Decode(char *filename,char *instance){
		 VML vmls;
		 if ( !vmls.Create(filename,VML_DECODE)) return false;
		 if ( !Vml(&vmls,instance)) return false;
		 vmls.Destroy(); return true;
	 }
	 bool GhbArg::Vml(VML *vmls,char *instance){
		 if(!vml_GhbArg(vmls,instance,this)) return false;
	 return true;
	}


bool_t
vml_GhbArg (VML *vmls, char *name,GhbArg *objp)
{
	 vml_class_begin(vmls,"GhbArg",name);
	 if (!vml_int (vmls, "num_iter", &objp->num_iter))
		 return FALSE;
	 vml_class_end(vmls,"GhbArg",name);
	return TRUE;
}
CPS_END_NAMESPACE
