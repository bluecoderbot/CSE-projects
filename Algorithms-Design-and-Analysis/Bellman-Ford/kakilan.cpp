#include <iostream>
#include <vector>
#include <string>
using namespace std;
  
bool solver(int ret[], vector<vector<int> > edges, int weights[], bool inf[], int N, int num_edges, int num_verts)
{
    
    
    
    int ret2[num_verts];
    if(N==0)
    {
        for(int i =0; i<num_verts; i++)
            ret2[i]=ret[i];
    }
    
    for(int i =0; i<num_edges; i++)
    {
        
        
        int p1 = edges[i][0];
        int p2 = edges[i][1];
        
        if(inf[p1]==false && (ret[p1]+weights[i]<ret[p2] || inf[p2]) )
        {
            ret[p2]=ret[p1]+weights[i];
            if(inf[p2])
                inf[p2]=false;
        }
    }
    
    
    
    if(N==0)
    {
        for(int i =0; i<num_verts; i++)
            if(ret2[i]!=ret[i])
                return false;
        return true;
    }
    
    
    return solver(ret, edges, weights, inf, N-1, num_edges, num_verts);
}


int main(int argc,char **argv)
{

    int num_verts;
    int num_edges;
    
    
    cin >> num_verts;
    cin >> num_edges;
    
    
    //int edges[num_edges][2];
    vector<vector<int> > edges( num_edges, vector<int> (2));
    
    int weights[num_edges];
    
    int min = 0, min_ind = 0;
    
    
    
    
  for(int i=0; i<num_edges; i++)
  {
      
      cin >> edges[i][0];
      //cout<< edges[i][0]<<" ";
      
      cin >> edges[i][1];
      //cout<< edges[i][1]<<" ";
      
      cin >> weights[i];
      //cout<< weights[i]<<" \n";
      
  }
    
    
    int ret[num_verts];
    bool inf[num_verts];
    
    ret[0]=0;
    inf[0]=false;
    
    for(int i =1; i<num_verts; i++)
    {
        ret[i]=0;
        inf[i]=true;
    }
    
    
    bool ans = solver(ret, edges, weights, inf, num_verts-1, num_edges, num_verts);
    
    
    if(ans)
    {
        cout<< "TRUE"<<"\n";
        for(int i=0; i<num_verts; i++)
        {
            if(inf[i])
                cout<< "INFINITY"<<"\n";
            else
                cout<< ret[i]<<"\n";
            
            
        }
    }
    else
    {
        cout<< "FALSE"<<"\n";
    }
    
    
}
