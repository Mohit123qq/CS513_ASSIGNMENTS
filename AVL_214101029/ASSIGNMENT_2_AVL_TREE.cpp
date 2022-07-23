#include <iostream>
#include<fstream>

using namespace std; 


class AVL_Node
{ 
    private:
    
    int key; // value of data inside the node
    
    int bf; // balance factor bf = height(left subtree) – height(right subtree)
    
    AVL_Node *LChild, *RChild; // left child and right child of a node
    
    friend class AVL_Tree; // making class AVL_Tree a friend so that it can use its members


};

class AVL_Tree
{
   private:
     
     AVL_Node *root; // root of the avl tree
     
     fstream f; // file pointer for opening and writing in the file
    
     bool issmaller; // this boolean tells if subtree tree is shortened after deletion
                     // issmaller is true then subtree is shortened
                     // issmaller is false then subtree is remain same in height

     bool istaller ; // this boolean tells if subtree tree height is increased after insertion
                     // istaller is true then subtree is incresed in height
                     // istaller is false then subtree is remain same in height



   
   ///////////////////////////////  ROTAION FUCTIONS  /////////////////////////////////////////////////////////  
     


    void rotateToLeft(AVL_Node* &root)
    {
      // cout<<"\ninto rtl\n";
      AVL_Node *p; //pointer to the root of the right subtree of root
      if (root == NULL) cerr << "Error in the tree" << endl;
      else if (root->RChild == NULL) cerr << "Error in the tree:" <<" No right subtree to rotate." << endl;
      else 
      {
         p = root->RChild;
         root->RChild = p->LChild; //the left subtree of p becomes the right subtree of root
         p->LChild = root;
         root = p; //make p the new root node
      } 
    }

 


    void rotateToRight(AVL_Node* &root) 
    {
      // cout<<"\ninto rtr\n";
      AVL_Node *p; //pointer to the root of the left subtree of root
      if (root == NULL) cerr << "Error in the tree" << endl;
      else if (root->LChild == NULL) cerr << "Error in the tree:" << " No left subtree to rotate." << endl;
      else
      {
        p = root->LChild; 
        root->LChild = p->RChild; //the right subtree of p becomes the left subtree of root
        p->RChild = root;
        root = p; //make p the new root node
      } 
    }//end rotateRight




   //////////////////////////////////  FOR INSERTION PROCESS  //////////////////////////////////////////////////



    void balanceFromLeft(AVL_Node* &root)
    {
      //   cout<<"into bfl\n";
       AVL_Node *p; 
       AVL_Node *w;
       p = root->LChild; //p points to the left subtree of root
       switch (p->bf) 
       { 
           case -1: 
              root->bf = 0; 
              p->bf = 0; 
              rotateToRight(root); 
              break;
           case 0: cerr << "Error: Cannot balance from the left." << endl; 
              break;
           case 1: 
              w = p->RChild; 
              switch (w->bf) //adjust the balance factors 
              {  
               case -1: 
                  root->bf = 1; 
                  p->bf = 0; 
                  break;
               case 0: 
                  root->bf = 0; 
                  p->bf = 0; 
                  break;
               case 1: 
                  root->bf = 0; 
                  p->bf = -1;
              }//end switch
          
            w->bf = 0; 
            rotateToLeft(p); 
            root->LChild = p; 
            rotateToRight(root);
        }//end switch; 
    }//end balanceFromLeft



    void balanceFromRight(AVL_Node* &root) 
    {
      //   cout<<"into bfr\n";
      AVL_Node *p; 
      AVL_Node *w;
      p = root->RChild; //p points to the left subtree of root
      switch (p->bf) 
      {  
          case -1: 
             w = p->LChild; 
             switch (w->bf) //adjust the balance factors 
             {  
                 case -1: 
                    root->bf = 0; 
                    p->bf = 1; 
                    break;
                 case 0:  
                    root->bf = 0; 
                    p->bf = 0;
                    break;
                 case 1: 
                    root->bf = -1; 
                    p->bf = 0;
             }//end switch
            w->bf = 0; 
            rotateToRight(p); 
            root->RChild = p;
            rotateToLeft(root); 
            break;
          case 0: cerr << "Error: Cannot balance from the right." << endl; 
            break;
          case 1: 
            root->bf = 0; 
            p->bf = 0; 
            rotateToLeft(root);
      }//end switch; 
    }//end balanceFromRight



