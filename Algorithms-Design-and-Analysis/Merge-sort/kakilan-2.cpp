#include <iostream>


using namespace std;
  


void merge_arrays(int end, int arr[], int middle, int start)
{
    
    int back[end - middle];
    for (int d = 1; d <= end - middle; d++) back[d-1] = arr[d+ middle];
  
    
    middle++;
    int front[middle - start];
    for(int y = 1; y <= middle - start ; y++) front[y-1] = arr[y-1+start];
    middle--;

    
    
    
    
    for(int mctr = start, c1 = 0, c2 = 0; c1 < middle - start + 1 || c2 < end - middle; mctr++)
    {
        if(c1 < middle - start + 1 && c2 < end - middle)
        {
            if (front[c1] <= back[c2])
                arr[mctr] = front[c1++];
            else
                arr[mctr] = back[c2++];
        }
        else if(c1 < middle - start + 1)
            arr[mctr] = front[c1++];
        else
            arr[mctr] = back[c2++];
    }
  
}
  

void msrt(int end, int start,int arr[])
{
    
    if (end-1 <= start) return;
    
    end--;
    
    msrt( start+(end-start)/2+1 , start, arr);
    msrt( end+1, start+(end-start)/2+1 , arr);
    merge_arrays(end, arr, start+(end-start)/2, start);

}

void sort(int NUM, int array[])
{
    
    msrt(NUM, 0, array);
    
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
