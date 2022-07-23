#include <iostream>
#include <cstdlib>
#include<fstream>
using namespace std;
 
typedef class TREAP_NODE *treap_tree;

class TREAP_NODE
{
    int key;
    
    int random_priorities;
    
    TREAP_NODE *LChild, *RChild;

    friend class TREAP;
};
treap_tree nullnode, root;
 

class TREAP
{
    
    fstream f; // file pointer for opening and writing in the file
    
    
        ///////////// INITIALISING TREAP ////////////////////////////////////
        void initialize()
        {
           nullnode = new TREAP_NODE;
           nullnode->LChild = nullnode->RChild = nullnode;
           root = nullnode;
        }
        /////////////////////////////////////////////////////////////////////

        //////////// LEFT ROTATE ////////////////////////////////////////////
        void treap_left_rotate(treap_tree& k1)
        {
            treap_tree k2;
            k2 = k1->RChild;
            k1->RChild = k2->LChild;
            k2->LChild = k1;
            k1 = k2;
        }
        /////////////////////////////////////////////////////////////////////
        
        //////////// RIGHT ROTATE ////////////////////////////////////////////
        void treap_right_rotate(treap_tree& k1)
        {
            treap_tree k2;
            k2 = k1->LChild;
            k1->LChild = k2->RChild;
            k2->RChild = k1;
            k1 = k2;
        }
        //////////////////////////////////////////////////////////////////////

        ///////////// INSERT /////////////////////////////////////////////////
        void insert_in_treap(treap_tree& t, int x)
        {
            if (t == nullnode)
            {
                t = new TREAP_NODE;
                t->LChild = t->RChild = nullnode;
                t->key = x;
                t->random_priorities = rand();
            }
            else
            {
                if (t->key == x)
                {
                    return;
                }
                else
                {
                    if (x < t->key)
                    {
                        insert_in_treap(t->LChild, x);
                        if (t->LChild->random_priorities > t->random_priorities)
                        treap_right_rotate(t);
                    }
                    else
                    {
                        insert_in_treap(t->RChild, x);
                        if (t->RChild->random_priorities > t->random_priorities)
                        treap_left_rotate(t);
                    }
                }   
            }
        }
        ////////////////////////////////////////////////////////////////////////

        ////////////// DELETE //////////////////////////////////////////////////
        void delete_in_treap(treap_tree& t, int x)
        {
            if (t == nullnode)
                return;
            if (x > t->key)
                delete_in_treap(t->RChild, x);
            else if (x < t->key)
                delete_in_treap(t->LChild, x);
            else
            {
                if (t->LChild == nullnode && t->RChild == nullnode)
                {
                    delete t;
                    t = nullnode;
                }
                else if (t->LChild == nullnode)
                {
                    treap_tree tmp = t;
                    t = t->RChild;
                    delete tmp;
                }
                else if (t->RChild == nullnode)
                {
                    treap_tree tmp = t;
                    t = t->LChild;
                    delete tmp;
                }
                else
                {
                    if (t->LChild->random_priorities < t->RChild->random_priorities)
                    {
                        treap_left_rotate(t);
                        delete_in_treap(t->LChild, x);
                    }
                    else
                    {
                        treap_right_rotate(t);
                        delete_in_treap(t->RChild, x);
                    }
                }
            }
        }
        ////////////////////////////////////////////////////////////////////////

        ////////////////// PRINT TREE //////////////////////////////////////////
        
        
        void inorder(treap_tree ptr)
        {
            if (root == nullnode)
            {
                cout<<"Tree is empty, insert element first"<<endl;
                return;
            }
            if (ptr == nullnode)
                return;
            if (ptr != NULL)
            {
                
                inorder(ptr->LChild);
                cout<<ptr->key<<"  ";
                inorder(ptr->RChild);
            }
        }

        
        
        void print()
        {
            if (root == nullnode)
            {
                cout<<"Tree is empty, insert element first"<<endl;
                return;
            }
            cout<<"PRINTING TREAP.......\n";
            f.open("TREAP.gv" , ios::in | ios::out ) ;// opening file to write
            if(!f)cout<<"Error in opening the fILE !!!";// shows error if could not open the file
            f.clear();
            f<<"digraph g"; 
            f<<"\n";
            f<<"{";
            f<<"\n";
            f<<"node [shape = record,height=.1];";
            f<<"\n";

            preorder(root , f); // writes what nodes are in tree
            f<<"\n\n";
            childs(root , f); // writes the childrens of a node
            
            f<<"\n";
            f<<"}\n\n";
            
            f.close();
            
        
            system("dot -Tpng TREAP.gv -o TREAP_Tree.png");// graphviz command to make png file of output
            
            
            system("TREAP_Tree.png");// displays the file
        }

