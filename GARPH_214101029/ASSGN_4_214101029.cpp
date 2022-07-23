#include <iostream>
#include<vector>
#include<utility>
#include<climits>
#include<stack>
#include<fstream>
#include<queue>


using namespace std; 

class GRAPH
{
    int vertices,                          //no of vertices
        edges,                             //no of edges
        v1,                                //first vertex of an edge
        v2,                                //second vertex of an edge
        w,                                 //weight of an edge
        t=0;                               //time for a vertex start or end
    
    vector<pair<int ,int >>g[10000];      //GRAPH
    bool visited_node[10000]={0};         //i-th node visited or not ,true if visited
    int SCC=0;                             //NO OF STRONGLY CONNECTED COMPONENTS 
    struct time                            //for storing time 
        {
            int st=0,                      //storing satrt time
                et=0;                      //storing end time 
        };    

    fstream f;                             //to read/write .gv file 
    vector<int>str;                        //to store strongly connected component no. with ith vertex index
    
    
    
    
    
    
    //ADJACENCY LIST REPRESENTATION ////////////////////////////////////////
    void adajacency_list()
    {
        cout<<"ENTER THE GRAPH INPUT (vertex starts from 0):\n";
        cin>>vertices>>edges;
        // scadj.resize(vertices);
        

        for (int  i = 0; i < edges; i++)
        {
            
            cin>>v1>>v2>>w;

            //FOR UNDIRECTED GRAPH
            // g[v1].push_back(make_pair(v2,w));
            // g[v2].push_back(make_pair(v1,w));

            //FOR DIRECTED GRAPH
            g[v1].push_back(make_pair(v2,w));
           
        }

        
        
        ///////////////////////////////////////////////////////////////////////////////////////////
        
        struct time ti[vertices]; // TO SAVE START AND ENT TIME FOR VERTICES
        
        f.open("dfs.gv" , ios::in | ios::out ) ;// opening file to write
        if(!f)cout<<"Error in opening the fILE dfs.gv !!!";// shows error if could not open the file
        f.clear();
        f<<"digraph g"; 
        f<<"\n";
        f<<"{";
        f<<"\n";
        f<<"node [shape = record,height=.1];";
        f<<"\n";
    
        ///FOR QUESTION 1 ////////////////////////////////////////////////////////////////////////////////////////////////
        //CALLING DFS/////////////////////
        cout<<"\n-----------------------------------------------\n";
        cout<<"\nQUESTION 1--\n";
        cout<<"\nDFS TRAVERSAL :";
        char *ucolor = new char[vertices];
        int *upi = new int[vertices];
        for (int i = 0; i < vertices; i++)
        {
            ucolor[i]='w';
            upi[i] =-1;
        } 
        for (int i = 0; i < vertices; i++)
        {
            if(ucolor[i]=='w')
            {
                DFS(i,ucolor,upi,ti);
            }
        }
        cout<<"\n-----------------------------------------------\n";
        cout<<"\nQUESTION 2--\n";
        cout<<"\nSTRONGLY CONNECTED COMPONENTS : \n";






        // cout<<"-------------------------------\n\n";
        // for (int i = 0; i < vertices; i++)
        // {
        //     cout<<i<<" "<<ti[i].st<<" "<<ti[i].et;
        //     cout<<"\n";
        // }
        // f<<"\n\n"<<"\"GREEN-EDGE\""<<"->"<<"\"DFS-TREE-AND-TREE-EDGE\"";
        // f<<"\n"<<"\"RED-EDGE\""<<"->"<<"\"FORWARD-EDGE\"";
        // f<<"\n"<<"\"BLUE-EDGE\""<<"->"<<"\"BACK-EDGE\"";
        // f<<"\n"<<"\"DOTTED-EDGE\""<<"->"<<"\"CROSS-EDGE\""<<"\n";
        //PRINTING THE EDGES WITH WEIGHTS
        // int s=0; 
        int e=0;
        for (int i= 0; i < vertices;i++)
        {
            
            
            for (int j = 0; j < g[i].size(); j++)
            {
                ++e;
                // f<<"\""<<i<<" ["<<ti[i].st<<"/"<<ti[i].et<<"]\"->\""<<g[i][j].first<<" ["<<ti[g[i][j].first].st<<"/"<<ti[g[i][j].first].et<<"]\"";
                // f<<"\n";
                // cout<<i<<"-->"<<g[i][j].first<<" "<<"w= "<<g[i][j].second<<"\n";
                if(ti[i].st < ti[g[i][j].first].st &&
                   
                   ti[g[i][j].first].st < ti[g[i][j].first].et &&
                   ti[i].st < ti[g[i][j].first].et && 
                   
                   ti[g[i][j].first].et < ti[i].et &&
                   ti[g[i][j].first].st < ti[i].et &&
                   ti[i].st < ti[i].et  
                  )
                {
                    // cout<<e<<" "<<i<<"-->"<<g[i][j].first<<" "<<"fe"<<"\n";
                    if(upi[g[i][j].first]==i)
                    {
                        f<<" edge [ color=green ]";
                        f<<"\""<<i<<" ["<<ti[i].st<<"/"<<ti[i].et<<"]\"->\""<<g[i][j].first<<" ["<<ti[g[i][j].first].st<<"/"<<ti[g[i][j].first].et<<"]\"";
                        f<<"[style=bold,label=\"tree edge\"];";
                        f<<"\n";
                    }
                    else
                    {
                        //cout<<ti[i].st << ti[g[i][j].first].st << ti[g[i][j].first].et <<ti[i].st<<"\n";
                        f<<" edge [ color=red ]";
                        f<<"\""<<i<<" ["<<ti[i].st<<"/"<<ti[i].et<<"]\"->\""<<g[i][j].first<<" ["<<ti[g[i][j].first].st<<"/"<<ti[g[i][j].first].et<<"]\"";
                        f<<"[style=bold,label=\"forward edge\"];";
                        f<<"\n";
                    }
                }
                
                if(ti[g[i][j].first].st <= ti[i].st && ti[i].et <= ti[g[i][j].first].et)
                {
                   // cout<<e<<" "<<i<<"-->"<<g[i][j].first<<" "<<"be"<<"\n";
                   //cout<<ti[g[i][j].first].st <<"< "<< ti[i].st <<" <"<< ti[i].et <<"< "<< ti[g[i][j].first].et<<"\n";
                   f<<" edge [ color=blue ]";
                   f<<"\""<<i<<" ["<<ti[i].st<<"/"<<ti[i].et<<"]\"->\""<<g[i][j].first<<" ["<<ti[g[i][j].first].st<<"/"<<ti[g[i][j].first].et<<"]\"";
                   f<<"[style=bold,label=\"back edge\"];";
                   f<<"\n";

                }
                
                if(
                    ti[g[i][j].first].st < ti[g[i][j].first].et && 
                    ti[g[i][j].first].et < ti[i].st &&
                    ti[g[i][j].first].st < ti[i].st && 
                    ti[i].st < ti[i].et &&
                    ti[g[i][j].first].et < ti[i].et &&
                    ti[g[i][j].first].st < ti[i].et  
                     
                  )
                {
                   //cout<<e<<" "<<i<<"-->"<<g[i][j].first<<" "<<"ce"<<"\n";
                   f<<" edge [ color=black ]";
                   f<<"\""<<i<<" ["<<ti[i].st<<"/"<<ti[i].et<<"]\"->\""<<g[i][j].first<<" ["<<ti[g[i][j].first].st<<"/"<<ti[g[i][j].first].et<<"]\"";
                   f<<"[style=dotted,label=\"cross edge\"];";
                   f<<"\n";
                    
                }
                // else 
                // {
                //     f<<"\""<<i<<" ["<<ti[i].st<<"/"<<ti[i].et<<"]\"->\""<<g[i][j].first<<" ["<<ti[g[i][j].first].st<<"/"<<ti[g[i][j].first].et<<"]\"";
                   
                //     f<<"\n";
                // }
            }
        //     s=s+g[i].size();//SIZE OF ADJACENCY LIST
            
        }
        // cout<<"\n"<<"ADJACENCNCY LIST SIZE : "<<s;

        f<<"\n";
        f<<"}\n\n";
          
        f.close();
        
      
        system("dot -Tpng dfs.gv -o dfs.png");// graphviz command to make png file of output
        
        
        system("dfs.png");// displays the file
 

    }
    ////////////////////////////////////////////////////////////////////////
    
