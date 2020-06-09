#include<bits/stdc++.h>
using namespace std;
class node{
  public:
	int data, height, count; 
	node* left; node*right;
};  
 

int height(node* node)
{
  int  height=(node==NULL)? -1 : node->height;	//height of null is -1
  return height;
}

int count(node* node)
{
  int  count=(node==NULL)? 0 : node->count;	 //count of null is 0
  return count;
}

// Get Balance factor of node N  
int balancefn(node *node)  
{  
   int bal=(node==NULL)? 0: height(node->left)-height(node->right);
    return bal;
}  

node *rightrotate(node *grandparent)  
{  
  node *parent=grandparent->left;     
  node *parentright = grandparent->left->right;  //save left child of parent
  grandparent->left->right = grandparent;  //make gp right child of parent
  grandparent->left = parentright;         

  grandparent->count = count(grandparent->left)+ count(grandparent->right)+ 1;
  parent->count = count(parent->left)+ count(parent->right) + 1; 
  
  // parent->height = max(height(parent->left), height(parent->right)) + 1;  
  grandparent->height = max(height(grandparent->left),height(grandparent->right)) + 1;
  parent->height = max(height(parent->left), height(parent->right)) + 1;   //Calculate parent height after grandparent because gp is now child of parent
  
  return parent;
}  

node *leftrotate(node *grandparent)  
{  
  node *parent=grandparent->right;
  node *parentleft = grandparent->right->left;
  grandparent->right->left = grandparent;  //make gp right child of parent
  grandparent->right = parentleft;  

 grandparent->count = count(grandparent->left)+ count(grandparent->right)+ 1;
  parent->count = count(parent->left)+ count(parent->right) + 1; 

  grandparent->height = max(height(grandparent->left),height(grandparent->right)) + 1;
  parent->height = max(height(parent->left), height(parent->right)) + 1;   //Calculate parent height after grandparent because gp is now child of parent
  return parent;   
}   

node *lrrotate(node *grandparent)
{
  grandparent->left = leftrotate(grandparent->left);  //First apply left rotation on parent so it becomes LL case
  return rightrotate(grandparent);            //Height will be adjusted in RR case so no need here        
}  

node *rlrotate(node *grandparent)
  {
  grandparent->right = rightrotate(grandparent->left);  //First apply right rotation on parent so it becomes RR case  
  return leftrotate(grandparent);  
}

node* insert(node *root, int key){
  if(root==NULL){
  	node *root = new node(); 
    root->data = key;
    root->left = NULL; 
    root->right = NULL;
    root->height = 0;   //height of new node is 0
     root->count=1;     //count of new node is 1
    return root;	  
  }
  
  if(key>root->data){
    root->right=insert(root->right,key);  //If equal nodes, insert in right child
  }
  else if(key<root->data){
  	root->left=insert(root->left,key);
  }
  else{
     // Ignore this case because ordered set contain unique elements
  }

int leftheight=(root->left==NULL)? -1 : root->left->height;
int rightheight=(root->right==NULL)? -1 : root->right->height;
root->height=1+max( leftheight , rightheight );  
int diff=(leftheight-rightheight);  // diff will act as balancing factor

int leftcount=(root->left==NULL)? 0 : root->left->count;
int rightcount=(root->right==NULL)? 0 : root->right->count;
root->count=1+leftcount+rightcount;

 if (diff==2)                   //LL or LR case
 {  if(key<root->left->data)  {   
     return rightrotate(root);   //LL case
    }
    else if(key>root->left->data){
       root->left = leftrotate(root->left);  //LR case First left rotate parent then right rotate grandparent  
      return rightrotate(root); 	
    }
  }
  else if(diff==-2)         //RR or RL case
  {
     if(key > root->right->data)  {  
       return leftrotate(root);
     }
     else if(key < root->right->data) {
       root->right = rightrotate(root->right);  
     return leftrotate(root);  //RL
    }
  }    

  // cout<<root->data<<" "<<diff<<" "<<leftheight<<" "<<rightheight<<" "<< root->height<<endl;
  return root;  
}

