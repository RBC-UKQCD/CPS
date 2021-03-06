#include<config.h>
CPS_START_NAMESPACE
//--------------------------------------------------------------------
/*!\file
  \brief Definition of slice_sum routine
 */
//--------------------------------------------------------------------
//  CVS keywords
//
//  $Source: /space/cvs/cps/cps++/src/comms/bgl/glb/slice_sum.C,v $
//  $State: Exp $
//
//--------------------------------------------------------------------

CPS_END_NAMESPACE
#include<comms/glb.h>
#include<util/smalloc.h>
#include<util/gjp.h>
#include <comms/sysfunc_cps.h>
CPS_START_NAMESPACE


void glb_sum_internal (Float * float_p, int dir,int len);


//-------------------------------------------------------------------
//* sum over a slice(hyperplane) which is orthogonal to the direction
//* "dir". There are "blcklength" summations to be done:
//* float_p[i] = sum_over_nodes_of_this_slice(float_p[i])
//-------------------------------------------------------------------

//-------------------------------------------------------------------
/*!
  The vector pointed to by \a float_p is summed over each 3-dimensional
  hyperplane of nodes which is perpendiculat to the \a dir direction

  \param float_p The number to be summed.
  \param blcklength The number of floating point numbers in the vector.
  \param dir The normal direction defining the hyperplane; one of {0, 1, 2, 3} 
  corresponding to {x, y, z, t}.
  \post The vector sum is written back to \a float_p, which is identical on
  all nodes in this hyperplane.

  \ingroup comms
*/
//-------------------------------------------------------------------
void slice_sum(Float * float_p, int blcklength, int dir)
{
  char *cname = "slice_sum";
  char *fname = "slice_sum(*float_p, int, int)";

  for (int i =0;i<4;i++)
  if (i != dir)
    glb_sum_internal(float_p,i,blcklength);

}


CPS_END_NAMESPACE
