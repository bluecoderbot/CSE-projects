#include <iostream>
#include <vector>
#include <string>
using namespace std;
  






int* lowest2(int freqs[],  int N)
{
    int i_l = 0;
    for(int i =1; i<N; i++)
        if(freqs[i]<freqs[i_l])
            i_l = i;

    
    int i_sl;
    if(i_l!=0)
        i_sl = 0;
    else
        i_sl = 1;
    
    for(int i =0; i<N; i++)
        if(i!=i_l && freqs[i]<freqs[i_sl])
            i_sl = i;
    
    
    int* ret = new int[2];
    
    ret[0] = i_l;
    ret[1] = i_sl;
    
    return ret;
}




string* huff(int freqs[], int N)
{
    
    int i_l, i_sl;
    string* ret = new string[N];
    
    
    
    
    
    int* L_sl = lowest2(freqs, N);
    i_l  = L_sl[0];
    i_sl = L_sl[1];
    
    //cout<< freqs[i_l]  <<"\n";
    //cout<< freqs[i_sl] <<"\n\n";
    
    
    
    
    
    
    ret[i_l]="0";
    ret[i_sl]="1";
    
    if(N == 2)
        return ret;
    
    
    
    
    
    
    
    int* freqs2 = new int[N-1];
    
    int ofset = 0;
    for(int i =0; i<N; i++)
    {
        if(i_l==i || i_sl==i)
        {
            freqs2[N-2]+=freqs[i];
            ofset-=1;
        }
        else
        {
            freqs2[i+ofset]+=freqs[i];
        }
    }
    
    
  
    
    string* ret2 = new string[N-1];
    ret2 = huff(freqs2, N-1);
    
    
    
    
    int ofset2 = 0;
    
    for(int i =0; i<N; i++)
    {
        if(i_l==i || i_sl==i)
            ofset2-=1;
        else
            ret[i] = ret2[i+ofset2];
    }
    
    ret[i_l]=ret2[N-2] + ret[i_l];
    ret[i_sl]=ret2[N-2] + ret[i_sl];
    
    return ret;
    
}



int main(int argc,char **argv) {

  int* Sequence;
    int arraySize = 6;
    
    Sequence = new int[arraySize];
    
  // Read the sequence
  for(int i=0; i<arraySize; i++)
  {
      cin >> Sequence[i];
      //cout<<Sequence[i]<< " : ";
  }
    
  // Free allocated space
  //delete[] Sequence;
    
    
    string* seq = huff(Sequence, 6);

    
    
    for(int i =0; i<6; i++)
    {
        cout<< (char)(65+i)<<":"<<seq[i]<<"\n";
    }

}