    ///// DFS TRAVERSAL ////////////////////////////////////////////////////
    void DFS(int u ,char ucolor[],int upi[] ,time ti[] )
    {   
        t++;
        cout<<u<<" -->";
        ti[u].st=t;
        ucolor[u]='g';
        for (auto i= 0; i != g[u].size();i++)
        {
            if(ucolor[g[u][i].first]=='w')
            {
                upi[g[u][i].first]=u;
                DFS(g[u][i].first,ucolor,upi,ti);
            }   
        }
       ucolor[u]='b';
       t++;
       ti[u].et=t;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////


    void strongconnect(int u  ,int order[], int link[], stack<int> *s,bool stack_member[] ,int sc[] ,vector<int>scadj[])
    {
        // cout<<"sc\n";
        // scadj.resize(vertices);
        static int  num=0;
        num++;
        order[u]=(num);
        link[u]=order[u];
        (*s).push(u);
        stack_member[u]=true;
        for(int  i = 0; i < g[u].size(); i++)
        {
            // cout<<"\n";
            //    cout<<g[u][i].first<<" ";
            if(order[g[u][i].first] == -1)
             {
                    // cout<<g[u][i].first<<" ";
                 strongconnect(g[u][i].first , order ,link ,s, stack_member ,sc , scadj) ;
                 link[u]=min(link[u] , link[g[u][i].first]);
             }
             else if(stack_member[g[u][i].first]) 
             {
                 link[u]=min(link[u] , order[g[u][i].first]);
             }
        }
        int scc=0;
        
        if(link[u]==order[u])
        {
            
            cout<<"\nSCC IS : ";
            SCC++;
            
            while((*s).top()!=u)
            {
                scc = (*s).top();
                cout<<scc<<" ";
                sc[scc]=SCC;
                scadj[SCC].push_back(scc);
                
                stack_member[scc]=false;
                (*s).pop();
            }

            scc = (*s).top();
            cout<<scc<<"\n";
            sc[scc]=SCC;
            scadj[SCC].push_back(scc);
            
            stack_member[scc]=false;
            (*s).pop();
        }
        // cout<<endl;
        // cout<<SCC<<"\n";
    } 
    void tarjan_algo()
    {
        int *order = new int[vertices+1];
	    int *link = new int[vertices+1];
	    bool *stack_member = new bool[vertices+1];
	    stack<int> *s = new stack<int>();
        int *sc= new int[vertices+1];
        vector<int>scadj[vertices+1];
        
        
        
         for (int i = 0; i < vertices; i++)
         {
             link[i]=-1;
             order[i]=-1;
             stack_member[i]=false;
            
            
         }
        //  cout<<"\n-----------------------------------------------\n";
         for (int i = 0; i < vertices; i++)
         {
            
             if(order[i] == -1)
               {
                   strongconnect(i , order, link, s, stack_member ,sc ,scadj);
               }
         }
        // cout<<"\n\n str-------";
        str.resize(vertices);
        
        
        
        for (int i = 0; i < vertices; i++)
        {
            // cout<<i<<" "<<sc[i]<<"\n";
            str[i]=sc[i];
            // cout<<i<<" "<<str[i]<<"\n";
        }
        
        ///FOR QUESTION 2 ////////////////////////////////////////////////////////////////////////////////////////////////
        fstream f;
        f.open("tarjan.gv" , ios::in | ios::out ) ;// opening file to write
        if(!f)cout<<"Error in opening the fILE tarjan.gv !!!";// shows error if could not open the file
        f.clear();
        f<<"digraph g"; 
        f<<"\n";
        f<<"{";
        f<<"\n";
        f<<"node [shape = record,height=.1];";
        f<<"\n";
        
        for (int i= 0; i < vertices;i++)
        {
            
            
            for (int j = 0; j < g[i].size(); j++)//TARJAN CODE
            {
                if(sc[i]==sc[g[i][j].first] )
                {
                    f<<"\n"<<" edge [ color=red ]";
                    f<<"\n"<<" node [ style=bold ]";
                    f<<"\n"<<"\""<<i<<"\""<<"->"<<"\""<<g[i][j].first<<"\" ";
                    f<<"[style=bold];";

                }
                else
                {
                    f<<"\n"<<" node [ style=bold ]";
                    f<<"\n"<<" edge [ color=black ]";
                    f<<"\n"<<"\""<<i<<"\""<<"\n"<<"\""<<g[i][j].first<<"\" ";
                }


            }
        }
        f<<"\n";
        f<<"}\n\n";
          
        f.close();
        
      
        system("dot -Tpng tarjan.gv -o tarjan.png");// graphviz command to make png file of output
        
        
        system("tarjan.png");// displays the 
        // cout<<"\n TAR end\n";

        vector<int>DAG[SCC+1];

        ///FOR QUESTION 3 ////////////////////////////////////////////////////////////////////////////////////////////////
        cout<<"\n----------------------------------------------------------\n";
        cout<<"\nQUESTION 3--\n";
        cout<<"\nGRAPH G' OF THE INPUT GRAPH G IS SHOWN IN OUTPUT --\n";
        cout<<"\n-----------------------------------------------\n";
         
        fstream q;
        q.open("q3.gv" , ios::in | ios::out ) ;// opening file to write
        if(!f)cout<<"Error in opening the fILE q3.gv !!!";// shows error if could not open the file
        q.clear();
        q<<"digraph g"; 
        q<<"\n";
        q<<"{";
        q<<"\n";
        q<<"node [shape = record,height=.1];";
        q<<"\n";
        q<<"\n"<<" node [ style=bold ]";
        q<<"\n"<<"\""<<"GRAPH G' RED EDGE : STRONG COMPONENT EDGE"<<"\"";
        q<<"->"<<"\""<<"BLUE EDGE : COMPONENT EDGE"<<"\"\n";
        // for (int i = 0; i < SCC; i++)
        // {
        //     cout<<i+1<<" "<<noonodesiniscc[i+1]<<"\n";
        // }
        // for (int i = 0; i <= SCC; i++)
        // {  cout<<i<<"--> ";
        //     for (int j = 0; j < scadj[i].size(); j++)
        //     {
        //         cout<<scadj[i][j]<<" ";
        //     }cout<<"\n";
            
        // }

        // TO PRINT ALL STRONGLY CONNECTED COMPONENTS
        // cout<<"\n\nstart writing in q3---";
        for (int i = 1; i <= SCC; i++)
        {   int first=scadj[i][0];
            for (int j = 0; j < scadj[i].size(); j++)
            {
                // cout<<"\n q3 printing-----\n";
                if(scadj[i].size() >1)
                {
                  q<<"\n"<<" edge [ color=red ]";
                  q<<"\n"<<" node [ style=bold ]";
                  if(j<scadj[i].size() -1)
                    {
                        q<<"\n"<<"\""<<scadj[i][j]<<"\""<<"->"<<"\""<<scadj[i][j+1]<<"\" ";
                        
                    }
                    else
                    {
                        q<<"\n"<<"\""<<scadj[i][j]<<"\""<<"->"<<"\""<<first<<"\" ";
                    }
                  q<<"[style=bold];";
                }
                // cout<<i<<" "<<scadj[i][j]<<" ";
                // scadjl[j].
            }cout<<"\n";
            
        }

        ///TO CONNECT STRONGLY CONNECTED COMPONENTS TO MAKE A DAG
        int scc_matrix[SCC+1][SCC+1];
        for (int i = 0; i <= SCC+1; i++)
        {
            for (int j = 0; j <= SCC+1; j++)
            {
                scc_matrix[i][j]=0;
            }
            
        }
        
        for (int i= 0; i < vertices;i++)
        {
            
            
            for (int j = 0; j < g[i].size(); j++)
            {
                if(str[i]!=str[g[i][j].first] && scc_matrix[str[i]][str[g[i][j].first]]!=1 && scc_matrix[str[g[i][j].first]][str[i]]!=1)
                {
                    // cout<<"\nmatrix--> ";
                    // cout<<scc_matrix[str[i]][str[g[i][j].first]]<<" "<<
                    // scc_matrix[str[g[i][j].first]][str[i]]<<"\n";
                    // cout<<i<<"-> "<<g[i][j].first<<" :"<<str[i]<<"\n";
                    q<<"\n"<<" edge [ color=blue ]";
                    q<<"\n"<<" node [ style=bold ]";
                    q<<"\n"<<"\""<<i<<"\""<<"->"<<"\""<<g[i][j].first<<"\" ";
                    // cout<<"\n"<<"\""<<str[i]<<"\""<<"->"<<"\""<<str[g[i][j].first]<<"\" ";
                    DAG[str[i]].push_back(str[g[i][j].first]); // SAVING THE DAG NODES...
                    q<<"[style=bold];";
                    
                    scc_matrix[str[i]][str[g[i][j].first]]=1;
                    scc_matrix[str[g[i][j].first]][str[i]]=1;
        //             noonodesiniscc[str[i]]--;
        //             cout<<noonodesiniscc[str[i]]<<"\n";

                }
        //         else
        //         {
        //             if(str[i]!=str[g[i][j].first] && noonodesiniscc[str[g[i][j].first]]!=0 && noonodesiniscc[str[i]]!=0)
        //             {
        //                 cout<<i<<"-> "<<g[i][j].first<<" :"<<"\n";
        //                 // if(noonodesiniscc[str[i]]!=0)
        //                 // {
        //                 f<<"\n"<<" edge [ color=black ]";
        //                 f<<"\n"<<"\""<<i<<"\""<<"->"<<"\""<<g[i][j].first<<"\" ";
        //                 noonodesiniscc[str[g[i][j].first]]--;
        //                 noonodesiniscc[str[i]]--;
        //                 // cout<<noonodesiniscc[str[g[i][j].first]]<<"\n";
        //                 // }
        //             }
        //         }
            }
        }
        
       



        q<<"\n";
        q<<"}\n\n";
          
        q.close();
        
      
        system("dot -Tpng q3.gv -o q3.png");// graphviz command to make png file of output
        
        
        system("q3.png");// displays the file

        ///FOR QUESTION 4 ////////////////////////////////////////////////////////////////////////////////////////////////
        cout<<"\nQUESTION 4--\n";
        
         
        fstream q4;
        q4.open("semic.gv" , ios::in | ios::out ) ;// opening file to write
        if(!q4)cout<<"Error in opening the fILE semic.gv !!!";// shows error if could not open the file
        q4.clear();
        q4<<"digraph g"; 
        q4<<"\n";
        q4<<"{";
        q4<<"\n";
        q4<<"node [shape = record,height=.1];";
        q4<<"\n";
        q4<<"\n"<<" node [ style=bold ]";
        q4<<"\n"<<"\""<<"DAG OF G' GRAPH"<<"\"";
        // q4<<"->"<<"\""<<"BLUE EDGE : COMPONENT EDGE"<<"\"\n";
        
        // cout<<"\n----------------------------------------------------------\n";
        for (int i = 1; i <= SCC; i++)
        {   
            
            for (int j = 0; j < DAG[i].size(); j++)
            {
                q4<<"\n"<<" edge [ color=blue ]";
                q4<<"\n"<<" node [ style=bold ]";
                q4<<"\n"<<"\""<<i<<"\""<<"->"<<"\""<<DAG[i][j]<<"\" ";
                // cout<<"\n"<<"\""<<i<<"\""<<"->"<<"\""<<DAG[i][j]<<"\" ";
                    // cout<<"\n"<<"\""<<i<<"\""<<"->"<<"\""<<g[i][j].first<<"\" ";
                    // DAG[str[i]].push_back(str[g[i][j].first]); // SAVING THE DAG NODES...
                q4<<"[style=bold];";
                // cout<<i<<" "<<DAG[i][j]<<"\n";
            }//cout<<"\n";
        }

         
        q4<<"\n";
        q4<<"}\n\n";
          
        q4.close();
        
      
        system("dot -Tpng semic.gv -o semic.png");// graphviz command to make png file of output
        
        
        system("semic.png");// displays the file

        int dag_matrix[SCC+1][SCC+1];
        for (int i = 1; i < SCC+1; i++)
        {
            
            for (int j = 1; j < SCC+1; j++)
            {
                dag_matrix[i][j]=0;
                dag_matrix[i][i]=1;
            }
            
        }
        cout<<"\nPRINT DAG OF GRAPH G':\n";
        for (int i = 0; i <= SCC; i++)
        {   
            cout<<i<<"--> ";
            for (int j = 0; j < DAG[i].size(); j++)
            {
                dag_matrix[i][DAG[i][j]]=1;
                cout<<DAG[i][j]<<" ";//dag_matrix[i][DAG[i][j]]=1;;
            }cout<<"\n";
        }
        cout<<"\n";
        
        
        // for (int i = 1; i <SCC+1; i++)
        // {
        //     for (int j = 1; j <SCC+1; j++)
        //     {
        //        cout<< dag_matrix[i][j]<<" ";
        //     }cout<<"\n";
            
        // }

        //APPLYING TOPOLOGICAL SEARCH TO OBTAINED DAG 
        cout<<"\nAPPLYING TOPOLOGICAL SORT TO CHECK\n";
         vector<int> in_degree(SCC+1, 0);
 
        for (int u = 0; u < SCC+1; u++) 
        {
            
            for (int itr = 0; itr < DAG[u].size(); itr++)
                in_degree[DAG[u][itr]]++;
        }
    
        queue<int> que;
        for (int i = 0; i < SCC+1; i++)
            if (in_degree[i] == 0)
                   que.push(i); 
    
        // Initialize count of visited vertices
        int cnt = 0;
       vector<int> top_order;
       while (!que.empty()) 
        {
            
            int u = que.front();
            que.pop();
            top_order.push_back(u);
            
            for (int itr = 0; itr < DAG[u].size(); itr++)
                
                if (--in_degree[ DAG[u][itr] ] == 0)
                      que.push(DAG[u][itr]);
    
            cnt++;
        }
    
        // Check if there was a cycle
        // if (cnt != SCC+1)
        // {
        //     cout << "\nThere exists a cycle in the graph\n";

        // }

        // cout<<"\nPrint topological order\n";
        int p=top_order[1];
        for (int i = 1; i < top_order.size() ; i++)
        {
            // cout<<p<<"->";
            // cout << top_order[i] << "\n";
            if(dag_matrix[p][top_order[i]]==0 )//||
            // // // // //if(dag_matrix[top_order[i]][p]==1 )
            {
                cout<<"\nIT IS NOT SEMICONNECTED";
                break;
            }
            if(i == top_order.size()-1)
            {
            // //     // 
                cout<<"\nIT IS  SEMICONNECTED";
                break;
            
            }
            p=top_order[i];
        }
        cout << "\n";
    
        ///FOR QUESTION 4 ////////////////////////////////////////////////////////////////////////////////////////////////
    
    }//TARJAN ALGO ENDS........

     



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///FOR QUESTION 5 /////////////////////////////////////////////////////////////////////////////////////////////////////

    void Dijkstra(int &start)
    {
        cout << "\nGetting the shortest path from " << start << " to all other nodes.\n";
        vector<int> dist;
        vector<int>camefrom;
        
        // Initialize all source->vertex as infinite.
        int n = vertices;
        for(int i = 0; i < n; i++)
        {
            dist.push_back(1000000007); // Define "infinity" as necessary by constraints.
            camefrom.push_back(start);
        }
            
        // Create a PQ.
        priority_queue<pair<int, int>, vector< pair<int, int> >, greater<pair<int, int> > > pq;
        
        // Add source to pq, where distance is 0.
        pq.push(make_pair(start, 0));
        dist[start] = 0;
        // camefrom[start]=start;
        
        
        fstream f;
        f.open("dj.gv" , ios::in | ios::out ) ;// opening file to write
        if(!f)cout<<"\nError in opening the fILE !!!\n";// shows error if could not open the file
        f.clear();
        f<<"digraph g"; 
        f<<"\n";
        f<<"{";
        f<<"\n";
        f<<"node [shape = record,height=.1];";
        f<<"\n";
        //  f<<"\n"<<" edge [ color=red ]";
        f<<"\n"<<" node [ style=bold ]";
        f<<"\n"<<"\""<<"SOURCE NODE : "<<start<<"\"\n";
        // f<<"\n"<<"\""<<u<<"\""<<"->"<<"\""<<v<<" ["<<dist[v]<<"] "<<"\" ";
        // f<<"[style=bold];";
                   
        
        while(pq.empty() == false)
        {
            // Get min distance vertex from pq
            int u = pq.top().first;
            pq.pop();
            // cout<<"\nfor= "<< u<<" "<<dist[u]<<"\n";
            // Visit all of u's friends. For each one (called v)....
            for(int i = 0; i < g[u].size(); i++)
            {
                int v = g[u][i].first;
                int weight = g[u][i].second;
                
                // If the distance to v is shorter by going through u...
                if(dist[v] > dist[u] + weight)
                {
                    // Update the distance of v.
                    dist[v] = dist[u] + weight;
                    camefrom[v]=u;
                    
                    // Insert v into the pq. 
                    pq.push(make_pair(v, dist[v]));
                    
                    // cout<<u<<"--> "<<v<<" dist= "<<dist[v]<<"\n";    
                }
                
            }

           
            
        }
        for(int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < g[i].size(); j++)
            {
                // cout << "\nfrom " <<i<< "-->" << g[i][j].first<<"\n" ;//<< " dist= " << dist[i] << " came from= "<<camefrom[i]<<endl;
                cout << "The distance from node " << start << " to node " << i << " is: " << dist[i] <<endl;
                f<<"\n"<<" edge [ color=red ]";
                f<<"\n"<<" node [ style=bold ]";
                f<<"\n"
                 <<"\"NODE:"<<i
                 <<", DISTANCE:["<<dist[i]<<"], ["<<camefrom[i]
                 <<"]"
                 <<"\""<<"->"
                 <<"\"NODE:"<<g[i][j].first
                 <<", DISTANCE:["<<dist[g[i][j].first]<<"], ["<<camefrom[g[i][j].first]
                 <<"]"<<"\" ";
                 f<<"[style=bold,label=\""<<g[i][j].second<<"\"];";
            }
            
            
        }
        cout<<"\n----------------------------------------------------------\n";
        f<<"\n";
        f<<"}\n\n";
            
        f.close();
            
        
        system("dot -Tpng dj.gv -o dj.png");// graphviz command to make png file of output
            
            
        system("dj.png");// displays the file
        
        

    }
    int shortestpath_dijkstra()
    {
        int start=0;
        cout<<"\n----------------------------------------------------------\n";
        cout<<"\nQUESTION 5--\n";
        cout<<"\nEnter the start node : ";
        cin>>start;
        Dijkstra(start);
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:

    void solutions()
    {
        adajacency_list();//TAKES INPUT GRAPH AND RUN DFS

        tarjan_algo();//CALCULATES THE STRONGLY CONNECTED COMPONENTS
    
        shortestpath_dijkstra();//FINDS SHORTEST PATHS FROM SOURSE GIVEN S TO ALL NODES

    }



};


int main()
{

    GRAPH gp;
    gp.solutions();    
    
    return 0;
}
