#include<stdio.h>
#include<config.h>
#include<math.h>
CPS_START_NAMESPACE
/*!\file
  \brief  Implementation of some Fasqtad class methods.

*/
//--------------------------------------------------------------------
//
//
//--------------------------------------------------------------------
//------------------------------------------------------------------
//
// f_asqtad.C
//
// Fasqtad is derived from FstagTypes and is relevant to
// Improved staggered (Asqtad) fermions
//
//------------------------------------------------------------------

CPS_END_NAMESPACE
#include <util/lattice.h>
#include <util/verbose.h>
#include <util/dirac_op.h>
#include <util/asqtad.h>
#include <util/vector.h>
#include <util/smalloc.h>
#include <util/pt.h>
#include <util/time_cps.h>
#include <util/gjp.h>
CPS_START_NAMESPACE




//int Fasqtad::ForceFlops=0;
//------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------
Fasqtad::Fasqtad()
	: Fsmear(3)
{
  cname = "Fasqtad";
  char *fname = "Fasqtad()";
  VRB.Func(cname,fname);

  asqtad_dirac_init(this);

}


//------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------
Fasqtad::~Fasqtad()
{
  char *fname = "~Fasqtad()";
  VRB.Func(cname,fname);
  asqtad_destroy_dirac_buf();
}


//------------------------------------------------------------------
// Returns the type of fermion class.
//------------------------------------------------------------------
FclassType Fasqtad::Fclass() const{
  return F_CLASS_ASQTAD;
}



//------------------------------------------------------------------
// int FmatEvlInv(Vector *f_out, Vector *f_in, 
//                CgArg *cg_arg, 
//                Float *true_res,
//		  CnvFrmType cnv_frm = CNV_FRM_YES):
// It calculates f_out where A * f_out = f_in and
// A is the fermion matrix that appears in the HMC 
// evolution ([Dirac^dag Dirac]). The inversion is done
// with the conjugate gradient. cg_arg is the structure
// that contains all the control parameters, f_in is the
// fermion field source vector, f_out should be set to be
// the initial guess and on return is the solution.
// f_in and f_out are defined on a checkerboard.
// If true_res !=0 the value of the true residual is returned
// in true_res.
// *true_res = |src - MatPcDagMatPc * sol| / |src|
// The function returns the total number of CG iterations.
//------------------------------------------------------------------
int Fasqtad::FmatEvlInv(Vector *f_out, Vector *f_in, 
		      CgArg *cg_arg, 
		      Float *true_res,
		      CnvFrmType cnv_frm)
{
  int iter;
  char *fname = "FmatEvlInv(CgArg*,V*,V*,F*,CnvFrmType)";
  VRB.Func(cname,fname);

  DiracOpAsqtad asqtad(*this, f_out, f_in, cg_arg, cnv_frm);
  iter = asqtad.InvCg(&(cg_arg->true_rsd));
  if (true_res) *true_res = cg_arg ->true_rsd;

  asqtad.Dslash(f_tmp, f_out, CHKB_EVEN, DAG_NO);

  // Return the number of iterations
  return iter;
}




//------------------------------------------------------------------
// int FmatEvlMInv(Vector **f_out, Vector *f_in, 
//                Float shift[], int Nshift, 
//                CgArg *cg_arg, Float *true_res,
//		  CnvFrmType cnv_frm = CNV_FRM_YES):
// It calculates f_out where (A + shift)* f_out = f_in and
// A is the fermion matrix that appears in the HMC 
// evolution ([Dirac^dag Dirac]) and shift is a real shift of the 
// fermion matrix, with Nshift such shifts. The inversion is done 
// with the multishift conjugate gradient. cg_arg is the structure
// that contains all the control parameters, f_in is the
// fermion field source vector, f_out is the array of solution 
// vectors, f_in and f_out are defined on a checkerboard.
// The function returns the total number of CG iterations.
//------------------------------------------------------------------
int Fasqtad::FmatEvlMInv(Vector **f_out, Vector *f_in, Float *shift, 
			 int Nshift, int isz, CgArg **cg_arg,
			 CnvFrmType cnv_frm, MultiShiftSolveType type, 
			 Float *alpha, Vector **f_out_d)
{
  char *fname = "FmatMInv(V**, V*, .....)";
  VRB.Func(cname,fname);

  Float dot = f_in -> NormSqGlbSum4D(e_vsize);

  Float *RsdCG = new Float[Nshift];
  for (int s=0; s<Nshift; s++)
    RsdCG[s] = cg_arg[s]->stop_rsd;

  Float trueMass;
  massRenormalise(&(cg_arg[0]->mass), &trueMass, Nshift, shift, RENORM_FORWARDS);

  DiracOpAsqtad asqtad(*this, f_out[0], f_in, cg_arg[0], cnv_frm);
  int iter = asqtad.MInvCG(f_out,f_in,dot,shift,Nshift,isz,RsdCG,type,alpha);
  
  if (type == MULTI && f_out_d != 0)
    for (int s=0; s<Nshift; s++)
      asqtad.Dslash(f_out_d[s], f_out[s], CHKB_EVEN, DAG_NO);
  for (int s=0; s<Nshift; s++) cg_arg[s]->true_rsd = RsdCG[s];

  massRenormalise(&(cg_arg[0]->mass), &trueMass, Nshift, shift, RENORM_BACKWARDS);

  delete[] RsdCG;
  return iter;

}

