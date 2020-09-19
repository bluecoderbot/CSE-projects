#include <iostream>

using namespace std;

int sum_combo(int array[], int array2[], int NUM)
{
    int ret = 0;
    for(int i =0; i< NUM; i++)
    {
        ret = ret+(array[i])*(array2[i]);
    }
    return ret;
}


void copyarray(int array1[], int array2[], int NUM)
{
    for(int i =0; i<NUM; i++)
        array2[i] = array1[i];
}

int* perm(int prices[], int NUM, int holds[], int allowance)
{
    
    
    if(allowance==0)
        return holds;
    
    int max = -1;
    int* combo = new int[NUM];
    
    for(int i =1; i< NUM; i++)
    {
        
        
        int allowance2 = allowance - i;
        
        if(allowance2>=0)
        {
            int* holds2 = new int[NUM];
            
            copyarray(holds , holds2, NUM);
            
            
            
            holds2[i] = holds2[i]+1;
            
            int* combo2 = new int[NUM];
            combo2 = perm(prices, NUM, holds2, allowance2);
            
            
            
            
            int tempmax = sum_combo(prices, combo2, NUM);
            
            if(tempmax>max)
            {
                copyarray(combo2, combo, NUM);
                max = tempmax;
            }
            
            
        }
        
    }
    
    int output_ret =sum_combo(prices, combo, NUM);
    
    return combo;
}







int main(int argc,char **argv) {

  // Get the size of the sequence
  int n = 1;
  int* p; 

  cin >> n;

  p = new int[n+1];
  //read p; 
  p[0] = 0; 
  for(int i=1; i<=n; i++)
  {
    cin >> p[i];
      
  }


    
    int* holds = new int[n+1];

    for(int i =0; i<=n; i++)
    {
        holds[i]=0;
    }
    
    
    
    
    int* outerr = perm(p, n+1, holds, n);
    
    
    
    
    
    int rettt = sum_combo(p, outerr, n+1);
    
    cout << rettt <<"\n";
    
    
    
    
    for(int i=0; i<=n; i++)
    {
        for(int x =0; x<outerr[i]; x++)
            cout << i << " ";
    }
    
    cout << -1<<"\n";
 

   // Free allocated space
}
