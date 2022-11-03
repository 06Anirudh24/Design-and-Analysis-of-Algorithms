#include "line.h"
#include<stdlib.h>
#include<iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    vector<double> point;
    //Line line;
    vector<Line> lines;
    TreeNode* left;
    TreeNode* right;
    int height;
    public: 
    TreeNode(){

        this.lines.resize(0) ; //check
        this.left = NULL ;
        this.right = NULL ;
        this.height = 1 ;

    }
    TreeNode(vector<double> point , Line line){
        this.point[0] = point[0];
        this.point[1] = point[1] ; 
        
        if(line.upper_endpoint.size() != 0)this.lines.push_back(line) ;
        else this.lines.resize(0) ;
        this.left = NULL ;
        this.right = NULL ;
        this.height = 1 ;
    }
    
};

double compare(vector <double> p, vector <double> q)
{
    double px = p[0];
    double py = p[1];
    double qx = q[0];
    double qy = q[1];
    if(py!=qy)
        return py-qy;
    else
        return qx-px; //Points have same y coordinate 
}

private class EventQueue
{
    TreeNode* root;
    
    public:
    EventQueue()
    {
        this->root = NULL;
    }
    
    TreeNode* Insert(TreeNode* root, vector<double> point, Line line)//null shouldn't come here
    {
        if(root == NULL) 
            return new TreeNode(point, line);
        
        else if (compare(point, root->point)<0)
        {
            root->left = this.Insert(root->left, point, line);
        }
        else if (compare(point, root->point)>0)
        {
            root->right= this.Insert(root->right, point, line);
        }
        else
        {
            if(line.upper_endpoint.size() != 0)
                root->lines.push_back(line);
            return root;
        }
            
        root->height = 1 + max(this.getHeight(root->left), this.getHeight(root->right));
        int balance = this.getBalance(root);    
            
        if(balance>1 && compare(point, root->point)<0)
        {
            return this.rightRotate(root);
        }
        if(balance<-1 && compare(point, root->point)>0)
        {
            return this.leftRotate(root);
        }
        if(balance>1 && compare(point, root->point)>0)
        {
            root->left =  this.rightRotate(root->left);
            return this.rightRotate(root);
        }
        if(balance<-1 && compare(point, root->point)<0 )
        {
            root -> right = this.rightRotate(root->right);
            return this.leftRotate(root);
        }
        return root;
    }
    
   
    void insert_line(Line line)
    {
        upper_end = line->upper_endpoint ;
        lower_end = line->lower_endpoint ;
        this.root = this.Insert(this.root, upper_end, line) ;
        Line temp; 
        this.root = this.Insert(this.root, lower_end, temp) ;
    }
    
    
    void insert(vector<double> point)
    {
        Line temp; 
        this.root = this.Insert(this.root, point, temp);
    }
    
    
    //Left rotation of BST at a node
    TreeNode* leftRotate(TreeNode* z)
    {
            TreeNode* y = z->right;
            TreeNode* temp = y->left;
            y->left = z;
            z->right = temp;
            z->height = 1+max(this.getHeight(z->left), this.getHeight(z->right));
            y->height = 1+max(this.getHeight(y->left), this.getHeight(y->right));
            return y;
    }
    //Right rotation of BST at a node
    TreeNode* rightRotate(TreeNode* z)
    {
            TreeNode* y = z->left;
            TreeNode* temp = y->right;
            y->right = z;
            z->left = temp;
            z->height = 1+max(this.getHeight(z->left), this.getHeight(z->right));
            y->height = 1+max(this.getHeight(y->left), this.getHeight(y->right));
            return y;
    }
    
    int getHeight(TreeNode* root)
    {
        if(root==NULL)
            return 0;
        return root->height;
    }
    
    int getBalance(TreeNode* root) 
    {
        if(root==NULL)
            return 0;
        return this.getHeight(root->left)-this.getHeight(root->right);
    }
    
    void _inOrder(TreeNode* root,, vector<TreeNode*> *result) 
    {
        if(root==NULL)
            return;
        this._inOrder(root->left, result);
        *result.push_back(root);
        this._inOrder(root->right, result);
    }
    
    vector<TreeNode*> inOrder()
    {
        vector<TreeNode*> result;
        this._inOrder(this.root, &result);
        return result;
    }
        
    void delete(vector<double> point)
    {
        this.root = this._delete(this.root, point);
    }
    
    
    TreeNode* get_max()
    {
        TreeNode* current = this.root;
        while(current->right != NULL)
            current = current->right;
        return current;  
    }
    
    TreeNode* pop_next_event()
    {
        TreeNode* current = this.get_max();
        this.delete(current->point);
        return current;
    }
    
    
    TreeNode* _delete(TreeNode* root, vector<double> key)
    {
        if(root == NULL)
            return root;
        else if (compare(key, root->point)<0)
            root->left = this._delete(root->left, key);
        else if (compare(key, root->point)>0)
            root->right = this._delete(root->right, key);
        else
        {
            if(root->left == NULL)
            {
                TreeNode* temp = root->right; 
                root = NULL;
                return temp;
            }
            else if(root->right == NULL)
            {
                TreeNode* temp = root->left;
                root = NULL;
                return temp;
            }
            
            TreeNode* temp = this.getMinValueNode(root->right);
            root->point = temp->point;
            root->lines = temp->lines;
            root->right = this._delete(root->right, temp->point);
        }
        
        if(root == NULL)
            return root;
            
        root->height = 1+max(this.getHeight(root->left), this.getHeight(root->right));
        int balance = this.getBalance(root);
        
        if(balance>1 && this.getBalance(root->left)>=0)
            return this.rightRotate(root);
        if(balance<-1 && this.getBalance(root->right)<=0)
            return this.leftRotate(root);
        if(balance>1 && this.getBalance(root->left)<0)
        {
            root->left = this.leftRotate(root->left);
            return this.rightRotate(root);
        }
        if(balance<-1 && this.getBalance(root->right)>0)
        {
            root->right = this.rightRotate(root->right);
            return this.leftRotate(root);
        }
        return root;
    }
    
    
    TreeNode* getMinValueNode(TreeNode* root)
    {
        if(root==NULL || root->left==NULL)
            return root;
        return this.getMinValueNode(root->left);
    }
    
    int is_empty()
    {
        if(this.root == NULL)
            return 1;
        else 
            return 0;
    }
    
    
    
    
    
    
    
    
    
    
};