//------------------------------------------------------------------
// Lattice class api to the chronological inverter
//------------------------------------------------------------------
void Fasqtad::FminResExt(Vector *sol, Vector *source, Vector **sol_old, 
			 Vector **vm, int degree, CgArg *cg_arg, CnvFrmType cnv_frm)
{

  char *fname = "FminResExt(V*, V*, V**, V**, int, CgArg *, CnvFrmType)";
  VRB.Func(cname,fname);
  
  DiracOpAsqtad asqtad(*this, sol, source, cg_arg, cnv_frm);
  asqtad.MinResExt(sol,source,sol_old,vm,degree);
  
}

//------------------------------------------------------------------
// int FmatInv(Vector *f_out, Vector *f_in, 
//             CgArg *cg_arg, 
//             Float *true_res,
//             CnvFrmType cnv_frm = CNV_FRM_YES,
//             PreserveType prs_f_in = PRESERVE_YES):
// It calculates f_out where A * f_out = f_in and
// A is the fermion matrix (Dirac operator). The inversion
// is done with the conjugate gradient. cg_arg is the 
// structure that contains all the control parameters, f_in 
// is the fermion field source vector, f_out should be set 
// to be the initial guess and on return is the solution.
// f_in and f_out are defined on the whole lattice.
// If true_res !=0 the value of the true residual is returned
// in true_res.
// *true_res = |src - MatPcDagMatPc * sol| / |src|
// cnv_frm is used to specify if f_in should be converted 
// from canonical to fermion order and f_out from fermion 
// to canonical. 
// prs_f_in is used to specify if the source
// f_in should be preserved or not. If not the memory usage
// is less by half the size of a fermion vector.
// The function returns the total number of CG iterations.
//------------------------------------------------------------------
int Fasqtad::FmatInv(Vector *f_out, Vector *f_in, 
		   CgArg *cg_arg, 
		   Float *true_res,
		   CnvFrmType cnv_frm,
		   PreserveType prs_f_in)
{

  char *fname = "FmatInv(CgArg*,V*,V*,F*,CnvFrmType)";
  VRB.Func(cname,fname);

  DiracOpAsqtad stag(*this, f_out, f_in, cg_arg, cnv_frm);
  
  return stag.MatInv(true_res, prs_f_in);
  
}



//------------------------------------------------------------------
// int FeigSolv(Vector **f_eigenv, Float *lambda, int valid_eig[],
//              EigArg *eig_arg, 
//              CnvFrmType cnv_frm = CNV_FRM_YES):
//------------------------------------------------------------------
int Fasqtad::FeigSolv(Vector **f_eigenv, Float lambda[], 
		    Float chirality[], int valid_eig[],
		    Float **hsum,
		    EigArg *eig_arg, 
		    CnvFrmType cnv_frm)
{
  int iter;
  char *fname = "FeigSolv(EigArg*,V*,F*,CnvFrmType)";
  VRB.Func(cname,fname);
  CgArg cg_arg;
  cg_arg.mass = eig_arg -> mass;
  cg_arg.RitzMatOper = eig_arg->RitzMatOper;
  int N_eig = eig_arg->N_eig;

  // Call constructor and solve for eigenvectors.
  // Use null pointers to fake out constructor.
  Vector *v1 = (Vector *)0;
  Vector *v2 = (Vector *)0;

  DiracOpAsqtad stag(*this, v1, v2, &cg_arg, CNV_FRM_NO);
  
  iter = stag.RitzEig(f_eigenv, lambda, valid_eig, eig_arg);
  
  // Modified for anisotropic lattices
  Float factor = GJP.XiV()/GJP.XiBare();
  // Chirality is trivial
  for(int i=0; i < N_eig; ++i) {
    chirality[i] = 1.0;
    lambda[i] *= factor;
  }
  // End modification

#if 0
  // !!! THIS DOES NOT WORK YET !!!
  // Slice-sum the eigenvector density to make a 1D vector
  if (eig_arg->print_hsum)
    for(i=0; i < N_eig; ++i)
      slice_sum_sq(hsum[i], f_eigenv[i], eig_arg->hsum_dir);
#endif

  // Return the number of iterations
  return iter;
}