    void insertIntoAVL(AVL_Node * &root, AVL_Node *newNode, bool& istaller)
    {
      //cout<<"into insert imto avl\n";
        if (root == NULL) 
        {
          root = newNode; 
          istaller = true;
        }
        else if (root->key == newNode->key) cerr << "No duplicates are allowed." << endl;
        else if (root->key > newNode->key) //newItem goes in the left subtree
        { 
          insertIntoAVL(root->LChild, newNode, istaller);
          if (istaller) //after insertion, the subtree grew in height
          switch (root->bf) 
          { 
              case -1: 
                 balanceFromLeft(root); //right_rotate
                 istaller = false; 
                 break;
              case 0: 
                  root->bf = -1; //1
                  istaller = true; 
                  break;
              case 1: 
                  root->bf = 0; 
                  istaller = false;
          }//end switch 
        }//end if
       else
        {

          insertIntoAVL(root->RChild, newNode, istaller);
          if (istaller) //after insertion, the subtree grew in //height
          switch (root->bf) 
          { 
              case -1: 
                 root->bf = 0;
                 istaller = false; 
                 break;
              case 0: 
                 root->bf = 1; //-1
                 istaller = true; 
                 break;
              case 1: 
                 balanceFromRight(root); 
                 istaller = false;
          }//end switch 
        }//end else


     }


    

   ////////////////////////////////// FOR SHOWING THE OUTPUT AVL TREE  ////////////////////////////////////////

   void print()
    {

        cout<<"in print\n";
        f.open("AVL_Tree.gv" , ios::in | ios::out ) ;// opening file to write
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
        
      
        system("dot -Tpng AVL_Tree.gv -o AVL_Tree.png");// graphviz command to make png file of output
        
        
        system("AVL_Tree.png");// displays the file
    }

   void preorder(AVL_Node * &root ,fstream &f)
    {
     AVL_Node *ptr;ptr=root; 
    
      if(ptr!=NULL)
       {
          f<<"node";
          f<<ptr -> key;
          f<<"[label = ";
          f<<"\"<L> |<key>";
          f<<ptr -> key;
          f<<"|<bf>";
          f<<(ptr->bf)*(-1);     
          f<<"|<R> \"";
          f<<"];\n";
          preorder(ptr ->LChild , f); 
          preorder(ptr ->RChild , f);
       } 
    }





