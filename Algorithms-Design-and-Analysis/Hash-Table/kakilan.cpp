#include <iostream>
#include <vector>
#include <string>
using namespace std;




int main(int argc,char **argv) {

  int M = 1;

  
  cin >> M;
    
    
  vector <int> Sequence[M];
    
  while(true)
  {
      string command = "";
      cin >> command;
      
      
      //cout << command<< "\n";
      
      char head = command.at(0);
      
      if(head=='e')
      {
          break;
      }
      
      if(head == 'i')
      {
          
          int ll = command.length();
          
          int ind = 0;
          
          for(int x = 1; x<ll; x++)
              ind = ind*10+int(command.at(x))-48;
              
          
          int ind2 = ind%M;
          
          (Sequence[ind2]).insert((Sequence[ind2]).begin() , ind);
          
          
      }
      else if(head == 'o')
      {
          for (int i = 0; i < M; i++)
          {
              cout << i << ":";
              for(int x = 0; x<(Sequence[i]).size(); x++ )
              {
                  
                   cout << (Sequence[i]).at(x) << "->";
              }
              cout <<";\n";
          }
      }
      else if(head == 'd')
      {
          
          int ind = 0;
          int ll = command.length();
          for(int x = 1; x<ll; x++)
              ind = ind*10+int(command.at(x))-48;
                       
          
          cout << ind<<":";
          
          int ind2 = ind%M;
          
          int ind3 = -1;
          for(int x = 0; x<(Sequence[ind2]).size(); x++)
          {
              if( (Sequence[ind2]).at(x) == ind)
              {
                  ind3 = x;
                  break;
              }
          }
          if(ind3 !=-1)
          {
              (Sequence[ind2]).erase((Sequence[ind2]).begin()+ind3);
              cout << "DELETED;\n";
          }
          else
          {
              cout << "DELETE_FAILED;\n";
          }
          
      }
      else if(head == 's')
      {
          int ind = 0;
          int ll = command.length();
          for(int x = 1; x<ll; x++)
              ind = ind*10+int(command.at(x))-48;
                       
          cout << ind<<":";
          
          int ind2 = ind%M;
          
          int ind3 = -1;
          for(int x = 0; x<(Sequence[ind2]).size(); x++)
          {
              if( (Sequence[ind2]).at(x) == ind)
              {
                  ind3 = x;
                  break;
              }
          }
          if(ind3 !=-1)
          {
              cout << "FOUND_AT"<<ind2 << "," << ind3 <<";\n";
          }
          else
          {
              cout << "NOT_FOUND;\n";
          }
      }
      
      
  }
    
   
    
    
  

}
