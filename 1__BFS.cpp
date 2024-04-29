#include<iostream>
#include<omp.h>
#include<vector>
#include<queue>
using namespace std;

class Graph
{
    int V;
    vector<vector<int>>adj;
    public:

    Graph(int V) : V(V),adj(V){}

    void addEdge(int start,int end)
    {
        adj[start].push_back(end);
    }

    void BFS(int start)
    {
        vector<bool>visited(V,false);
        queue<int>q;
        q.push(start);
        visited[start] = true;

        while(!q.empty())
        {
            int v = q.front();
            q.pop();
            cout<<v<<" ";
            #pragma omp parallel for
            for(int i=0;i<adj[v].size();i++)
            {
                int n = adj[v][i];
                if(!visited[n])
                {
                    q.push(n);
                    visited[n] = true;
                }
            }
        }

    }


    void DFS(int start)
    {
        vector<bool>visited(V,false);
        fun(start,visited);
    }

    void fun(int v,vector<bool>&visited)
    {
        visited[v] = true;
        cout<<v<<" ";

        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); i++)
        {
            int n = adj[v][i];
            if(!visited[n])
            {
                fun(n,visited);
            }
        }
        

    }
};


int main()
{
    int vertices;
    int edges;
    cout<<"enter the no. of the vertices :";
    cin>>vertices;
    cout<<"enter the number of the edges :";
    cin>>edges;

    Graph g(vertices);
    for(int i=0;i<edges;i++)
    {
        int start;
        int end;
        cin>>start>>end;
        g.addEdge(start,end);
    }
    g.BFS(0);
    cout<<endl;
    g.DFS(0);
}