        void preorder(treap_tree ptr ,fstream &f)
        {
            // treap_tree ptr;
            // ptr=root; 
            if (ptr == nullnode)
                return;
            
            if(ptr!=NULL)
            {
                f<<"node";
                f<<ptr -> key;
                f<<"[label = ";
                f<<"\"<L> |<key>";
                f<<ptr -> key;
                f<<"|<bf>";
                f<<(ptr->random_priorities);     
                f<<"|<R> \"";
                f<<"];\n";
                preorder(ptr ->LChild , f); 
                preorder(ptr ->RChild , f);
            } 
        }





        void childs(treap_tree ptr ,fstream &f)
        {
        
            // treap_tree ptr;
            // ptr=root;
            
            if (ptr == nullnode)
               return;
            
            if(ptr!=NULL)  
            {
                
                if(ptr->LChild!=nullnode)
                {
                    f<<"\"node";
                    f<<ptr->key;
                    f<<"\":L -> ";
                    f<<"\"node";
                    f<<ptr->LChild->key;
                    f<<"\":";
                    f<<ptr->LChild->key;
                    f<<";\n";
                }
                if(ptr->RChild != nullnode)
                {
                    f<<"\"node";
                    f<<ptr->key;
                    f<<"\":R -> ";
                    f<<"\"node";
                    f<<ptr->RChild->key;
                    f<<"\":";
                    f<<ptr->RChild->key;
                    f<<";\n";
                }
                childs(ptr ->LChild , f); 
                childs(ptr ->RChild , f);
            } 
        }

        ////////////////////////////////////////////////////////////////////////
        
        
        
        ////////////////// SEARCH //////////////////////////////////////////////   	
        bool search_in_treap(TREAP_NODE *node,int e)
        {
            if (node == nullnode)
                return false;
            if (node->key == e)
                return true;
            else
            {
                if (e < node->key)
                    return search_in_treap(node->LChild, e);
                else
                    return search_in_treap(node->RChild, e);
            }
        }
        ////////////////////////////////////////////////////////////////////////

    public:
        TREAP()
        {
            initialize();
        }

        void TREAP_Insert(int k)
        {
            insert_in_treap(root, k);// calling for insertion of new node
        }

        void TREAP_Delete(int k)
        {
            if (root == nullnode)
            {
                cout<<"Tree is empty, nothing to delete"<<endl;
                return;
            }
            else
             delete_in_treap(root,k);
        }

        bool TREAP_Search(int k)
        {
            if (root == nullnode)
            {
                cout<<"Tree is empty"<<endl;
                return false;
            }
            else
              return search_in_treap(root,k);
        }

        void TREAP_Print()
        {
            inorder(root);
            print();
        }

};// CLASS TREAP ENDS.........







int main()
{
    TREAP treap;
    int choice, num , element;
    bool flag = false;
    
    
    
    while (1)
    {
        cout<<endl<<"----------------------------"<<endl;
        cout<<endl<<"Operations on Treap"<<endl;
        cout<<"1.Insert Element "<<endl;
        cout<<"2.Delete Element "<<endl;
        cout<<"3.Print Treap "<<endl;
        cout<<"4.Search "<<endl;
        cout<<"5.Quit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        cout<<endl<<"----------------------------"<<endl;


        
        switch(choice)
        {
            case 1:
                cout<<"Enter the number of elements to be inserted : ";
                cin>>num;
                for (int i = 0; i < num; i++)
                {
                    cin>>element;
                    treap.TREAP_Insert(element);
                }
                break;
            
            
            case 2:
                
                cout<<"Enter the number to be deleted : ";
                cin>>num;
                if (treap.TREAP_Search(num))
                    flag = true;
                else
                    cout<<"Element not found"<<endl;
                
                treap.TREAP_Delete( num);
                
                if (!treap.TREAP_Search(num) && flag)
                    cout<<"Element Deleted"<<endl;
                
                break;
            
            
            case 3:
                
                cout<<"Inorder Traversal:"<<endl;
                
                cout<<endl;
                treap.TREAP_Print();
                break;  
            
            
            case 4:
                cout<<"Enter element to search inside treap :";
                cin>>element;
                if(treap.TREAP_Search(element))
                {
                    cout<<"\nElement found";
                }
                else
                {
                    cout<<"\nElement not found";
                }
                cout<<endl; 
                break;
            
            
            case 5:
                exit(1);
                break;
            
            
            default:
                cout<<"Wrong choice"<<endl;
        
        
        }// END SWITCH
    }// END WHILE

return 0;

}