//------------------------------------------------------------------
// Solve  A * f_eigenv = lambda * f_eigenv where
// A is the fermion matrix (Dirac operator). The solution
// is done with the Lanczos algorithm. eig_arg is the
// structure that contains all the control parameters, f_eigenv
// is the fermion field eigenvectors, lambda are the
// returned eigenvalues.
// f_eigenv is defined on the whole lattice.
//------------------------------------------------------------------
int Fasqtad::FeigSolv(Vector **f_eigenv, Float *lambda,
                    LanczosArg *eig_arg,
                    CnvFrmType cnv_frm)
{
  int iter;
  char *fname = "FeigSolv(V*,F*,LanczosArg*,CnvFrmType)";
  VRB.Func(cname,fname);
  CgArg cg_arg;
  cg_arg.mass = eig_arg->mass;
  //cg_arg.RitzMatOper = eig_arg->RitzMatOper;
  //int N_eig = eig_arg->N_eig;
  int nk = eig_arg->nk_lanczos_vectors;
  int np = eig_arg->np_lanczos_vectors;
  int maxiters = eig_arg->maxiters;
  Float stopres = eig_arg->stop_residual;
  MatrixPolynomialArg* cheby_arg = &eig_arg->matpoly_arg;
//(MatrixPolynomialArg*)eig_arg->matpoly_arg;

  if(cnv_frm == CNV_FRM_YES) // convert only nk, not (nk+np)
    for(int i=0; i < nk; ++i)
      Fconvert(f_eigenv[i], STAG, StrOrd());

  // Call constructor and solve for eigenvectors.
  // Use null pointers to fake out constructor.
  Vector *v1 = (Vector *)0;
  Vector *v2 = (Vector *)0;
  DiracOpAsqtad stag(*this, v1, v2, &cg_arg, CNV_FRM_NO);

  iter = stag.ImpResLanczos(f_eigenv, lambda,  eig_arg);

  if(cnv_frm == CNV_FRM_YES) for(int i=0; i < nk; ++i) // convert only nk, not (nk+np)
                               Fconvert(f_eigenv[i], CANONICAL, StrOrd());

  return iter;
}

//------------------------------------------------------------------
// SetPhi(Vector *phi, Vector *frm_e, Vector *frm_o, Float mass, 
//        DagType dag):
// It sets the pseudofermion field phi from frm_e, frm_o.
// Modified - now returns the (trivial) value of the action
//------------------------------------------------------------------
Float Fasqtad::SetPhi(Vector *phi, Vector *frm_e, Vector *frm_o, 
		      Float mass, DagType dag){
  // dag is ignored for staggered
  char *fname = "SetPhi(V*,V*,V*,F)";
  VRB.Func(cname,fname);
  CgArg cg_arg;
  cg_arg.mass = mass;
//  static int called=0;

  DiracOpAsqtad stag(*this, phi, frm_o, &cg_arg, CNV_FRM_NO);
  stag.Dslash(phi, frm_o, CHKB_ODD, DAG_NO);

  // Modified for anisotropic lattices
  //------------------------------------------------------------------
  fTimesV1MinusV2((IFloat *)phi, 2.*mass*GJP.XiBare()/GJP.XiV(), 
	(IFloat *)frm_e, (IFloat *)phi, e_vsize);

  return 0.0;
}



//------------------------------------------------------------------
// Float BhamiltonNode(Vector *boson, Float mass):
// The boson Hamiltonian of the node sublattice.
//------------------------------------------------------------------
Float Fasqtad::BhamiltonNode(Vector *boson, Float mass){
  char *fname = "BhamiltonNode(V*,F)";
  VRB.Func(cname,fname);
  CgArg cg_arg;
  cg_arg.mass = mass;

  DiracOpAsqtad stag(*this, f_tmp, boson, &cg_arg, CNV_FRM_NO);
  Float ham;
  stag.MatPcDagMatPc(f_tmp, boson, &ham);

  return ham;
}


