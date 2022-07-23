#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>
#include <string.h>
using namespace std;

//////////////// PARAMETERS //////////////////////////////////////////////////////////////////////////////
long long int avl_rotations=0,//NO OF ROTATINS IN AVL
              treap_rotations=0,//NO OF ROTATIONS IN TREAP
              
              key_comp_treap=0,//TOTAL KEY COMPARISIONS IN TREAP
              key_comp_bst=0,//TOTAL KEY COMPARISIONS IN BST
              key_comp_avl=0,//TOTAL KEY COMPARISIONS IN AVL
              
              avl_final_height=0,//FINAL HEIGHT OF AVL TREE
              bst_final_height=0,//FINAL HEIGHT OF BST TREE
              treap_final_height=0;//FINAL HEIGHT OF TREAP TREE
              
long double   avl_avg_node_height=0,//AVERAGE HEIGHT OF EVERY NODE IN FINAL AVL TREE
              bst_avg_node_height=0,//AVERAGE HEIGHT OF EVERY NODE IN FINAL BST TREE
              treap_avg_node_height=0,//AVERAGE HEIGHT OF EVERY NODE IN FINAL TREAP TREE
              
              total_bst_nodes=0,// TOTAL NODES IN BST
              total_treap_nodes=0,// TOTAL NODES IN TREAP
              total_avl_nodes=0;//TOTAL NODES IN AVL

double        ft_bst=0,//TOTAL TIME TAKEN BY BST
              ft_treap=0,//TOTAL TIME TAKEN BY TREAP
              ft_avl=0;//TOTAL TIME TAKEN BY AVL
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////// BST ///////////////////////////////////////////////////////////////////////////////////////////
class node
{
    int key; //KEY VALUE OF NODE
    class node *left; //LEFT CHILD OF NOFE
    class node *right; //RIGHT CHILD OF NODE
    friend class BST; //MAKING FRIEND BST CLASS TO USE MEMBERS

}*root;
 

class BST
{
        
        //////////////// SEARCH ////////////////////////////////////////
        void search_in_bst(int element, node **par, node **loc)
        {
            node *ptr, *ptrsave;
            if (root == NULL)
            {
                *loc = NULL;
                *par = NULL;
                return;
            }
            if (element == root->key)
            {
                key_comp_bst++;
                *loc = root;
                *par = NULL;
                return;
            }
            if (element < root->key)
            {
                key_comp_bst++;
                ptr = root->left;
            }
            else
                ptr = root->right;
            ptrsave = root;
            while (ptr != NULL)
            {
                if (element == ptr->key)
                {
                    key_comp_bst++;
                    *loc = ptr;
                    *par = ptrsave;
                    return;
                }
                ptrsave = ptr;
                if (element < ptr->key)
                {
                    key_comp_bst++;
                    ptr = ptr->left;
                }
            else
                ptr = ptr->right;
            }
            *loc = NULL;
            *par = ptrsave;
        }

        /////////////////////////////////////////////////////////////////
        
        /////////////// INSERTION ///////////////////////////////////////
        void insert_in_bst(node *tree, node *newnode)
        {
            if (root == NULL)
            {
                root = new node;
                root->key = newnode->key;
                root->left = NULL;
                root->right = NULL;
                // cout<<"Root Node is Added"<<"\n";
                return;
            }
            if (tree->key == newnode->key)
            {
                key_comp_bst++;
                // cout<<"Element already in the BST"<<"\n";
                return;
            }
            if (tree->key > newnode->key)
            {
                key_comp_bst++;
                if (tree->left != NULL)
                {
                    insert_in_bst(tree->left, newnode);	
            }
            else
            {
                    tree->left = newnode;
                    (tree->left)->left = NULL;
                    (tree->left)->right = NULL;
                    // cout<<"Node Added To Left"<<"\n";
                    return;
                }
            }
            else
            {
                if (tree->right != NULL)
                {
                    insert_in_bst(tree->right, newnode);
                }
                else
                {
                    tree->right = newnode;
                    (tree->right)->left = NULL;
                    (tree->right)->right = NULL;
                    // cout<<"Node Added To Right"<<"\n";
                    return;
                }	
            }
        }