    void childs(AVL_Node * &root ,fstream &f)
    {
       
     AVL_Node *ptr;ptr=root; 
     
      if(ptr!=NULL)  
       {
         
          if(ptr->LChild)
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
          if(ptr->RChild)
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

     
     
   /////////////////////////////////  FOR DELETION PROCESS  ///////////////////////////////////////////////////////////////// 
     
     
   
   void avl_delete(AVL_Node * &root, int key, bool& issmaller) // do the deletion
    {
      //cout<<"into insert imto avl\n";
        if (root->key != key && root->LChild==NULL && root->RChild==NULL || root==NULL) 
        {
            cerr<< "\nELEMENT NOT FOUND\n";
            return;
        }
        
        if (root->key == key) 
        {
           cout<<"\nDELETING -->"<<key<<"\n";
            if(root->LChild==NULL && root->RChild==NULL)
            {
               // cout<<"\n NO CHILDS\n";
               root=NULL;
            }
            else
            {
                  if(root->RChild==NULL)
                  {
                     // cout<<"\n NO RIGHT CHILD\n";
                     root->key=root->LChild->key;
                     root->bf=0;
                     root->LChild=NULL;
                  }
                  else
                  {
                     if(root->LChild==NULL)
                     {
                     //   cout<<"\n NO LEFT CHILD\n";
                       root->key=root->RChild->key;
                       root->bf=0;
                       root->RChild=NULL;
                     
                     }
                     
                  }
            }

           if(root) 
           if(root->LChild!=NULL && root->RChild!=NULL)
           {
            //   cout<<"\n BOTH CHILD\n";
               AVL_Node* pre = predecessor(root->LChild);
               AVL_Node* parent_of_pred=root->LChild;
               root->key=pre->key;

               if(pre->key == root->LChild->key)
               {
                  // cout<<"\n FROM LEFT\n";

                  root->LChild=root->LChild->LChild;
                  //balanceforLR(root);
                  //root->bf=1;
                  
                  if(root->bf==0)root->bf=1;
                  if(root->bf==-1)root->bf=0;
                  if(root->bf==1)
                  {
                     balanceforLR(root,issmaller);
                  }
               }
               
               else
               {
                  // cout<<"\n FROM PREDECESSOR\n";
                  while (parent_of_pred->RChild!=pre)
                  {
                     
                     parent_of_pred=parent_of_pred->RChild;
                  }
                  if(pre->LChild==NULL)
                  {
                     // cout<<"\n PREDECCESOR LCHILD NULL\n";
                     
                    parent_of_pred->RChild=NULL;
                     if(parent_of_pred->bf==0)
                     {
                        parent_of_pred->bf=-1;
                        issmaller=false;
                     }
                     if(parent_of_pred->bf==1)
                     {
                        parent_of_pred->bf=0;
                        issmaller=true;
                     }
                  }
                  else
                  {
                     // cout<<"\nPREDECESSOR LCHILD NOT NULL\n";
                     pre->key=pre->LChild->key;
                     pre->bf=0;
                     pre->LChild=NULL;
                     
                  }
               }
               
               
           }


        }
        else if (root->key > key) //newItem goes in the left subtree
        { 
          avl_delete(root->LChild, key, issmaller);  ///////from left
         //   cout<<root->key<<" "<<root->bf<<"\n";
          if (issmaller) //after deletion, the subtree decrease in height
            
          switch (root->bf) 
          { 
              case -1: 
                 root->bf=0;
                 issmaller=true;
                 break;
              case 0: 
                 root->bf=1;
                 issmaller=false;
                 break;
              case 1:
               //   issmaller=false;
                 balanceforLR(root ,issmaller); 
                 
                  
          }//end switch 
        }//end if
       else
        {

          avl_delete(root->RChild, key, issmaller);  ///////from right
         //   cout<<root->key<<" "<<root->bf<<"\n";
          if (issmaller) //after deletion, the subtree decrease in height
            
          switch (root->bf) 
          { 
              case -1:
               //   issmaller=false; 
                 balanceforRR(root ,issmaller);
                 
                 break;
              case 0: 
                 root->bf=-1;
                 issmaller=false;
                 break;
              case 1: 
                 root->bf=0;
                 issmaller=true;
          }//end switch 
        }//end else
        

   }// avl_delete() ends...



   AVL_Node* predecessor(AVL_Node* &root) // finds predecessor if node to be deleted
   {
         AVL_Node* p=root;
         if(p==NULL)return NULL;

         while(p->RChild!= NULL)p=p->RChild;

         return p;
   }

    void balanceforLR(AVL_Node* &root , bool& issmaller) // balances the nodes before left rotation
    {
      //  cout<<"\n IN BALANCEFORLR \n";
       AVL_Node *p = root; //root bf =1
       AVL_Node *w = p->RChild; 
      
       switch (w->bf) 
       { 
           case 1: 
            //   cout<<"\n in lr 1\n";
              root->RChild->bf=0;
              root->bf=0;
              rotateToLeft(root);
              issmaller=true;
              break;
           
           
           case 0: 
            //   cout<<"\n in lr 0\n";
            //   if(root->bf != 0)
            //   {
            //       root->RChild->bf=-1;
            //       root->bf=1;
            //       rotateToLeft(root);
            //       if(root->LChild->LChild==NULL && root->LChild->RChild==NULL)
            //          root->LChild->bf=0;
            //   }
            //   cout<<root->key;
              
              issmaller=false;
              break;
           
           
           case -1: 
            //   cout<<"\n in lr -1\n";
            //   balanceforRR(root->RChild,issmaller);
              root->RChild->bf=1;
              root->RChild->LChild->bf=1;
              rotateToRight(root->RChild);
               //   balanceforLR(root,issmaller);
              root->LChild->bf=0;
              root->bf=0;
              rotateToLeft(root);
              issmaller=true;



        }//end switch; 
    }//end balanceforLR


    void balanceforRR(AVL_Node* &root , bool& issmaller) // balances the nodes before right rotation
    {
      // cout<<"\n IN BALANCEFORRR \n";
      AVL_Node *p=root; //root bf = -1
      AVL_Node *w = p->LChild;;
      
      switch (w->bf) 
      {  
          case 1: 
            //  cout<<"\n in rr 1\n";
            //  balanceforLR(root->LChild , issmaller);
             root->LChild->bf=-1;
             root->LChild->RChild->bf=-1;
             rotateToLeft(root->LChild);
               //  balanceforRR(root ,issmaller);
             root->LChild->bf=0;
             root->bf=0;
             rotateToRight(root);
             issmaller=true;
             break;
          
          
          case 0: 
            //  cout<<"\n in rr 0\n";
            //  root->LChild->bf=1;
            //  root->bf=-1;
            //  rotateToRight(root);
            //  if(root->RChild->LChild==NULL && root->RChild->RChild==NULL)
            //     root->RChild->bf=0;
             issmaller=false;
             break;
          
          
          case -1: 
            //  cout<<"\n in rr -1\n";
             root->LChild->bf=0;
             root->bf=0;
             rotateToRight(root);
             issmaller=true;
      
      
      }//end switch; 
    }//end balanceForRR


//////////////////////////////////////////////////////////////////////////////////////////////////

public:


   AVL_Tree()
   {
         root=NULL;
   } 
   
   AVL_Tree(const AVL_Tree &T){} 
   
   AVL_Tree &operator=(const AVL_Tree &T); 



    void AVL_Insert(int k)
     {
      
        istaller = false;// istaller to false so that it can find its new position
        AVL_Node *newNode;
        newNode = new AVL_Node(); //allocating new node
        newNode->key = k; //allocating value of new node
        newNode->bf = 0; //initialising balance factor to 0
        newNode->LChild = NULL; //initialising new node left child null
        newNode->RChild = NULL;//initialising new node right child null
        insertIntoAVL(root, newNode, istaller);// calling for insertion of new node
     }


    void AVL_Delete(int k)
     {
         issmaller=1;// puting issmaler to so that it can backtrack to root node
         avl_delete(root ,k,issmaller);//calling for node deletion
     }
    
    bool AVL_Search(int k)
     {
       AVL_Node *ptr=root;
       while(ptr)
       {
          if(ptr->key==k)return true;// if found the element return true
          else
          { 
             if(ptr->key > k) ptr=ptr->LChild;// if element less than node go to left child
             
             else
             { 
                if(ptr->key < k) ptr=ptr->RChild;// if element more than node go to right child
             }
          }


       }  

        return false; 
     }
     
     
    void AVL_Print(const char *filename)
     {   
        print();// calling to write content in AVL_Tree.gv file
     } 

     ~AVL_Tree(){}


}; // AVL_Tree class ends....






 int main()

 { 
    int key;
    AVL_Tree avl_tree; //MAKING OBJECT
   
    char ch;
    int choice, val;
    
    //////////////// PERFORMING OPERATIONS //////////////////////////
    
    do    
    {
        cout<<"\nAVL_Operations\n";
        cout<<"1. Insert "<<endl;
        cout<<"2. Delete"<<endl;
        cout<<"3. Search"<<endl;
        cout<<"4. Print"<<endl;
        cout<<"\nEnter Your Choice: ";
        cin>>choice;
        switch (choice)
        {
            case 1 :
                cout<<"\nEnter integer element to INSERT: ";
                cin>>key; 
                avl_tree.AVL_Insert(key);                     
                break;    

                                    
            case 2 : 
                cout<<"\nEnter integer element to DELETE: ";
                cin>>key;
                avl_tree.AVL_Delete(key);                     
                break; 


            case 3 : 
                cout<<"Enter integer element to SEARCH: ";
                cin>>key;
                if (avl_tree.AVL_Search(key))
                    cout<<"Element "<<key<<" found in the tree ";
                else
                    cout<<"Element "<<key<<" not found in the tree"<<endl;
                break;

            case 4:
                 // avl_tree.AVL_Print("AVL_Tree.png");
                 cout<<"\n----SHOWING AVL TREE OUTPUT----\n"; 
                 avl_tree.AVL_Print("AVL_Tree.png");
                  break;

            
            default : 
                cout<<"\n WRONG ENTRY \n ";
                break;   
    
        }
    
          cout<<"\nDo you want to continue (Type y or n): ";
          cin>>ch;                       
    } 
    while (ch == 'Y'|| ch == 'y');               
 

  return 0;
 }
