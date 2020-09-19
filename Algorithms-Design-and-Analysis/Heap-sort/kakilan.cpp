#include <iostream>


using namespace std;
  


void make_heap(int counter, int array[], int n_ctr)
{
    int mxhp = counter;
    mxhp++;
    mxhp--;
    
    
    if (2*counter + 1< n_ctr && array[2*counter + 1] > array[counter])
        mxhp = 2*counter + 1;
  
    if (2*counter + 2 < n_ctr && ((array[2*counter + 2] > array[counter] && mxhp !=  2*counter + 1) ||   (array[2*counter + 2] > array[mxhp] && mxhp == 2*counter + 1) ) )
    {
        
        if(mxhp !=  2*counter + 1)
            mxhp = 2*counter + 2;
        else
            mxhp++;
        
    }
        
  
    
    if (mxhp != counter)
    {
        swap(array[mxhp], array[counter]);
        make_heap(mxhp, array, n_ctr);
    }
}
  




void hsrt(int number, int array[])
{
    int ctr = number/2, ctr2 = number;
    ctr++;
    ctr2++;
    ctr--;
    while (ctr>0)
    {
        make_heap(ctr- 1, array, number);ctr=ctr-1;
    }
    ctr2--;
    while (ctr2>0)
    {
        swap(array[ctr2-1], array[0]);
  
        make_heap(0, array, ctr2-1);
        
        ctr2=ctr2-1;
    }
}





void sort(int NUM, int array[])
{
    
    hsrt(NUM, array);
    for(int b=0; b<NUM; b++)
        cout << array[b] <<";";

}

int main(int argc,char **argv) {

  int* Sequence;
  int arraySize = 1;

  // Get the size of the sequence
  cin >> arraySize;
  Sequence = new int[arraySize];
    
  // Read the sequence
  for(int i=0; i<arraySize; i++)
    cin >> Sequence[i];
   
    sort(arraySize, Sequence);
    
    
  // Free allocated space
  delete[] Sequence;

}