        /////////////////////////////////////////////////////////////////

        /////////////// DELETION ////////////////////////////////////////
        void delete_in_bst(int element)
        {
            node *parent, *location;
            if (root == NULL)
            {
                cout<<"Tree empty"<<"\n";
                return;
            }
            search_in_bst(element, &parent, &location);
            if (location == NULL)
            {
                // cout<<"element not present in tree"<<"\n";
                return;
            }
            if (location->left == NULL && location->right == NULL)
            {
                    if (parent == NULL)
                    {
                        root = NULL;
                    }
                    else
                    {
                        if (location == parent->left)
                            parent->left = NULL;
                        else
                            parent->right = NULL;
                    }
            }
            if (location->left != NULL && location->right == NULL)
            {
                node *child;
                if (location->left != NULL)
                    child = location->left;
                else
                    child = location->right;
                if (parent == NULL)
                {
                    root = child;
                }
                else
                {
                    if (location == parent->left)
                        parent->left = child;
                    else
                        parent->right = child;
                }
            }
            if (location->left == NULL && location->right != NULL)
            {
                node *child;
                if (location->left != NULL)
                    child = location->left;
                else
                    child = location->right;
                if (parent == NULL)
                {
                    root = child;
                }
                else
                {
                    if (location == parent->left)
                        parent->left = child;
                    else
                        parent->right = child;
                }
            }
            if (location->left != NULL && location->right != NULL)
            {
                node *ptr, *ptrsave, *suc, *parsuc;
                ptrsave = location;
                ptr = location->right;
                while (ptr->left != NULL)
                {
                    ptrsave = ptr;
                    ptr = ptr->left;
                }
                suc = ptr;
                parsuc = ptrsave;
                if (suc->left == NULL && suc->right == NULL)
                    {
                         node *child;
                         node *parent = parsuc;
                         node *location = suc;
                        if (location->left != NULL)
                            child = location->left;
                        else
                            child = location->right;
                        if (parent == NULL)
                        {
                            root = child;
                        }
                        else
                        {
                            if (location == parent->left)
                                parent->left = child;
                            else
                                parent->right = child;
                        }
                    }
                else
                    {
                        node *child;
                        node *parent = parsuc;
                        node *location = suc;
                        if (location->left != NULL)
                            child = location->left;
                        else
                            child = location->right;
                        if (parent == NULL)
                        {
                            root = child;
                        }
                        else
                        {
                            if (location == parent->left)
                                parent->left = child;
                            else
                                parent->right = child;
                        }
                    }
                if (parent == NULL)
                {
                    root = suc;
                }
                else
                {
                    if (location == parent->left)
                        parent->left = suc;
                    else
                        parent->right = suc;
                }
                suc->left = location->left;
                suc->right = location->right;
            }
            free(location);
        }

        /////////////////////////////////////////////////////////////////
        long long int height_bst(node *ptr) // final tree height
        {
            if(ptr==NULL)
              return 0;
            else
            {
                long long int l_depth=height_bst(ptr->left);
                long long int r_depth=height_bst(ptr->right);
                if(l_depth > r_depth)
                  return(l_depth +1);
                else
                  return(r_depth +1);


            } 
        }
        void total_nodes_bst(node *ptr) //no of total nodes in bst
        {
            // cout<<"\nin total_nodes_bst";
            if(ptr!=NULL)
            {
                total_nodes_bst(ptr->left);
                // cout<<ptr->key<<" ";
                total_bst_nodes++;
                total_nodes_bst(ptr->right);

            }
        }

        long long int av_node_height_bst(node *ptr)//average height of every nodes in bst
        {
            // cout<<"\nin av_node_height_bst";
            if(ptr!=NULL)
            {
                av_node_height_bst(ptr->left);
                // cout<<ptr->key<<" ";
                bst_avg_node_height += height_bst(ptr); 
                av_node_height_bst(ptr->right);
            }
        }
        
        
        ////////////////////////////////////////////////////////////////

