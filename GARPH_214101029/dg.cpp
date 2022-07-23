
/*
#include<iostream>
#include<stdio.h>
using namespace std;
#include<conio.h>
#define INFINITY 999
struct node
{
    int cost;
    int value;
    int from;
}a[7];
void min_heapify(int *b, int i, int n)
{
    int j, temp;
    temp = b[i];
    j = 2 * i;
    while (j <= n)
    {
        if (j < n && b[j + 1] < b[j])
        {
            j = j + 1;
        }
        if (temp < b[j])
        {
            break;
        }
        else if (temp >= b[j])
        {
            b[j / 2] = b[j];
            j = 2 * j;
        }
    }
    b[j / 2] = temp;
    return;
}
void build_minheap(int *b, int n)
{
    int i;
    for(i = n / 2; i >= 1; i--)
    {
        min_heapify(b, i, n);
    }
}
void addEdge(int am[][7], int src, int dest, int cost)
{
     am[src][dest] = cost;
     return;
}
void bell(int am[][7])
{
    int i, j, k, c = 0, temp;
    a[0].cost = 0;
    a[0].from = 0;
    a[0].value = 0;
    for (i = 1; i < 7; i++)
    {
        a[i].from = 0;
        a[i].cost = INFINITY;
        a[i].value = 0;
    }
    while (c < 7)
    {
        int min = 999;
        for (i = 0; i < 7; i++)
        {
            if (min > a[i].cost && a[i].value == 0)
            {
                min = a[i].cost;
            }
            else
            {
                continue;
            }
        }
        for (i = 0; i < 7; i++)
        {
            if (min == a[i].cost && a[i].value == 0)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        temp = i;
        for (k = 0; k < 7; k++)
        {
            if (am[temp][k] + a[temp].cost < a[k].cost)
            {
                a[k].cost = am[temp][k] + a[temp].cost;
                a[k].from = temp;
            }
            else
            {
                continue;
            }
        }
        a[temp].value = 1;
        c++;
    }
    cout<<"Cost"<<"\t"<<"Source Node"<<endl; 
    for (j = 0; j < 7; j++)
    {
        cout<<a[j].cost<<"\t"<<a[j].from<<endl;
    }
}
int main()
{
    int n, am[7][7], c = 0, i, j, cost;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            am[i][j] = INFINITY;
        }
    }
    while (c < 12)
    {
        cout<<"Enter the source, destination and cost of edge\n";
        cin>>i>>j>>cost;
        addEdge(am, i, j, cost);
        c++;
    }
    bell(am);
    getch();
}
*/






#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector< vector<pair<int, int> > > FormAdjList()
{
    // Our adjacency list.
    vector< vector<pair<int, int> > > adjList;
    
    // We have 7 vertices, so initialize 7 rows.
    const int n = 7;
    
    for(int i = 0; i < n; i++)
        {
        // Create a vector to represent a row, and add it to the adjList.
        vector<pair<int, int> > row;
        adjList.push_back(row);
        }
    
    
    // Now let's add our actual edges into the adjacency list.
    // See the picture here: https://www.srcmake.com/uploads/5/3/9/0/5390645/spadjlist_orig.jpg
    
    adjList[0].push_back(make_pair(1, 2));
    adjList[0].push_back(make_pair(2, 3));
    
    adjList[1].push_back(make_pair(0, 2));
    adjList[1].push_back(make_pair(5, 1));
    
    adjList[2].push_back(make_pair(0, 3));
    adjList[2].push_back(make_pair(5, 2));
    
    adjList[3].push_back(make_pair(1, 4));
    adjList[3].push_back(make_pair(4, 1));
    adjList[3].push_back(make_pair(6, 2));
    
    adjList[4].push_back(make_pair(3, 1));
    adjList[4].push_back(make_pair(5, 2));
    adjList[4].push_back(make_pair(6, 1));
    
    adjList[5].push_back(make_pair(1, 1));
    adjList[5].push_back(make_pair(2, 2));
    adjList[5].push_back(make_pair(4, 2));
    adjList[5].push_back(make_pair(6, 2));
    
    adjList[6].push_back(make_pair(3, 2));
    adjList[6].push_back(make_pair(4, 1));
    adjList[6].push_back(make_pair(5, 2));
    
    // Our graph is now represented as an adjacency list. Return it.
    return adjList;
}



// Given an Adjacency List, find all shortest paths from "start" to all other vertices.
vector<int> DijkstraSP(vector< vector<pair<int, int> > > &adjList, int &start)
{
    cout << "\nGetting the shortest path from " << start << " to all other nodes.\n";
    vector<int> dist;
    
    // Initialize all source->vertex as infinite.
    int n = adjList.size();
    for(int i = 0; i < n; i++)
    {
        dist.push_back(1000000007); // Define "infinity" as necessary by constraints.
    }
        
    // Create a PQ.
    priority_queue<pair<int, int>, vector< pair<int, int> >, greater<pair<int, int> > > pq;
    
    // Add source to pq, where distance is 0.
    pq.push(make_pair(start, 0));
    dist[start] = 0;
    
    // While pq isn't empty...
    while(pq.empty() == false)
    {
        // Get min distance vertex from pq. (Call it u.)
        int u = pq.top().first;
        pq.pop();
        cout<<"\nfor= "<< u<<" "<<dist[u]<<"\n";
        // Visit all of u's friends. For each one (called v)....
        for(int i = 0; i < adjList[u].size(); i++)
        {
            int v = adjList[u][i].first;
            int weight = adjList[u][i].second;
            
            // If the distance to v is shorter by going through u...
            if(dist[v] > dist[u] + weight)
            {
                // Update the distance of v.
                dist[v] = dist[u] + weight;
                
                // Insert v into the pq. 
                pq.push(make_pair(v, dist[v]));
            // cout<<v<<" "<<dist[v]<<"\n";    
            }
            
        }
    }
    
    return dist;
}
    
void PrintShortestPath(vector<int> &dist, int &start)
{
    cout << "\nPrinting the shortest paths for node " << start << ".\n";
    for(int i = 0; i < dist.size(); i++)
    {
        cout << "The distance from node " << start << " to node " << i << " is: " << dist[i] << endl;
    }
}
    
int main() 
    {
    cout << "Program started.\n";
    
    // Construct the adjacency list that represents our graph. 
    vector< vector<pair<int, int> > > adjList = FormAdjList();
    
    // Get a list of shortest path distances for node 0.
    int node = 5;
    vector<int> dist = DijkstraSP(adjList, node);
    
    // Print the list.
    PrintShortestPath(dist, node);
    
    cout << "Program ended.\n";
    
    return 0;
    }
