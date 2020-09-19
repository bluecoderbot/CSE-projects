#include <iostream>
#include <vector>
#include <string>
using namespace std;
  

void solver(vector< vector<int> > verticies, int* stack, int* vals, int ind, int N)
{
    
    //-1 is unvisited, 0 is visited but not removed, 1 is removed
        
    if(stack[ind] ==-1)
    {
        stack[ind]=0;
        
        //bool flag = true;
        
        for(int x = 0; x<N ; x++)
        {
            if(ind!=x && verticies[ind][x]==1 && stack[x]<1)// is it on the stack and does ind point to x,
            {
                if(stack[x]==-1)
                {
                    solver(verticies, stack, vals, x, N);
                }
                else //stack[x]==0
                {
                    
                    //vals[x] = 0;
                }
                
                
                if(vals[ind]>vals[x]) vals[ind]= vals[x];
            }
        }
        
        stack[ind] = 1;
        
    }
        
    
    
}


int main(int argc,char **argv)
{

  int* Sequence;
    int num_verts;
    int num_edges;
    
    
    cin >> num_verts;
    cin >> num_edges;
    
    
    int edges[num_edges][2];
    
    //int verticies[num_verts][num_verts];
    
    
    vector<vector<int> > verticies( num_verts, vector<int> (num_verts));
    
  for(int i=0; i<num_edges; i++)
  {
      cin >> edges[i][0];
      cin >> edges[i][1];
      
      verticies[edges[i][0]][edges[i][1]]=1;
      
      
  }
    
    
    
    
    int stack[num_verts];
    int vals[num_verts];
    for(int i=0; i<num_verts; i++)
    {
        verticies[i][i]=1;
        stack[i]=-1;
        vals[i]=i;
    }
    
    
    for(int i=0; i<num_verts; i++)
    {
        //cout<< stack[i]<<"\n";
        solver(verticies, stack, vals, i, num_verts);
        
        
    }
    
    for(int i=0; i<num_verts; i++)
    {
        cout<< vals[i]<<"\n";
    }
    
    
  //delete[] Sequence;
 
}
