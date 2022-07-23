#include <iostream>

using namespace std; 

/////////////  CLASS FOR SINGLE LINKED LIST  ///////////////////////
class ll  
{
  int d; // d=data inside node
  ll* next; // next ,pointer to next node
  friend class threaded_bst; //MAKING FRIEND WITH B FOR USING MEMBERS
};
/////////////////////////////////////////////////////////////////////
 

 ///////////   CLASS FOR THREADED BST  /////////////////////////////
 class threaded_bst
    {
      ///////////// PRIVATE MEMBERS  ///////////////////////////////
      int v,rcount; //v= value of a node,rcount = count of size of right subtree
      threaded_bst *l,*r; //l= left pointer of node ,r= right pointer of node
      bool rt , lt;//rt= right thread of node 1 if filled, lt=left thread of node 1 if filled
      threaded_bst* p; //p=parent of node;
      //////////////////////////////////////////////////////////////
     
     ////////////// PUBLIC MEMBER FUCTIONS /////////////////////////
      public:
      
      threaded_bst() //CONSTRUCTOR FOR INITIALISATION
      {
        v=0;
        rcount=0;
        l=r=NULL;
        rt=lt=0;
        p=NULL;
      } 

      threaded_bst* newnode(int v, threaded_bst* pa)  // MAKING NEW NODE 
      {
        //cout<<"\nin new node\n";
        threaded_bst* node = new threaded_bst;
        node->v=v;
        node->l=node->r=NULL;
        node->rt=node->lt=0;
        node->p=pa;
        //cout<<"\ndone\n";
        return node;
      }

      void insert (threaded_bst*& root)  // 1.INSERT FUNCTION
      {
         
          int n; //NO OF ELEMENTS TO INSERT
          cout<<"How many elements you want to insert:";
          cin>>n;
          for (int i = 1; i <= n; i++)
          {
            int e;
            cin>>e;
            if(!root)
            {
              //cout<<"\nit is  emoty inserting:"<<i<<"\n";
              root = newnode(e,NULL);

            }
            else
            {
              //cout<<"\nit is not emoty inserting:"<<i<<"\n";
                threaded_bst *curr = root;
             
                threaded_bst *parent = NULL;

                //b *gpr = NULL;

                while (curr)
                  {
                     
                      parent = curr; 
                      if (e < curr->v) 
                      {
                          if (!curr->lt) break;
                          curr = curr->l;
                      }
                      else 
                      {
                        if(e > curr->v)
                        {
                          if (!curr->rt) break;
                          
                          curr = curr->r;
                        }
                          
                        else
                         { 
                           cout<<"THIS ELEMENT IS ATREADY PRESENT !!!";
                           return;
                         }
                      }
                      
                  }
                  // construct a node and assign it to the appropriate parent pointer
                  if (e < parent->v) 
                  {
                     threaded_bst* tmp=newnode(e,parent);
                     // parent->l = newnode(e,parent);
                      tmp->l = parent->l;
                      tmp->r = parent;
                      parent->lt=1;
                      parent->l = tmp;
                     
                  }
                  else 
                  {
                    threaded_bst* tmp=newnode(e,parent);
                     //parent->r = newnode(e,1,parent);
                      tmp->l = parent;
                      tmp->r = parent->r;
                      parent->rt=1;
                      parent->r = tmp;
                      

                     
                  }
              }
                
          }
         
      }//insert function ends
      
    
        threaded_bst* inos(threaded_bst* ptr)   // RETURNING INORDER SUCCESSOR REFERRENCE
        {
          if(ptr->rt==0)return ptr->r;

          ptr=ptr->r;
          while(ptr->lt)ptr=ptr->l;
          return ptr;
        }

        int successor(int ele ,threaded_bst * root)   // RETURNING INORDER SUCCESSOR  VALUE
        {
          threaded_bst *a;
          a=search(root,ele);
          threaded_bst *ptr;
          ptr=a;
          if(ptr->rt==0)return ptr->v;

          ptr=ptr->r;
          while(ptr->lt)ptr=ptr->l;
          return ptr->v;
        }
        
        threaded_bst* inop(threaded_bst* ptr)   // RETURNING INORDER PREDECESSOR REFERRENCE
        {
          if(ptr->lt==0)return ptr->l;

          ptr=ptr->l;
          while(ptr->rt)ptr=ptr->r;
          return ptr;
        }


        threaded_bst* lm(threaded_bst* root)  // RETURNING LEFTMOST ELEMENT REFERENCE
        {
          if(root->l==NULL)return root;
          threaded_bst *ptr=root;
          while(ptr->lt)ptr=ptr->l;
          return ptr;
        }
        
        threaded_bst* rm(threaded_bst* root)   // RETURNING RIGHTMOST ELEMENT REFERENCE
        {
          if(root->r==NULL)return root;
          threaded_bst*ptr=root;
          while(ptr->rt)ptr=ptr->r;
          return ptr;
        }
        



        void printtree(threaded_bst* root)   // INORDER TRAVERSE THE TREE AND PRINTING THE VALUES
        {
          threaded_bst a;
          if(!root)
          {
            cout<<"\nteree is empty\n";
            return;
          }
          threaded_bst* ptr =root;
          while(ptr->lt){ptr=ptr->l;}
          
          while(ptr)
          {
            cout<<ptr->v<<" ";//<<" "<<ptr->lt<<" "<<ptr->rt<<"\n";

            ptr=inos(ptr);
          }
          
        }

        void reverseinorder(threaded_bst* root)  // TRAVERSE INORDER IN REVERSE AND PRINTING VALUES
        {
          if(!root)
          {
            cout<<"\nteree is empty\n";
            return;
          }
          threaded_bst* ptr =root;
          while(ptr->rt)
          {
           
            ptr=ptr->r;
           
          }
          
          while(ptr)
          {
           
            cout<<ptr->v<<" ";
           
            
             if(ptr->lt==0)
             {ptr= ptr->l;}
             else
             {
               ptr=ptr->l;
               while(ptr->rt){ptr=ptr->r;}
             }

            
          }

        }

       


        threaded_bst* search(threaded_bst* root ,int k)  //SEARCH THE GIVEN ELEMENT AND RETURN THE REFRENCE
        {
          threaded_bst* tmp=root;
          if(root->v == k)return root;
          while(1)
          {
            if (tmp->v < k) 
                {
                    if (!tmp->rt) 
                        return NULL;
                    tmp = tmp->r;
                } 
                else if (tmp->v > k) 
                {
                    if (!tmp->lt) 
                        return NULL;
                    tmp = tmp->l;
                } 
                else 
                {
                    return tmp;
                }
          }
        }


        ll* allelementsbet(int j, int k ,threaded_bst* root) //FINDING ELEMENT BETWEEN K1 AND K2 AND SAVING IT IN SINGLE LINKED LIST
        {
          threaded_bst *x,*y,*ptr;
          threaded_bst a;
          x=a.search(root,j);
          y=a.search(root,k);
          //cout<<x->v<<" "<<y->v;
          ll *sl =new ll, *h;
          ptr=x;
          sl->d=ptr->v;
          sl->next=NULL;
          h=sl;
          //cout<<x->v<<" ";
          while(ptr!=y)
          {
           // cout<<" hmm";
           
            //cout<<ptr->v<<" ";
             if(ptr->rt==0)
             {ptr= ptr->r;}
             else
             {
               ptr=ptr->r;
               while(ptr->lt)ptr=ptr->l;
             }
            ll* temp=new ll;
            temp->d=ptr->v;
            temp->next=NULL;
            sl->next=temp;
            sl=sl->next;
            //cout<<ptr->v<<" ";            
          }
          
        printll(h);
        } 

        void printll(ll * h) //PRINTING THE LINKED LIST
        {
          ll *ys=h;
          while(ys)
          {
            cout<<ys->d<<" ";
            ys=ys->next;           
          }
        }
        
        void split(int k, threaded_bst* root) //SPLITING THE TREE AND PRINTING THOSE SLITED TREES
        {
            threaded_bst a;
            threaded_bst *node=a.search(root ,k), *nr,*isnl,*iisnl,*rootl,*rootr,*root1,*root2,*lmm,*rmm;
            cout<<"\n split \n ";
            //cout<<node->v;
           
           //cout<<inos(root)->v;
            root1=root;
            if(node==lm(root) || node==rm(root)){cout<<"\n THIS IS ALREADY TREE \n ";return;}
            isnl=inos(node)->l;
            if(inos(node)==rm(root))
            {
              root2=inos(node); 
              printtree(root1);
              cout<<"\n";
              printtree(root2); 
              return;
            }//cout<<root2->v;
            
            if(inop(node)==lm(root))
            {
              root2=inop(node);
              inos(inos(node))->l=inos(node);
              node->r=NULL;
              node->rt=node->lt=0;
              printtree(root1);
              cout<<"\n";
              printtree(root2);
              return;
            }
            
            if(root->v > node->v)//NODE < ROOT
            {root2=root->l;rootl=root->l;root->l=inop(root);}
            
            if(root->v < node->v && inos(node)!=rm(root))  // NODE > ROOT
            {root2=root->r;rootr=root->r;root->r=inos(root);root2->lt=root2->rt=0;}
            
            if(root->v == node->v)//NODE = ROOT
            {root1=root->l;root2=root->r;root2=root->r;}
            
            //if(inos(node)->l->v <= node->v){inos(node)->l=NULL;} 

            //inos(inos(node))->l=inos(node);
           // cout<<node->r->v;
            node->r=NULL;
            node->rt=node->lt=0;
            

            cout<<"\n\n";
           cout<<"root1="<<root1->v;
              //a.printtree(root1);
            cout<<"\n";
            cout<<"root2="<<root2->v;
            //cout<<root2->v;
           // node->r=NULL; 
            cout<<"\n";
           //a.printtree(root2);
           
          //cout<<rm(root2)->lt;

          //for root done

        }

        void Delete(int key,threaded_bst* root)  //DELETING THE GIVEN NODE FROM THE TREE
        {
          //cout<<"\nin delete\n ";
            threaded_bst *dest = root, *p = root;
            while(1)
            {
                if (dest->v < key) 
                {
                    if (!dest->rt) 
                        return; 
                    p = dest;
                    dest = dest->r;
                } 
                else if (dest->v > key) 
                {
                    
                    if (!dest->lt) 
                        return; 
                    p = dest;
                    dest = dest->l;
                }
                else 
                {
                    
                    break; 
                }
            }
            threaded_bst *target = dest;
            if (dest->rt && dest->lt) 
            { 
                
                p = dest;
                
                target = dest->l;
                while (target->rt) 
                {
                    p = target;
                    target = target->r;
                }
                
                dest->v = target->v; 
            }
            if (p->v >= target->v) 
            {
                if (!target->rt && !target->lt) 
                {
                    p->l = target->l;
                    p->lt = 0;
                } 
                else if (target->rt) 
                {
                    threaded_bst *largest = target->l;
                    while (largest->rt)
                    {
                        largest = largest->r;
                    }
                    largest->r = p;
                    p->l = target->l;
                }
                else 
                {
                    threaded_bst *smallest = target->r;
                    while (smallest->lt) 
                    {
                        smallest = smallest->l;
                    }
                    smallest->l = target->l;
                    p->l = target->r;
                }
            } 
            else 
            {
                if (!target->rt && !target->lt) 
                {
                    p->r = target->r;
                    p->rt = 0;
                }
                else if (!target->rt) 
                {
                    threaded_bst *largest = target->l;
                    while (largest->rt) 
                    {
                        largest = largest->r;
                    }
                    largest->r =  target->r;
                    p->r = target->l;
                } 
                else 
                {
                    threaded_bst *smallest = target->r;
                    while (smallest->lt)
                    {
                        smallest = smallest->l;
                    }
                    smallest->l = p;
                    p->r = target->r;
                }
            }
            //cout<<"out of delete\n";
        }

        int kthelement(int k ,threaded_bst* root)
        {
         
          threaded_bst* ptr=root; 
          while(ptr->rt)ptr=ptr->r;
        
            while(k--)
            {
              
              if(ptr->lt==0)
              {ptr= ptr->l;}
              else
              {
                ptr=ptr->l;
                while(ptr->rt){ptr=ptr->r;}
              }
              if(k==1)return ptr->v;
            
          }

        }

    
    };    //CLASS ENDS....




 int main()

 {
    
    
    threaded_bst Threaded_BST; //MAKING OBJECT
    threaded_bst *root=NULL;//MAKING A ROOT
    char ch;
    int choice, val;
    //////////////// PERFORMING OPERATIONS //////////////////////////
    do    
    {
        cout<<"\nThreaded_BinarySearchTree_Operations\n";
        cout<<"1. Insert "<<endl;
        cout<<"2. Delete"<<endl;
        cout<<"3. Search"<<endl;
        cout<<"4. Reverse Inoder"<<endl;
        cout<<"5. Successor"<<endl;
        cout<<"6. Split"<<endl;
        cout<<"7. All Elements Between"<<endl;
        cout<<"8. Kth Largest Element"<<endl;
        cout<<"9. Print tree"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>choice;
        switch (choice)
        {
            case 1 : 
                Threaded_BST.insert(root);                     
                break;    

                                    
            case 2 : 
                cout<<"Enter integer element to delete: ";
                cin>>val;
                Threaded_BST.Delete(val,root);                     
                break; 


            case 3 : 
                cout<<"Enter integer element to search: ";
                cin>>val;
                if (Threaded_BST.search(root,val))
                    cout<<"Element "<<val<<" found in the tree and its REFERENCE IS :"<<Threaded_BST.search(root,val)<<endl;
                else
                    cout<<"Element "<<val<<" not found in the tree"<<endl;
                break;

            case 4:
                  cout<<"\nPRINTING REVERSE INORDER\n";
                  Threaded_BST.reverseinorder(root);
                  break;

            case 5:
                  cout<<"\nPRINTING INORDER SUCCESSOR\n";
                  cout<<"ENTER THE ELEMENT :";
                  int element;cin>>element;
                  cout<<"\nINORDER SUCCESSOR IS=\n"<<Threaded_BST.successor(element,root);
                  break;

            case 6:
                  cout<<"\nSPLITING THE TREE\n";
                  cout<<"ENTER K :";
                  int K;cin>>K;
                  Threaded_BST.split(K,root);
                  break;

            case 7:
                  cout<<"\nPRINTING ALL ELEMENTS BETWEEN K1 AND K2 (K1 ,K2 INCLUDED)\n";
                  int k1,k2;
                  cout<<"ENTER K1 ";cin>>k1;
                  cout<<"\nENTER K2 ";cin>>k2;
                  Threaded_BST.allelementsbet(k1,k2,root);
                  break;

            case 8:
                  cout<<"\nPRINTING Kth LARGEST ELEMENT\n";
                  int k;
                  cout<<"\nENTER K ";cin>>k;
                  cout<<"\nKth LARGEST ELEMENT IS :"<<Threaded_BST.kthelement(k,root);
                  break;

            case 9:
                  cout<<"\nPRINTING TREE USING GRAPHVIZ\n";
                  Threaded_BST.printtree(root);
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
