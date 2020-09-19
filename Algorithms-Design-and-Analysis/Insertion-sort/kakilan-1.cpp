#include <iostream>

#define MAX_INT 2147483647

using namespace std;
  
void sort(int NUM, int array[])
{
    
    for(int m = 1; m < NUM; m++)
    {
        
        
        int h = m, num = array[m];
  
        for (;num<=array[h- 1]&&h- 1 >= 0 ; h--) array[h] = array[h- 1];
        
        
        array[h] = num;
        
        
        for(int k=0;k<=m;k++) cout << array[k] <<";";
        
        cout << "\n";
        
        
    }
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



