#include <iostream>


using namespace std;
  

int split(int n2, int arxay[], int n1)
{
    int kk = n1;
    int fff = kk - 1;
    
    while ( (kk > n2 - 1)==false )
    {
        if( (arxay[kk]>=arxay[n2]) ==false )
            swap(arxay[kk], arxay[++fff]);
        kk++;
    }
    
    swap(arxay[n2], arxay[1+fff]);
    return 1+fff;
}





void qukSrt(int n2, int arxay[], int n1)
{
    
    if ( (n1 >= n2) == false)
    {
        int halfway = split(n2, arxay, n1);
        
        qukSrt( split(n2, arxay, n1) - 1, arxay, n1);
        qukSrt(n2, arxay, 1 + halfway);
    }
}








void sort(int NUM, int array[])
{
    
    qukSrt(NUM-1, array, 0);
    
    for(int b=0; b<NUM; b++)
        cout << array[b] <<";";

}

int main(int argc,char **argv) {

  int* Sequence;
  int arraySize = 1;

  
  cin >> arraySize;
  Sequence = new int[arraySize];
    
  
  for(int i=0; i<arraySize; i++)
    cin >> Sequence[i];
   
    sort(arraySize, Sequence);
    
    
  
  delete[] Sequence;

}