    public:
        BST()
        {
            root = NULL;
        }
    
        void BST_Insert(long long int k)
        {
            // cout<<"\nINSERT IN BST--->"<<k;
            node *temp;
            // int e;
            // cout<<"Enter the number of elem to be inserted : ";
            // cin>>e;
            // for (int  i = 0; i < e; i++)
            // {
                temp = new node;
                // cin>>temp->key;
                temp->key=k;
                insert_in_bst(root, temp);    
            // }
        }

        void BST_Delete(int k)
        {
            // cout<<"\nDELETE IN BST--->"<<k;
            delete_in_bst(k);
        }

        long long int final_height_bst()
        {
               return height_bst(root);
        }
        void av_bst()
        {
            total_nodes_bst(root);
            av_node_height_bst(root);
            // cout<<total_bst_nodes<<"\n";
            // cout<<bst_avg_node_height<<"\n";
        }

        

        
};// BST CLASS ENDS.............
////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////// TREAP ///////////////////////////////////////////////////////////////////////////
typedef class TREAP_NODE *treap_tree;

class TREAP_NODE
{
    int key;
    
    int random_priorities;
    
    TREAP_NODE *LChild, *RChild;

    friend class TREAP;
};
treap_tree nullnode, treap_root;
 

class TREAP
{
    
    fstream f; // file pointer for opening and writing in the file
    
    
        ///////////// INITIALISING TREAP ////////////////////////////////////
        void initialize()
        {
           nullnode = new TREAP_NODE;
           nullnode->LChild = nullnode->RChild = nullnode;
           treap_root = nullnode;
        }
        /////////////////////////////////////////////////////////////////////

        //////////// LEFT ROTATE ////////////////////////////////////////////
        void treap_left_rotate(treap_tree& k1)
        {
            treap_rotations++;
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
            treap_rotations++;
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
                    key_comp_treap++;
                    return;
                }
                else
                {
                    if (x < t->key)
                    {
                        key_comp_treap++;
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
            {
                key_comp_treap++;
                delete_in_treap(t->RChild, x);
            }
            else if (x < t->key)
            {
                key_comp_treap++;
                delete_in_treap(t->LChild, x);
            }
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
            if (treap_root == nullnode)
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
            if (treap_root == nullnode)
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

            preorder(treap_root , f); // writes what nodes are in tree
            f<<"\n\n";
            childs(treap_root , f); // writes the childrens of a node
            
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
            {
                key_comp_treap++;
                return true;
            }
            else
            {
                if (e < node->key)
                {
                    key_comp_treap++;
                    return search_in_treap(node->LChild, e);
                }
                else
                    return search_in_treap(node->RChild, e);
            }
        }
        ////////////////////////////////////////////////////////////////////////
        long long int height_treap(treap_tree ptr) // final tree height
        {
            if(ptr== nullnode)
              return 0;
            else
            {
                long long int l_depth=height_treap(ptr->LChild);
                long long int r_depth=height_treap(ptr->RChild);
                if(l_depth > r_depth)
                  return(l_depth +1);
                else
                  return(r_depth +1);


            } 
        }

        void total_nodes_treap(treap_tree ptr) //no of total nodes in bst
        {
            // cout<<"\nin total_nodes_bst";
            if(ptr!=nullnode)
            {
                total_nodes_treap(ptr->LChild);
                // cout<<ptr->key<<" ";
                total_treap_nodes++;
                total_nodes_treap(ptr->RChild);

            }
        }

        long long int av_node_height_treap(treap_tree ptr)//average height of every nodes in bst
        {
            // cout<<"\nin av_node_height_bst";
            if(ptr!= nullnode)
            {
                av_node_height_treap(ptr->LChild);
                // cout<<ptr->key<<" ";
                treap_avg_node_height += height_treap(ptr); 
                av_node_height_treap(ptr->RChild);
            }
        }

    public:
        TREAP()
        {
            initialize();
        }

        void TREAP_Insert(int k)
        {
            // cout<<"\nINSERT IN TREAP--->"<<k;
            insert_in_treap(treap_root, k);// calling for insertion of new node
        }

        void TREAP_Delete(int k)
        {
            // cout<<"\nDELETE IN TREAP--->"<<k;
            if (treap_root == nullnode)
            {
                cout<<"Tree is empty, nothing to delete"<<endl;
                return;
            }
            else
             delete_in_treap(treap_root,k);
        }

        bool TREAP_Search(int k)
        {
            if (treap_root == nullnode)
            {
                cout<<"Tree is empty"<<endl;
                return false;
            }
            else
              return search_in_treap(treap_root,k);
        }

        void TREAP_Print()
        {
            inorder(treap_root);
            print();
        }

        long long int final_treap_height()
        {
            return height_treap(treap_root);
        }

        void av_treap()
        {
            total_nodes_treap(treap_root);
            av_node_height_treap(treap_root);

        }

};// CLASS TREAP ENDS.........
////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////// AVL //////////////////////////////////////////////////////////////////////////////////////

class AVL_Node
{
	private:

