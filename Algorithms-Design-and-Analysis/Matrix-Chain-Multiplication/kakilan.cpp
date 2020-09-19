#include <iostream>
#include <vector>
#include <string>
using namespace std;
  




int main(int argc,char **argv) {

  int* Sequence;
  int arraySize = 1;

  // Get the size of the sequence
  cin >> arraySize;
    
    
    Sequence = new int[arraySize+1];
    
  // Read the sequence
  for(int i=0; i<=arraySize; i++)
  {
      cin >> Sequence[i];
      //cout<<Sequence[i]<< " : ";
  }
    
    
    
    
    
    
    //vector<vector<int> > dims( arraySize , vector<int> (arraySize));
    int dims[arraySize+1][arraySize+1];
    
    for(int i =0; i< arraySize; i++)
    {
        for(int x =0; x< arraySize; x++)
        {
            dims[i][x] = 0;
        }
    }
    
    string ordering[arraySize+1][arraySize+1];
    
    //vector<vector<string> > ordering( arraySize , vector<string> (arraySize));
    
    
    
    for(int i=0; i<arraySize; i++)
    {
        ordering[i][i] = "A"+to_string(i);
    }
    
   
       for(int i =1; i<arraySize; i++)
       {
           for(int x =0; x<arraySize-i; x++)
           {
               int cost = 0;
               string name;
               
               if(i==1)
               {
                   cost = Sequence[x]*Sequence[x+1]*Sequence[x+2];
                   
                   
                   name = "(A"+to_string(x) +"A"+to_string(x+1)+")";
                   
                   
                   
               }
               else
               {
                   cost = 2147483647;
                          
                   for(int y = 0; y< i; y++)
                   {
                       int c1 = dims[x][x+y];
                       int c2 = dims[x+y+1][x+i];
                       int c3 = Sequence[x]*Sequence[x+y+1]*Sequence[x+i+1]+c1+c2;
                       if(c3<cost)
                       {
                           name = "("+ ordering[x][x+y] + ordering[x+y+1][x+i] +")";
                           cost = c3;
                       }
                   }
               }
               ordering[x][x+i] = name;
               dims[x][x+i] = cost;
               
           }
       }
    
    
    
    
    cout<< dims[0][arraySize-1] <<"\n";
    
    
    if(arraySize==1)
    {
        cout<<"A0";
    }
    else if(arraySize==2)
    {
        cout<<"(A0A1)";
    }
    else
    {
        cout<< ordering[0][arraySize-1];
    }
    
    cout <<"\n";
    
    
  // Free allocated space
  delete[] Sequence;

}
