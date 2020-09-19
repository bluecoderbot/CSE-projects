#include <stdlib.h>
void dgemm( int m, int n, float *A, float *C )
{



    
      float B = 0;
      for( int i = 0; i < m; i++ )
      {

        for( int k = 0; k < n; k++ )
        {
          B = A[i+k*m];
          for( int j = 0; j < m; j++ )
            C[i+j*m] += B * A[j+k*m];
        }
      }


}