	int key;
	
    AVL_Node *LChild, *RChild;
	
    int height;
    
    friend class AVL_Tree;
};

class AVL_Tree
{
    AVL_Node *root; // root of the avl tree
    
    
        int max(int a, int b)// finding the max value
        {
            return (a > b)? a : b;
        }

        int height(AVL_Node *N) // for calculating height of node N
        {
            if (N == NULL)
                return 0;
            return N->height;
        }

        int Balancefactor(AVL_Node *N) //calculating balance factor
        {
            if (N == NULL)
                return 0;
            
            return (height(N->LChild) - height(N->RChild));
        }

        AVL_Node * min_node(AVL_Node* node)// finding minimum valued node
        {
            AVL_Node* current = node;

            
            while (current->LChild != NULL)
                current = current->LChild;

            return current;
        }

        void inorder(AVL_Node *root) // inorder traversal
        {
            if(root != NULL)
            {
                
                inorder(root->LChild);
                cout << root->key << " "<<root->height<<"\n";
                inorder(root->RChild);
            }
        }


        AVL_Node* newNode(int key) // for a new node
        {
            AVL_Node* node = new AVL_Node();
            node->key = key;
            node->LChild = NULL;
            node->RChild = NULL;
            node->height = 1; // new node is initially added at leaf                
            return(node);
        }

        ///////////////////////////////  ROTAION FUCTIONS  /////////////////////////////////////////////////
        AVL_Node *rotateToLChild(AVL_Node *x)
        {
            avl_rotations++;
            AVL_Node *y = x->RChild;
            AVL_Node *T = y->LChild;
            y->LChild = x;
            x->RChild = T;
            x->height = max(height(x->LChild),height(x->RChild)) + 1;//Updating height
            y->height = max(height(y->LChild),height(y->RChild)) + 1;
            return y;
        }


