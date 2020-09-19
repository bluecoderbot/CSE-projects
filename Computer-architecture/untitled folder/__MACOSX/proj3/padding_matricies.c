#include <stdlib.h>
void dgemm( int m, int n, float *A, float *C )
{
// FILL-IN 

	if(m%2==1 || n%2==1)
	{
		int m2 = m, n2 = n;
		if(m%2==1)
			m2++;
		if(n%2==1)
			n2++;

		float *B = (float*) malloc( m2*n2 * sizeof(float) );
		
		for( int k = 0; k < n; k++ ) 
		{
		    for( int i = 0; i < m; i++ ) 
		    	B[i+k*m2] = A[i+k*m];


		}


	  	for( int i = 0; i < m; i++ )
		    for( int k = 0; k < n; k++ ) 
		      for( int j = 0; j < m; j++ )
		        C[i+j*m] += B[i+k*m2] * B[j+k*m2];


		free( B );
		return;
	}

	for( int i = 0; i < m; i++ )
	    for( int k = 0; k < n; k++ ) 
	      for( int j = 0; j < m; j++ )
	        C[i+j*m] += A[i+k*m] * A[j+k*m];

}