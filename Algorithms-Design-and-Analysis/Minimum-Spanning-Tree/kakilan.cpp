#include <iostream>
#include <vector>
#include <string>
using namespace std;
  
void solver( vector< vector<int> > edges, int stack_verts[], int stack_edges[], int num_edges, int weights[], int N)
{
    bool flag = true;
    
    
    
    
    //cout<<N<<"\n\n\n";
    
    
    int min = weights[0];
    int min_ind = 0;
    for(int i=0; i<num_edges; i++)
    {
        
        
        
        int s1 = stack_verts[edges[i][0]];
        int s2 = stack_verts[edges[i][1]];
        
        
        
        if(stack_edges[i]!=1 &&(s1!=s2) && (flag || weights[i] < min))
        {
            
            min = weights[i];
            min_ind = i;
            
            flag = false;
        }
        
        //cout<<i<<": ";
        //cout<<"s1: " <<s1 <<" s2: " <<s2<<" min: "<<min <<" min_ind: "<<min_ind <<" weights: "<<weights[i] <<"\n";
        
    }
    
    
    
    if(flag) return;
    
    
    
    
    
    stack_verts[edges[min_ind][0]]=1;
    stack_verts[edges[min_ind][1]]=1;
    stack_edges[min_ind]=1;
    
    solver( edges, stack_verts, stack_edges, num_edges, weights, N+1);
    
    
}


void namer(int ret[], vector<int> tracker, vector<vector<int> > verticies, int num_verts, int n)
{
    
    if(n==0) return;
    
    int n2 =0;
    vector<int> tracker2;
    
    for(int i=0; i<n; i++)
    {
           for(int x=0; x<num_verts; x++)
           {
               if(tracker[i]!=x&& ret[x]==-1 && verticies[tracker[i]][x]==1)
               {
                   ret[x]=tracker[i];
                   tracker2.push_back(x);
                   n2++;
               }
           }
    }
    
    
    
    namer(ret, tracker2, verticies, num_verts, n2);
    
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
      //cout<< weights[i];
      
      
      
      if(i==0)
          min =weights[0];
      
      if(weights[i] < min)
      {
          min = weights[i];
          min_ind = i;
      }
      
  }
    
    
    
    
    
    int stack_verts[num_verts];
    int stack_edges[num_edges];
    
    for(int i =0; i<num_verts; i++)
        stack_verts[i] = 0;
    
    
    for(int i =0; i<num_edges; i++)
        stack_edges[i] = 0;
    
    stack_verts[edges[min_ind][0]]=1;
    stack_verts[edges[min_ind][1]]=1;
    stack_edges[min_ind]=1;
    
    

    
    
  
    
    solver( edges, stack_verts, stack_edges, num_edges, weights, 0);
    
    vector<vector<int> > verticies( num_verts, vector<int> (num_verts));
    
    
    for(int i=0; i<num_verts; i++)
        for(int x=0; x<num_verts; x++)
            verticies[i][x]=0;
    
    
    
    
    for(int i=0; i<num_edges; i++)
    {
        if(stack_edges[i]==1)
        {
            verticies[edges[i][0]][edges[i][1]] = 1;
            verticies[edges[i][1]][edges[i][0]] = 1;
        }
        
    }
    
 
    
    
    
    int ret[num_verts];
    ret[0]=0;
    vector<int> tracker;
    int n =0;
    
    
    for(int i=1; i<num_verts; i++)
    {
        if(verticies[0][i]==1)
        {
            
            ret[i]=0;
            tracker.push_back(i);
            n++;
            
        }
        else
            ret[i]=-1;
    }
    
    
   
    

    namer(ret, tracker, verticies,  num_verts,  n);
    
    
    
    
    for(int i=1; i<num_verts; i++)
    {
        cout<<ret[i]<<"\n";
    }
    
    
    
}
