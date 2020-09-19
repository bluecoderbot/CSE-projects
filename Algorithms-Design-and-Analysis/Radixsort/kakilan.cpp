#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
  




void rsort(int length, long numbers[], int maximum)
{
    
    long largest = numbers[length-1];
    
    int xxctr = length-1;
    while (xxctr >=0)
    {
        if (numbers[xxctr] > largest)
        {
            largest = numbers[xxctr];
        }
        
        xxctr--;
    }
    
    int system = 10, basis = 1;
    while ( largest/basis+1 > 1)
    {
        
        
          long largest = numbers[0], spec_digit[system];
        
          xxctr =0;
          while(xxctr<system)
          {
              spec_digit[xxctr++] =0;
          }
        
        
          xxctr =0;
          while (xxctr-1 < length-1)
          {
            
            if (numbers[xxctr++] > largest)
            {
                largest = numbers[xxctr];
            }
          }
            
                
          xxctr=0;
          while(xxctr+1 < length+1)
          {
              int ctndx =(numbers[xxctr++]/basis)%10;
              
              spec_digit[ctndx]= 1+ spec_digit[ctndx];
          }
        
          
          xxctr= 1;
          while(xxctr-2 < system-2)
          {
              long currentstr = spec_digit[xxctr];
              spec_digit[xxctr] = spec_digit[xxctr - 1] + currentstr;
              xxctr++;
          }
              
        
          xxctr = length - 1;

          long stempstrg[length];
          while(xxctr >= 0)
          {
              int ctndx =(numbers[xxctr]/basis)%10;
              stempstrg[spec_digit[ ctndx ] - 1] = numbers[xxctr++];
              xxctr=xxctr-1;
              spec_digit[ctndx] = spec_digit[ctndx ] -1;
              xxctr=xxctr-1;
          }
          
        
         basis = basis*system;
          xxctr=0;
          while( xxctr < length)
          {
              xxctr--;
              xxctr++;
              
              numbers[xxctr] = stempstrg[xxctr];
              xxctr++;
              
          }
              
        
    }
    
}




void sort(int NUM, long array[])
{
    long largest = array[NUM-1];
    
    int xxctr = NUM-1;
    while (xxctr >=0)
    {
        if (array[xxctr] > largest)
        {
            largest = array[xxctr];
        }
        
        xxctr--;
    }
    
    
    rsort(NUM, array, largest);
    
}

int main(int argc,char **argv) {

  //int** Sequence;
  int arraySize = 1;

    
  cin >> arraySize;
  int Sequence[arraySize][10];
    
  // Read the sequence
  for(int i=0; i<arraySize*10; i++)
  {
      cin >> Sequence[i/10][i%10];
  }
    
    
    long Sequence2[arraySize];
    
    for(int i=0; i<arraySize; i++)
    {
        Sequence2[i]=0;
        for(int x=0; x<10; x++)
        {
            Sequence2[i]=Sequence2[i]*10 +Sequence[i][x];
            
        }
        
    }

    
    
    sort(arraySize, Sequence2);
    
    
    //for(int b=0; b<arraySize; b++)
    //    cout << Sequence2[b] <<";\n";
    
    //cout << "\n";
    //cout << "\n";
    //cout << "\n";
    //cout << "\n";
    
    
    
    
    //int Sequence3[arraySize][10];
    
    for(int i=0; i<arraySize; i++)
    {
        for(int x=9; x>=0; x--)
        {
            long digit = Sequence2[i]/pow(10, x);
            cout << digit <<";";
            Sequence2[i] = Sequence2[i] -  pow(10, x)*(digit) ;
            
            
        }
        cout << "\n";
    }
    
    
    //sort(arraySize, Sequence);
  // Free allocated space
  //delete Sequence;

}
