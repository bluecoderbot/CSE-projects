#include <stdlib.h>
#include <stdbool.h> 

void dgemm( int m, int n, float *A, float *C )
{
// FILL-IN


  //LOOP UNROLLING 
  //LOOP UNROLLING
  //LOOP UNROLLING
  //LOOP UNROLLING
  //LOOP UNROLLING

  bool flag_Y = true, flag_X = true;

  if(m%2==1)
    flag_Y = false;
  if(n%2==1)
    flag_X = false;

    for( int i = 0; i < m; i+=2 )
    {
      for( int j = 0; j < m; j+=2 )
      {

        float cell_0_0 = 0, cell_0_1 =0, cell_1_0 =0, cell_1_1 = 0;

          for( int k = 0; k < n; k++ )
          {
            //C[i+j*m] += A[i+k*m]* A[j+k*m];

            cell_0_0 += A[i+k*m]* A[j+k*m];
              cell_0_1 += A[i+k*m]* A[j+1+k*m];
              cell_1_0 += A[i+1+k*m]* A[j+k*m];
              cell_1_1 += A[i+1+k*m]*A[j+1+k*m];

          }


          C[i+0+(j+0)*m] = cell_0_0;

          if(flag_X || m-j>1)
            C[i+0+(j+1)*m] = cell_0_1;

      if(flag_Y|| m-i>1)
      {
        C[i+1+(j+0)*m] = cell_1_0;
        if(flag_X || m-j>1)
          C[i+1+(j+1)*m] = cell_1_1;
      }
    }

  }


}