//!< Routine which allows bosonic asqtad formulation.  Not sure why
//!< anyone would want this, but included for completeness.
void Fasqtad::BforceVector(Vector *in, CgArg *cg_arg) {

  int iter;
  char *fname = "BforceVector(V*)";
  VRB.Func(cname,fname);

  DiracOpAsqtad asqtad(*this, f_tmp, in, cg_arg, CNV_FRM_NO);
  asqtad.Dslash(f_tmp, in, CHKB_EVEN, DAG_NO);

}


//------------------------------------------------------------------
// Fdslash(Vector *f_out, Vector *f_in, CgArg *cg_arg, CnvFrmType cnv_frm,
//                    int dir_flag) :
// Fdslash is the derivative part of the fermion matrix. 
// Fdslash calculates both odd-->even and even-->odd sites.
// dir_flag is flag which takes value 0 when all direction contribute to D,
// 1 - when only the special anisotropic direction contributes to D,
// 2 - when all  except the special anisotropic direction. 
//------------------------------------------------------------------
void Fasqtad::Fdslash(Vector *f_out, Vector *f_in, CgArg *cg_arg, 
		    CnvFrmType cnv_frm, int dir_flag)
{
  int offset;
  char *fname = "Fdslash(V*,V*,CgArg*,CnvFrmType,int)";
  VRB.Func(cname,fname);
  
  DiracOpAsqtad stag(*this, f_out, f_in, cg_arg, cnv_frm);
  offset = GJP.VolNodeSites() * FsiteSize() / (2 * VECT_LEN);
  
  stag.Dslash(f_out, f_in+offset, CHKB_ODD, DAG_NO, dir_flag);
  stag.Dslash(f_out+offset, f_in, CHKB_EVEN, DAG_NO, dir_flag);

}


static int Rotate (int mu, int i){
	int mu_p = (mu+i)%4;
	if( mu >= 4)
		mu_p += 4;
//	printf("Rotate(%d, %d)=%d)\n",mu,i,mu_p);
	return mu_p;
}
static int NotParallel( int mu, int nu){
	int dif = mu-nu;
	if (dif==0 ||dif==-4||dif==4)return 0;
	else return 1;
}

enum {NUM_DIR=8,POS_DIR=4};

