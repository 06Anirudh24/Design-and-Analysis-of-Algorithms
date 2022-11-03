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
    TreeNode(){;
    TreeNode(vector<double> point , Line line);
};

double compare(vector <double> p, vector <double> q);
private class EventQueue
{
    TreeNode* root;
    
    public:
    EventQueue();    
    TreeNode* Insert(TreeNode* root, vector<double> point, Line line);
    void insert_line(vector<Line> line);
    void insert(vector<double> point);
    //Left rotation of BST at a node
    TreeNode* leftRotate(TreeNode* z);
    //Right rotation of BST at a node
    TreeNode* rightRotate(TreeNode* z);
    int getHeight(TreeNode* root);
    int getBalance(TreeNode* root);
    void _inOrder(TreeNode* root,, vector<TreeNode*> *result);    
    vector<TreeNode*> inOrder(); 
    void delete(vector<double> point);    
    TreeNode* get_max();    
    TreeNode* pop_next_event();    
    TreeNode* _delete(TreeNode* root, vector<double> key);    
    TreeNode* getMinValueNode(TreeNode* root);
    int is_empty();
   
    
    
    
    
    
    
    
    
    
    
};





