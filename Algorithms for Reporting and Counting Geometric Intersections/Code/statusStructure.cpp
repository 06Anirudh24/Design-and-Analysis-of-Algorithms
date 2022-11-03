#include<stdlib.h>
#include<iostream>
#include "line.h"
using namespace std;
struct TreeNodeStatus{
    Line line;
    TreeNodeStatus* left;
    TreeNodeStatus* right;
    int height;
    public: 
    TreeNodeStatus(){
        this.line = Line() ; //check
        this.left = NULL ;
        this.right = NULL ;
        this.height = 1 ;

    }
    TreeNodeStatus(Line line){
        this.line = line ; //check
        this.left = NULL ;
        this.right = NULL ;
        this.height = 1 ;
    }
   
    void copy(TreeNodeStatus* node){
        this.line.Line(node->line.upper_endpoint , node->line.lower_endpoint)   ; // check
        this.left = node->left;
        this.right = node->right;
        this.height = node->height ;
    }
};
private class StatusStructure{
    TreeNodeStatus* root ;
    public:
    StatusStructure(){
        this->root = NULL ;
    }
    TreeNodeStatus* Insert(TreeNodeStatus* root, vector<double> point , Line line){
        if(root == NULL) return new TreeNodeStatus(line) ;
        else if (root->line.compare_lower(point, line) > 0){
            root -> left = this.Insert(root->left, point, line) ;
        } 
        else{
            root-> right = this.Insert(root->right, point, line) ;
        }
        root->height = 1 + max(this.getHeight(root->left), this.getHeight(root->right)) ;
        int balance = this.getBalance(root) ;
        if(balance > 1 && root->line.compare_lower(point, line) > 0){
            return this.rightRotate(root) ;
        }
        if(balance < -1 && root->line.compare_lower(point, line) < 0){
            return this.leftRotate(root) ;
        }
        if(balance > 1 && root->line.compare_lower(point, line) < 0){
            root->left =  this.rightRotate(root->left) ;
            return this.rightRotate(root) ;
        }
        if(balance <-1 && root->line.compare_lower(point,line) >0 ){
            root -> right = this.rightRotate(root->right) ;
            return this.leftRotate(root) ;
        }
        return root ;
    }
    void insert(vector<double> point, vector<Line> lines){
        for(int i = 0 ; i < lines.size() ; i++){
            this -> root = this.Insert(this-> root , point , lines[i]) ;
        }
       
    }
    void _print_name(){
        vector<TreeNodeStatus*> temp = this.inOrder() ;
        printf("\n") ;
        for(int i = 0 ; i < temp.size() ; i++){
            cout <<"Line number" << temp[i].line.name<< "points ("<< temp[i].line.upper_endpoint << " , " << temp[i].line.lower_endpoint << ")\n" ,  ; 
        } 
        
    }
    
