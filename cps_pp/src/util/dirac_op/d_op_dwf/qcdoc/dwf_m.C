#include<config.h>
CPS_START_NAMESPACE
//--------------------------------------------------------------------
//  CVS keywords
//
//  $Author: chulwoo $
//  $Date: 2004-07-01 21:26:51 $
//  $Header: /home/chulwoo/CPS/repo/CVS/cps_only/cps_pp/src/util/dirac_op/d_op_dwf/qcdoc/dwf_m.C,v 1.3 2004-07-01 21:26:51 chulwoo Exp $
//  $Id: dwf_m.C,v 1.3 2004-07-01 21:26:51 chulwoo Exp $
//  $Name: not supported by cvs2svn $
//  $Locker:  $
//  $RCSfile: dwf_m.C,v $
//  $Revision: 1.3 $
//  $Source: /home/chulwoo/CPS/repo/CVS/cps_only/cps_pp/src/util/dirac_op/d_op_dwf/qcdoc/dwf_m.C,v $
//  $State: Exp $
//
//--------------------------------------------------------------------
//------------------------------------------------------------------
// dwf_m.C
//
// dwf_m is the fermion matrix.  
// The in, out fields are defined on the checkerboard lattice
//
//------------------------------------------------------------------

CPS_END_NAMESPACE
#include<util/dwf.h>
#include<util/gjp.h>
#include<util/vector.h>
#include<util/verbose.h>
#include<util/error.h>
#include<util/dirac_op.h>
#include "dwf_internal.h"
CPS_START_NAMESPACE


void  dwf_m(Vector *out, 
	    Matrix *gauge_field, 
	    Vector *in, 
	    Float mass, 
	    Dwf *dwf_lib_arg)
{

//------------------------------------------------------------------
// Initializations
//------------------------------------------------------------------
  int f_size = 24 * dwf_lib_arg->vol_4d * dwf_lib_arg->ls / 2;
  Float minus_kappa_sq = -dwf_lib_arg->dwf_kappa * dwf_lib_arg->dwf_kappa;
  Vector *frm_tmp2 = (Vector *) dwf_lib_arg->frm_tmp2;
  
//------------------------------------------------------------------
// Apply Dslash E <- O
//------------------------------------------------------------------
  dwf_dslash(frm_tmp2, gauge_field, in, mass, 1, 0, dwf_lib_arg);

//------------------------------------------------------------------
// Apply Dslash O <- E
//------------------------------------------------------------------
  dwf_dslash(out, gauge_field, frm_tmp2, mass, 0, 0, dwf_lib_arg);
  
//------------------------------------------------------------------
// out = in - dwf_kappa_sq * out
//------------------------------------------------------------------
  //  out->FTimesV1PlusV2(minus_kappa_sq, out, in, f_size); 
  vaxpy3((Float *)out,&minus_kappa_sq,(Float *)out,(Float *)in,f_size/6);
  DiracOp::CGflops+=2*f_size;

}






CPS_END_NAMESPACE