int ksmall(node* root, int k) 
    {
        int leftcount=count(root->left);
        if(leftcount+1==k) {
        	return root->data;
        }
        else if(leftcount+1>k) {
        	return ksmall(root->left, k);
        }
        else return ksmall(root->right, k-leftcount-1);   //subtract leftcount cz every node in left subtree is smaller and subtract 1 for root
    }

int contains(node* root, int key)
{ if(root==NULL) return -1;
  else if(root->data==key) return 1;
  else if(root->data>key) return contains(root->left, key);
  else  return contains(root->right, key);
}

node* contains2(node* root, int key)
{ if(root==NULL) return NULL;
  else if(root->data==key) return root;
  else if(root->data>key) return contains2(root->left, key);
  else  return contains2(root->right, key);
}

node * predecessor(node* node1)  
{  
    node1=node1->left;
    while (node1->right != NULL){  
        node1 = node1->right;  
    }
    return node1;
}  

node * successor(node* node1)  
{  
    node1=node1->right;
    while (node1->left != NULL){  
        node1 = node1->left;  
    }
    return node1;
}  
  
int closest(node* root, int key)
{
 node* node1=contains2(root, key);
 int n=(successor(node1)->data > predecessor(node1)->data) ? successor(node1)->data :   predecessor(node1)->data;
  return n;
 cout<<successor(node1)->data;

} 

int range(node *root, int low, int high) 
{ 
    if(root==NULL) return 0; 
  
    else if (root->data<=high && root->data>=low) 
         return 1+range(root->left, low, high)+range(root->right, low, high); 
    else if (root->data>high) 
         return range(root->left,low,high); 
    else if(root->data<low)
         return range(root->right,low, high); 
} 
  
node* deletenode(node* root, int key)  
{  
    if(root==NULL)
        {  
        return root;  
        }
    else if(key==root->data)  
        {     
            if(root->left == NULL &&     root->right == NULL){   //no child
               node* temp = root;  
                root = NULL;  
            free(temp);  
            }
            else if(root->left == NULL &&     root->right != NULL)           {  // right child
            node *temp = root->right; 
            *root = *temp;
            free(temp);  
            }
             else if(root->left != NULL &&     root->right == NULL){   //left child
            node *temp = root->left ;  
            *root = *temp; 
            free(temp);  
             }
           else{    //both child
          
            node* temp = successor(root);  
  
            // Copy the inorder successor's  
            // data to this node  
            root->data = temp->data;  
  
            // Delete the inorder successor  
            root->right = deletenode(root->right,  
                                     temp->data);  
             } 
        }
   else if ( key > root->data )  
   {   root->right = deletenode(root->right, key); 
   }
    
    else 
    {    root->left = deletenode(root->left, key); 
    }

     if (root == NULL)  
    return root;  

    int leftheight=(root->left==NULL)? -1 : root->left->height;
    int rightheight=(root->right==NULL)? -1 : root->right->height;
    root->height=1+max( leftheight , rightheight );  
    int balance=(leftheight-rightheight); 
   
    if (balance ==2) {     //LL or LR 
        if( balancefn(root->left) >= 0)    //LL  
          return rightrotate(root);  
  
        else   
        {  
          root->left = leftrotate(root->left);      //LR
           return rightrotate(root);  
        }  
  }
    
    else if (balance == -2){      //RR
        if(balancefn(root->right) <= 0)  
           return leftrotate(root);  
   
        else        //RL
        {  
          root->right = rightrotate(root->right);  
          return leftrotate(root);  
         }
    }  
    return root;  
}  
  

void preorder(node *root)  
{  
    if(root!=NULL)  
    {  
        cout << root->data << " ";  
        preorder(root->left);  
        preorder(root->right);  
    }  
}  

int main(){
node *root =NULL;

	//Operation: insert
	root = insert(root, 1); 
	root = insert(root, 2);  
	root = insert(root, 3);  
	root = insert(root, 4);
	root = insert(root, 5);  
	root = insert(root, 6);  
	preorder(root);	cout<<endl;

	//Operation: delete
	root = deletenode(root,3);  
    preorder(root);	cout<<endl;

    //Operation: contains
    cout<<contains(root,10)<<endl;

    //Operation: kth smallest element
    cout<<ksmall(root,5)<<endl;

    //Operation: No. of elements in specified range
    cout<<range(root, 1,4)<<endl;
	return 0;
}