        // done till line 54 of the github code of status Structure
    TreeNodeStatus* leftRotate(TreeNodeStatus* z){
        TreeNodeStatus* y = z->right ;
        TreeNodeStatus* temp = y->left ;
        y -> left = z ;
        z -> right = temp ;
        z -> height = 1 + max(this.getHeight(z->left) , this.getHeight(z->right)) ;
        y -> height = 1 + max(this.getHeight(y->left) , this.getHeight(y->right)) ;
        return y ;

    }
        // 64 done
    TreeNodeStatus* rightRotate(TreeNodeStatus* z){
        TreeNodeStatus* y = z->left ;
        TreeNodeStatus* temp = y->right ;
        y -> right = z ;
        z -> left = temp ;
        z -> height = 1 + max(this.getHeight(z->left) , this.getHeight(z->right)) ;
        y -> height = 1 + max(this.getHeight(y->left) , this.getHeight(y->right)) ;
        return y ;

    }
    //76 done
    int getHeight(TreeNodeStatus* root){
        if(root == NULL)return 0 ;
        return root -> height ;
    }
    int getBalance(TreeNodeStatus* root ){
        if(root == NULL)return 0 ;
        return this.getHeight(root->left) - this.getHeight(root-> right) ;
    }
    //86 done
    void InOrderTree(TreeNodeStatus* root, vector<TreeNodeStatus*> *result){
        if(root == NULL)return ;
        this.InOrderTree(root -> left , result) ;
        *result.push_back(root) ;
        this.InOrderTree(root -> right, result) ;
    }
    vector<TreeNodeStatus*> inOrder(){
        vector<TreeNodeStatus*> result ;
        this.InOrderTree(this.root, &result) ;
        return result ;
    }
    void deleteLine(vector<double> point, Line line){
        this.root = this.deletePoint(this.root,point, line) ;
    }
    void deleteLines(vector<double> point , vector<Line> lines) {
        for(int i = 0 ; i < lines.size() ; i++){
            this.deleteLine(point, lines[i]) ;
        }
    }
    TreeNodeStatus* deletePoint(TreeNodeStatus* root, vector<double> point, Line line){
        if(root == NULL){
            return root ;
        }
        else if(root -> line.compare_upper(point, line) > 0){
            root -> left = this.deletePoint(root->left,point, line) ;
        }
        else if(root-> line.compare_upper(point,line) < 0){
            root -> right = this.deletePoint(root -> right, point, line) ;
        }
        else{
            TreeNodeStatus* temp ;
            if(root -> left == NULL){
                temp = root -> right ;
                root = NULL ;
                return temp ;
            }
            else if(root -> right == NULL){
                temp = root -> left ;
                root = NULL ;
                return temp ;
            }
            temp = this.getMinimumValueOfNode(root->right) ;
            root -> line  = temp -> line ;
            root-> right = this.deletePoint(root -> right, point, temp -> line);
        }

        if(root == NULL)return root ;
        root->height = 1 + max(this.getHeight(root->left) , this.getHeight(root -> right)) ;
        int balance = this.getBalance(root) ;
        if(balance > 1 && this.getBalance(root -> left) >= 0){
            return this.rightRotate(root) ;
        }
        if(balance < -1 && this.getBalance(root -> right) <= 0){
            return this.leftRotate(root) ;
        }
        if(balance > 1 && this.getBalance(root -> left) < 0){
            root->left =  this.rightRotate(root->left) ;
            return this.rightRotate(root) ;
        }
        if(balance <-1 && this.getBalance(root -> right) >0 ){
            root -> right = this.rightRotate(root->right) ;
            return this.leftRotate(root) ;
        }
        return root ;
    }
    TreeNodeStatus* getMinimumValueOfNode(TreeNodeStatus* root ){
        if(root == NULL || root-> left == NULL)return root ;
        return this.getMinimumValueOfNode(root -> left) ;
    }
    //149 done
    vector<vector<Line>> findSegmentsContain(vector<double> point){
        vector<Line> L ,C, LC ; 
        this.findSegments(this.root, point, &L, &C, &LC) ;
        vector<vector<Line>> temp ;
        temp.push_back(L) ;
        temp.push_back(C) ;
        temp.push_back(LC) ;
        return temp ;
    }
    void findSegments(TreeNodeStatus* root , vector<double> point ,  vector<Line> *L , vector<Line> *C , vector<Line> *LC ){
        if(root == NULL) return ;
        else if(root -> line.point_location(point) > 0 ){
            this.findSegments(root->right , point , L , C, LC) ;
        }
        else if(root -> line.point_location(point) < 0 ){
            this.findSegments(root->left , point , L , C, LC) ;
        }
        else{
            if(root -> left != NULL){
                this.findSegments(root -> left , point, L,C ,LC) ; 
            }
            if(root -> line.lower_endpoint[0] == point[0] && root-> line.lower_endpoint[1] == point[1] ){
                *L.push_back(root -> line) ;
            }
            else{
                *C.push_back(root-> line) ;
            }
            *LC.push_back(root -> line) ;
            if(root -> right != NULL){
                this.findSegments(root->right, point, L, C, LC) ;
            }
        }
    }
    Line findLeftNeighbour(vector<double> point){
        TreeNodeStatus* leftneighbour = NULL ;
        this.findLeft(this.root , point , &leftneighbour) ;
        return leftneighnour -> line ;

    }
    Line findRightNeighbour(vector<double> point){
        TreeNodeStatus* rightneighbour = NULL ;
        this.findRight(this.root, point, &rightneighbour) ;
        return rightneighbour -> line ;
    }
    void findLeft(TreeNodeStatus* root, vector<double> point, TreeNodeStatus **leftneighbour){
        if(root == NULL)return ;
        if(root -> line.point_location(point) > 0 ){
            *leftneigbour = new TreeNodeStatus() ;
            *leftneighour.copy(root) ;
            this.findLeft(root->right, point , leftneigbour) ;
        }
        else if (root -> line.point_location(point) <= 0){
            this.findLeft(root -> left, point, leftneighbour) ;
        }
    }
    void findRight(TreeNodeStatus* root, vector<double> point, TreeNodeStatus **rightneighbour){
        if(root == NULL)return ;
        if(root -> line.point_location(point) >= 0 ){
            
            this.findRight(root->right, point , rightneigbour) ;
        }
        else if (root -> line.point_location(point) < 0){
            *rightneigbour = new TreeNodeStatus() ;
            *rightneighour.copy(root) ;
            this.findRight(root -> left, point, rightneighbour) ;
        }
    }
    Line findLeftMost(vector<double> point){
        TreeNodeStatus* leftmost = NULL ;
        this.findLeftMost(this.root , point, &leftmost ) ;
        return leftmost -> line ;
    }
    Line findRightMost(vector<double> point){
        TreeNodeStatus* rightmost = NULL ;
        this.findLeftMost(this.root , point, &rightmost ) ;
        return rightmost -> line ;
    }
    void findLeftMostNode(TreeNodeStatus* root , vector<double> point, TreeNodeStatus **leftmost){
        if(root == NULL) return ;
        if(root -> line.point_location(point) > 0){
            this.findLeftMostMode(root -> right , point, leftmost) ;
        }
        else if(root -> line.point_location(point) < 0){
            this.findLeftMostMode(root -> left , point, leftmost) ;
        }
        else {
             this.findLeftMostMode(root -> right , point, leftmost) ;
             *leftmost = new TreeNodeStatus() ;
             *leftmost.copy(root) ;
             this.findLeftMostMode(root -> left , point, leftmost) ;

        }
    }
    void findRightMostNode(TreeNodeStatus* root , vector<double> point, TreeNodeStatus **rightmost){
        if(root == NULL) return ;
        if(root -> line.point_location(point) > 0){
            this.findRightMostMode(root -> right , point, rightmost) ;
        }
        else if(root -> line.point_location(point) < 0){
            this.findRightMostMode(root -> left , point, rightmost) ;
        }
        else {
             this.findRightMostMode(root -> left , point, rightmost) ;
             *rightmost = new TreeNodeStatus() ;
             *rightmost.copy(root) ;
             this.findRightMostMode(root -> right , point, rightmost) ;

        }
    }
    // do wewrite the main function?

};