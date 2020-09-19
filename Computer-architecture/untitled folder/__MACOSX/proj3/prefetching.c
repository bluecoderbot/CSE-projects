#include <stdlib.h>
void dgemm( int m, int n, float *A, float *C )
{



    //PREFETCHING
    //PREFETCHING
    //PREFETCHING
    //PREFETCHING
    //PREFETCHING
    //PREFETCHING
    //PREFETCHING
    //PREFETCHING
    float *B = (float*) malloc( n * sizeof(float) );
    
      for( int i = 0; i < m; i++ )
      {
          for( int k = 0; k < n; k++ )
              B[k] = A[i+k*m];

        for( int k = 0; k < n; k++ )
          for( int j = 0; j < m; j++ )
            C[i+j*m] += B[k] * A[j+k*m];
      }



    free( B );
}
