#include <iostream>


using namespace std;
  





int crossing(int low, int mid, int high, int array[])
{
    int sum = 0;
    bool sumset = false;
    
    int left_sum = 0;
    
    for(int i = mid; i>=low; i--)
    {
        sum = sum+array[i];
        
        
        if(sumset && sum>left_sum)
        {
            left_sum=sum;
        }
        else if(!sumset)
        {
            left_sum=sum;
            sumset = true;
        }
    }
    
    sum = 0;
    sumset = false;
    
    int right_sum = 0;
    for(int i = mid+1; i<=high; i++)
    {
        sum = sum+array[i];
        
        
        if(sumset && sum>right_sum)
        {
            right_sum=sum;
        }
        else if(!sumset)
        {
            right_sum=sum;
            sumset = true;
        }
    }
    
    return left_sum + right_sum;
}








int msrt(int low, int high, int array[])
{
    if(high == low)
    {
        return (int)array[0];
    }
    
    int mid = (int)((low+high)/2);
    
    int leftsum = msrt(low, mid, array);
    int rightsum = msrt(mid+1, high, array);
    int crosssum = crossing(low, mid, high, array);
    
    
    if (leftsum>=rightsum && leftsum>=crosssum)
        return leftsum;
    
    else if(rightsum>=leftsum && rightsum>=crosssum)
        return rightsum;
    else
        return crosssum;
}
















void val(int NUM, int array[])
{
    
    int ret = msrt(0, NUM-1, array);
    
    cout << ret;

    
}

int main(int argc,char **argv) {

  int* Sequence;
  int arraySize = 1;

  // Get the size of the sequence
  cin >> arraySize;
  Sequence = new int[arraySize];
    
  // Read the sequence
  for(int i=0; i<arraySize; i++)
  {
      cin >> Sequence[i];
  }
   
  val(arraySize, Sequence);
    
    
  // Free allocated space
  delete[] Sequence;

}