        AVL_Node *rotateToRChild(AVL_Node *y)
        {
            avl_rotations++;
            AVL_Node *x = y->LChild;
            AVL_Node *T = x->RChild;
            x->RChild = y;
            y->LChild = T;
            y->height = max(height(y->LChild),height(y->RChild)) + 1;//Updating height
            x->height = max(height(x->LChild),height(x->RChild)) + 1;
            return x;
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////





        //////////////////////////////////  FOR INSERTION PROCESS  /////////////////////////////////////////
        AVL_Node* insertIntoAVL(AVL_Node* node, int key)
        {
            
            if (node == NULL)
                return(newNode(key));

            if (key < node->key)
            {
                key_comp_avl++;
                node->LChild = insertIntoAVL(node->LChild, key);
            }
            else if (key > node->key)
            {
                key_comp_avl++;
                node->RChild = insertIntoAVL(node->RChild, key);
            }
            else 
                return node;

            node->height = 1 + max(height(node->LChild), height(node->RChild)); //Update height

            int balance = Balancefactor(node); // checking unbalanced or not

            if (balance > 1 && key < node->LChild->key) // LChild LChild Case
                return rotateToRChild(node);

            
            if (balance < -1 && key > node->RChild->key) // RChild RChild Case
                return rotateToLChild(node);

            if (balance > 1 && key > node->LChild->key) // LChild RChild Case
            {
                node->LChild = rotateToLChild(node->LChild);
                return rotateToRChild(node);
            }

            if (balance < -1 && key < node->RChild->key) // RChild LChild Case
            {
                node->RChild = rotateToRChild(node->RChild);
                return rotateToLChild(node);
            }

            return node;
        }// insertIntoAVL
        ////////////////////////////////////////////////////////////////////////////////////////////////////




        /////////////////////////////////  FOR DELETION PROCESS  ///////////////////////////////////////////
        AVL_Node* avl_delete(AVL_Node* root, int key)
        {
            
            
            if (root == NULL)
                return root;

            
            if ( key < root->key )
            {
                key_comp_avl++;
                root->LChild = avl_delete(root->LChild, key);
            }
            
            else if( key > root->key )
             {
                key_comp_avl++;
                root->RChild = avl_delete(root->RChild, key);
             }
            
            else
            {
                
                if( (root->LChild == NULL) || (root->RChild == NULL) ) // node with only one child or no child
                {
                    AVL_Node *temp = root->LChild ? root->LChild : root->RChild;
                    if (temp == NULL) // No child 
                    {
                        temp = root;
                        root = NULL;
                    }
                    else 
                    *root = *temp; // Copy the contents of the non-empty child
                    free(temp);
                }
                else
                {
                    AVL_Node* temp = min_node(root->RChild);
                    root->key = temp->key; // Copy the inorder successor's
                    root->RChild = avl_delete(root->RChild, temp->key); // Delete the inorder successor
                }
            }

            
            if (root == NULL)
            return root;

            
            root->height = 1 + max(height(root->LChild), height(root->RChild));

            
            int balance = Balancefactor(root);

            

            if (balance > 1 && Balancefactor(root->LChild) >= 0)
                return rotateToRChild(root);

            
            if (balance > 1 && Balancefactor(root->LChild) < 0)
            {
                root->LChild = rotateToLChild(root->LChild);
                return rotateToRChild(root);
            }


            if (balance < -1 && Balancefactor(root->RChild) <= 0)
                return rotateToLChild(root);

            
            if (balance < -1 && Balancefactor(root->RChild) > 0)
            {
                root->RChild = rotateToRChild(root->RChild);
                return rotateToLChild(root);
            }

            return root;
        }//DELETE
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        long long int height_avl(AVL_Node *ptr) // final tree height
        {
            if(ptr==NULL)
              return 0;
            else
            {
                long long int l_depth=height_avl(ptr->LChild);
                long long int r_depth=height_avl(ptr->RChild);
                if(l_depth > r_depth)
                  return(l_depth +1);
                else
                  return(r_depth +1);


            } 
        }

        void total_nodes_avl(AVL_Node *ptr) //no of total nodes in bst
        {
            // cout<<"\nin total_nodes_bst";
            if(ptr!=NULL)
            {
                total_nodes_avl(ptr->LChild);
                // cout<<ptr->key<<" ";
                total_avl_nodes++;
                total_nodes_avl(ptr->LChild);

            }
        }

        long long int av_node_height_avl(AVL_Node *ptr)//average height of every nodes in bst
        {
            // cout<<"\nin av_node_height_bst";
            if(ptr!=NULL)
            {
                av_node_height_avl(ptr->LChild);
                // cout<<ptr->key<<" ";
                avl_avg_node_height += height_avl(ptr); 
                av_node_height_avl(ptr->RChild);
            }
        }


    public:
            AVL_Tree()
            {
                root=NULL;
            } 

            void AVL_Insert(int k)
            {   
                root=insertIntoAVL(root,k);// calling for insertion of new node
            }
            void AVL_Delete(int k)
            {
                root= avl_delete(root ,k);//calling for node deletion
            }

            void po()
            {
                inorder(root);//printing inorder
            }
             
            long long int final_height_avl()
            {
                return height_avl(root);
            } 

            void av_avl()
            {
                total_nodes_avl(root);
                av_node_height_avl(root);
            }
   
};//AVL_TREE CLASS ENDS..............
////////////////////////////////////////////////////////////////////////////////////////////////////////////




int main()
{
    // TREE OBJECTS
    BST bst;
    TREAP treap;
    AVL_Tree avl;
    
    fstream f; // FOR READING THE TEST FILE
    string value,//KEY FOR INSERTION / DELETION
           operation,// WHICH OPERATION TO PERFORM 
           filename = "TEST_";// FILE NAME
    long long int l=0; // COUNTER FOR OPERATIONS
    
    for (int i = 1; i <= 6; i++) // FOR LOOP FOR 6 TEST FILES.......
    {
              avl_rotations=0;
              treap_rotations=0;
              
              key_comp_treap=0;
              key_comp_bst=0;
              key_comp_avl=0;
              
              avl_final_height=0;
              bst_final_height=0;
              treap_final_height=0;
              
              avl_avg_node_height=0;
              bst_avg_node_height=0;
              treap_avg_node_height=0;

              total_bst_nodes=0;
              total_treap_nodes=0;
              total_avl_nodes=0;

        filename = "TEST_";
        if(i==1)filename.append("1");
        if(i==2)filename.append("2");
        if(i==3)filename.append("3");
        if(i==4)filename.append("4");
        if(i==5)filename.append("5");
        if(i==6)filename.append("6");   
        filename.append(".txt");

        // cout<<filename<<"\n";
        // fstream w;
        // w.open("g.txt" ,ios::in | ios::out);    
            f.open( filename , ios::in|ios::out );
            if(!f)cout<<"error";
            else
            {
                // cout<<"\nopen.......................\n";
                ///////// BST OPERATIONS /////////////////////////////////////////////
                l=0;
                clock_t s =clock();
                while (!f.eof())
                {
                    
                    f>>operation;
                    f>>value;

                    if(operation=="INSERT")
                    {
                        l++;
                        
                        bst.BST_Insert(stoi(value));
                        

                        // w<<key_comp_bst<<"\n";
                        
                        // treap.TREAP_Insert(stoi(value));
                        
                    }
                    if(operation=="DELETE")
                    {
                        l++;
                        
                        bst.BST_Delete(stoi(value));
                        // w<<key_comp_bst<<"\n";
                        
                        // treap.TREAP_Delete(stoi(value));
                        
                    }
                    clock_t e =clock();
                    // cout<<operation<<" "<<value<<"\n";
                    ft_bst =+ static_cast<double>(e - s) / CLOCKS_PER_SEC;
                    // cout<<"\n";
                    
                

                    
                }
                ////////////////////////////////////////////////////////////////////////
                // cout<<"\n\nEND OF FILE..................."<<l-1;
                // cout<<"\n\n"<<fixed<<setprecision(6)<<setw(12);
                // cout<<ft_bst<<"\n";
                
            }
            f.close();

            f.open(filename, ios::in|ios::out);
            if(!f)cout<<"error";
            else
            {
                // cout<<"\nopen.......................\n";
                //////////// TREAP OPERATIONS /////////////////////////////////////////
                l=0;
                clock_t st =clock();
                while (!f.eof())
                {
                    
                    f>>operation;
                    f>>value;

                    if(operation=="INSERT")
                    {
                        l++;   
                        treap.TREAP_Insert(stoi(value));
                        // w<<key_comp_treap<<"\n";
                        
                    }
                    if(operation=="DELETE")
                    {
                        l++;   
                        treap.TREAP_Delete(stoi(value));
                        // w<<key_comp_treap<<"\n";
                        
                    }
                    clock_t en =clock();
                    // cout<<operation<<" "<<value<<"\n";
                    ft_treap =+ static_cast<double>(en - st) / CLOCKS_PER_SEC;
                    // cout<<"\n";            
                }
                ///////////////////////////////////////////////////////////////////////
                // cout<<"\n\nEND OF FILE..................."<<l-1;
                // cout<<"\n\n"<<fixed<<setprecision(6)<<setw(12);
                // cout<<ft_bst;
                // cout<<"\n";
                // cout<<ft_treap;

                
            }
            f.close();
            
            f.open(filename, ios::in | ios::out);
            if(!f)cout<<"error";
            else
            {
                // cout<<"\nopen.......................\n";
                //////////// AVL OPERATIONS //////////////////////////////////////////
                l=0;
                clock_t str =clock();
                while (!f.eof())
                {
                    
                    f>>operation;
                    f>>value;

                    if(operation=="INSERT")
                    {
                        l++;
                        avl.AVL_Insert(stoi(value));
                        
                        
                    }
                    if(operation=="DELETE")
                    {
                        l++;
                        avl.AVL_Delete(stoi(value));
                        
                    }
                    clock_t end =clock();
                    ft_avl =+ static_cast<double>(end - str) / CLOCKS_PER_SEC;
                    
                }
                ///////////////////////////////////////////////////////////////////////
                // cout<<"\n\nEND OF FILE..................."<<l-1;
                
                
            }
            f.close();
            
            cout<<"\nRESULTS OF "<<filename<<"---------------------------------------------------------------\n";
            cout<<fixed<<setprecision(6)<<setw(12)<<"\n";
            cout<<"TOTAL OPERATION TIME BST: "<<ft_bst<<"\n";
            cout<<"TOTAL OPERATION TIME TREAP: "<<ft_treap<<"\n";
            cout<<"TOTAL OPERATION TIME AVL: "<<ft_avl<<"\n";
            cout<<"\n\n";
            cout<<"TOTAL ROTATIONS AVL: "<<avl_rotations<<"\n";
            cout<<"TOTAL ROTATIONS TREAP: "<<treap_rotations<<"\n";
            cout<<"\n\n";
            cout<<"TOTAL KEY COMPARISIONS BST: "<<key_comp_bst<<"\n";
            cout<<"TOTAL KEY COMPARISIONS TREAP: "<<key_comp_treap<<"\n";
            cout<<"TOTAL KEY COMPARISIONS AVL: "<<key_comp_avl<<"\n";
            cout<<"\n\n";
            bst_final_height= bst.final_height_bst();
            cout<<"FINAL TREE HEIGHT BST: "<<bst_final_height<<"\n";
            treap_final_height= treap.final_treap_height();
            cout<<"FINAL TREE HEIGHT TREAP: "<<treap_final_height<<"\n";
            avl_final_height =avl.final_height_avl();
            cout<<"FINAL TREE HEIGHT AVL: "<<avl_final_height<<"\n";
            cout<<"\n\n";
            bst.av_bst();
            // cout<<"TOTAL NO OF NODES IN FINAL TREE BST: "<<total_bst_nodes<<"\n";
            cout<<"AVERAGE HEIGHT OF EVERY NODE IN FINAL TREE BST: "<<bst_avg_node_height / total_bst_nodes<<"\n";
            treap.av_treap();
            // cout<<"TOTAL NO OF NODES IN FINAL TREE TREAP: "<<total_treap_nodes<<"\n";
            cout<<"AVERAGE HEIGHT OF EVERY NODE IN FINAL TREE TREAP: "<<treap_avg_node_height / total_treap_nodes<<"\n";
            avl.av_avl();
            // cout<<"TOTAL NO OF NODES IN FINAL TREE AVL: "<<total_avl_nodes<<"\n";
            cout<<"AVERAGE HEIGHT OF EVERY NODE IN FINAL TREE AVL: "<<avl_avg_node_height / total_avl_nodes<<"\n";

            cout<<"------------------------------------------------------------------------------------";


    }//END FOR LOOP FOR 6 TEST FILES..................

system("pause");
    return 0;
}

