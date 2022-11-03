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
    TreeNodeStatus();
    TreeNodeStatus(Line line);
    void copy(TreeNodeStatus* node);
};
private class StatusStructure{
    TreeNodeStatus* root ;
    public:
    StatusStructure();
    TreeNodeStatus* Insert(TreeNodeStatus* root, vector<double> point , Line line);
    void insert(vector<double> point, vector<Line> lines);
    TreeNodeStatus* leftRotate(TreeNodeStatus* z);
    TreeNodeStatus* rightRotate(TreeNodeStatus* z);
    int getHeight(TreeNodeStatus* root);
    int getBalance(TreeNodeStatus* root );
    void _print_name() ;
    //86 done
    void InOrderTree(TreeNodeStatus* root, vector<TreeNodeStatus*> *result);
    vector<TreeNodeStatus*> inOrder();
    void deleteLine(vector<double> point, Line line);
    void deleteLines(vector<double> point , vector<Line> lines) ;
    TreeNodeStatus* deletePoint(TreeNodeStatus* root, vector<double> point, Line line);
    TreeNodeStatus* getMinimumValueOfNode(TreeNodeStatus* root );
    vector<vector<Line>> findSegmentsContain(vector<double> point);
    void findSegments(TreeNodeStatus* root , vector<double> point ,  vector<Line> *L , vector<Line> *C , vector<Line> *LC );
    Line findLeftNeighbour(vector<double> point);
    Line findRightNeighbour(vector<double> point);
    void findLeft(TreeNodeStatus* root, vector<double> point, TreeNodeStatus **leftneighbour);
    void findRight(TreeNodeStatus* root, vector<double> point, TreeNodeStatus **rightneighbour);
    Line findLeftMost(vector<double> point);
    Line findRightMost(vector<double> point);
    void findLeftMostNode(TreeNodeStatus* root , vector<double> point, TreeNodeStatus **leftmost);
    void findRightMostNode(TreeNodeStatus* root , vector<double> point, TreeNodeStatus **rightmost);
};