void Fasqtad::Smear(){
  char *fname = "Smear()";
  VRB.Func(cname,fname);
  if (smeared) return;

//--------------------------------------------------------------------
// c1 -> one link; c2 -> 3-link; c3 -> 3-link staple; c5 -> 5-link staple;
// c7 -> 7-link staple; c6 -> 5-link "straight" staple
//--------------------------------------------------------------------

  IFloat c1 = GJP.KS_coeff();
  IFloat c2 = GJP.Naik_coeff();
  IFloat c3 = -GJP.staple3_coeff();
  IFloat c5 = GJP.staple5_coeff();
  IFloat c7 = -GJP.staple7_coeff();
  IFloat c6 = GJP.Lepage_coeff();

  int i, j; 
  int N = 4;
  int vol = GJP.VolNodeSites();
  if (vol>2000) N = 2;
  ParTransAsqtad pt(*this);
  Matrix *result[NUM_DIR];
  Matrix *Unit;
  Matrix *P3[NUM_DIR];
  Matrix *P3mu[NUM_DIR];
  Matrix *P5[NUM_DIR];
  Matrix *P5mu[NUM_DIR];
  Matrix *P7[NUM_DIR];
  Matrix *P7mu[NUM_DIR];
  Matrix *P6[NUM_DIR];
  Matrix *P6mu[NUM_DIR];
  Matrix *Pmumu[NUM_DIR];
  Matrix *Pmumumu[NUM_DIR];
  VRB.Flow(cname,fname,"vol=%d\n",vol);
  Unit = (Matrix *)fmalloc(cname,fname,"Unit",sizeof(Matrix)*vol);
  for(i = 0;i<N;i++)
    Pmumumu[i] = P7mu[i] = (Matrix *)fmalloc(cname,fname,"Pmumumu[i]",sizeof(Matrix)*vol);
  for(i = 0;i<N;i++)
    Pmumu[i] = P7[i] = (Matrix *)fmalloc(cname,fname,"Pmumu[i]",sizeof(Matrix)*vol);
  for(i = 0;i<N;i++)
    P6mu[i] = P5mu[i] = (Matrix *)fmalloc(cname,fname,"P6mu[i]",sizeof(Matrix)*vol);
  for(i = 0;i<N;i++)
    P6[i] = P5[i] = (Matrix *)fmalloc(cname,fname,"P6[i]",sizeof(Matrix)*vol);
  for(i = 0;i<N;i++)
    P3mu[i] = (Matrix *)fmalloc(cname,fname,"P3mu[i]",sizeof(Matrix)*vol);
  for(i = 0;i<N;i++)
    P3[i] = (Matrix *)fmalloc(cname,fname,"P3[i]",sizeof(Matrix)*vol);
  for(j = 0;j<POS_DIR;j++){
     result[j] = fields[0] + vol*j;

     VRB.Flow(cname,fname,"result[%d]=%p\n",j,result[j]);
  }


  for(j = 0;j<vol;j++) Unit[j] = c1;
  for(j = 0;j<POS_DIR;j++)
     for(int k = 0;k<vol;k++) (result[j]+k)->ZeroMatrix();
  Float dtime = -dclock();
  int nflops = 0;
  ParTrans::PTflops=0;
  int dir[] = {6,0,2,4,7,1,3,5},dirs[8]; //mapping between ParTrans and DiracOpAsqtad
  Matrix *min[NUM_DIR],*mout[NUM_DIR];
  if (NUM_DIR%N !=0) ERR.General(cname,fname,"NUM_DIR(%d)is not divisible by N(%d)\n",NUM_DIR,N);
  for(int mu = 0;mu<POS_DIR;mu += N){
	int mu_p,nu_p,rho_p,sigma_p;
    for(i  = 0;i<N;i++){
      mu_p = Rotate(mu,i);
      min[i] = Unit;
      mout[i] = result[mu_p];
      dirs[i] = dir[mu_p];
    }
    pt.run(N,mout,min,dirs);
    for(int nu = 0;nu<NUM_DIR;nu++)
    if(NotParallel(mu,nu)){
      for(i  = 0;i<N;i++){
	nu_p = Rotate(nu,i);
        min[i] = Unit;
        mout[i] = P3[i];
        dirs[i] = dir[nu_p];
      }
      pt.run(N,mout,min,dirs);
      for(i  = 0;i<N;i++){
		mu_p = Rotate(mu,i);
        min[i] = P3[i];
        mout[i] = P3mu[i];
        dirs[i] = dir[mu_p];
      }
      pt.run(N,mout,min,dirs);
      for(int rho = 0;rho<NUM_DIR;rho++)
      if(NotParallel(mu,rho) && NotParallel(nu,rho)){
        for(i  = 0;i<N;i++){
  	   	  rho_p = Rotate(rho,i);
          min[i] = P3[i];
          mout[i] = P5[i];
          dirs[i] = dir[rho_p];
        }
        pt.run(N,mout,min,dirs);
        for(i  = 0;i<N;i++){
	  	mu_p = Rotate(mu,i);
          min[i] = P5[i];
          mout[i] = P5mu[i];
          dirs[i] = dir[mu_p];
        }
        pt.run(N,mout,min,dirs);
        for(int sigma = 0;sigma<NUM_DIR;sigma++)
        if(NotParallel(mu,sigma) && NotParallel(nu,sigma)&&NotParallel(rho,sigma)){
          for(i  = 0;i<N;i++){
    		sigma_p = Rotate(sigma,i);
            min[i] = P5[i];
            mout[i] = P7[i];
            dirs[i] = dir[sigma_p];
          }
          pt.run(N,mout,min,dirs);
          for(i  = 0;i<N;i++){
    		mu_p = Rotate(mu,i);
            min[i] = P7[i];
            mout[i] = P7mu[i];
            dirs[i] = dir[mu_p];
          }
          pt.run(N,mout,min,dirs);
          for(i  = 0;i<N;i++){
    		sigma_p = Rotate(sigma,i);
            int sig_n = (sigma_p+4)%8;
            min[i] = P7mu[i];
            mout[i] = P7[i];
            dirs[i] = dir[sig_n];
          }
          pt.run(N,mout,min,dirs);
		  Float c75 = c7/c5;
          for(i  = 0;i<N;i++)
            vaxpy3_m(P5mu[i],&c75,P7[i],P5mu[i],vol*3);
	  nflops +=vol*18*2*N;
        }
        for(i  = 0;i<N;i++){
            rho_p = Rotate(rho,i);
            int rho_n = (rho_p+4)%8;
            min[i] = P5mu[i];
            mout[i] = P5[i];
            dirs[i] = dir[rho_n];
        }
        pt.run(N,mout,min,dirs);
		Float c53 = c5/c3;
        for(i  = 0;i<N;i++)
          vaxpy3_m(P3mu[i],&c53,P5[i],P3mu[i],vol*3);
		nflops +=vol*18*2*N;
      }
      for(i  = 0;i<N;i++){
        nu_p = Rotate(nu,i);
        min[i] = P3[i];
        mout[i] = P6[i];
        dirs[i] = dir[nu_p];
      }
      pt.run(N,mout,min,dirs);
      for(i  = 0;i<N;i++){
        mu_p = Rotate(mu,i);
        min[i] = P6[i];
        mout[i] = P6mu[i];
        dirs[i] = dir[mu_p];
      }
      pt.run(N,mout,min,dirs);
      for(i  = 0;i<N;i++){
        nu_p = Rotate(nu,i);
        int nu_n = (nu_p+4)%8;
        min[i] = P6mu[i];
        mout[i] = P6[i];
        dirs[i] = dir[nu_n];
      }
      pt.run(N,mout,min,dirs);
	  Float c63 = c6/c3;
      for(i  = 0;i<N;i++)
        vaxpy3_m(P3mu[i],&c63,P6[i],P3mu[i],vol*3);
	  nflops +=vol*18*2*N;
      for(i  = 0;i<N;i++){
        nu_p = Rotate(nu,i);
        int nu_n = (nu_p+4)%8;
        min[i] = P3mu[i];
        mout[i] = P3[i];
        dirs[i] = dir[nu_n];
      }
      pt.run(N,mout,min,dirs);

	  Float c31 = c3/c1;
	  for(i  = 0;i<N;i++){
	    mu_p =Rotate(mu,i);
        vaxpy3_m(result[mu_p],&c31,P3[i],result[mu_p],vol*3);
      }
	  nflops +=vol*18*2*N;
    }
  }
  
  for(j = 0;j<POS_DIR;j++){
     result[j] = fields[1] + vol*j;
     result[j+POS_DIR] = fields[2] + vol*j;
     VRB.Flow(cname,fname,"result[%d]=%p\n",j,result[j]);
  }
  for(j = 0;j<vol;j++) Unit[j] = c2;
  for(int mu = 0;mu<NUM_DIR;mu += N){
    if (mu == 4) for(j = 0;j<vol;j++) Unit[j] = -c2;
    int mu_p;
    for(i  = 0;i<N;i++){
      mu_p = Rotate(mu,i);
      min[i] =  Unit;
      mout[i] = result[mu_p];
      dirs[i] = dir[mu_p];
    }
    pt.run(N,mout,min,dirs);
//    pt.run(1,&(result[mu]),&Unit,&dir[mu]);
    for(i  = 0;i<N;i++){
      mu_p = Rotate(mu,i);
      min[i] =  result[mu_p];
      mout[i] = Pmumu[i];
      dirs[i] = dir[mu_p];
    }
    pt.run(N,mout,min,dirs);
//    pt.run(1,Pmumu,&result[mu],&dir[mu]);
    for(i  = 0;i<N;i++){
      mu_p = Rotate(mu,i);
      min[i] = Pmumu[i];
      mout[i] =  result[mu_p];
      dirs[i] = dir[mu_p];
    }
    pt.run(N,mout,min,dirs);
//    pt.run(1,&(result[mu]),Pmumu,&dir[mu]);
  }
  ffree( Unit);
  for(j = 0;j<N;j++){
    ffree( P3[j]);
    ffree( P3mu[j]);
    ffree( P5[j]);
    ffree( P5mu[j]);
    ffree( P7[j]);
    ffree( P7mu[j]);
  }
  dtime +=dclock();
  nflops += ParTrans::PTflops;
  printf("%s:%s:",cname,fname);
  print_flops(nflops,dtime);

#if 0
  printf("%s:%s:",cname,fname);
  for(i = 0;i<3;i++){
  for(j = 0;j<POS_DIR;j++){
	IFloat *tmp = (IFloat *)(fields[i]+vol*j);
  printf("%e ",*tmp);
  }
  printf("\n");
  }
#endif

  smeared=1;
}

ForceArg Fasqtad::EvolveMomFforce(Matrix *mom, Vector *phi, Vector *eta,
		      Float mass, Float step_size) {
  char *fname = "EvolveMomFforce(M*,V*,V*,F,F)";
  ERR.General(cname,fname,"Not Implemented\n");
  return ForceArg(0.0,0.0,0.0);
}


CPS_END_NAMESPACE
