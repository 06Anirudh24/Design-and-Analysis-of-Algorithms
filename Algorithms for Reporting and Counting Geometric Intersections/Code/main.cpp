#include<stdlib.h>
#include<iostream>
#include "line.h"
#include "statusStructure.h"
#include "eventQueue.h"
using namespace std;
//Add imports for eventQueue, statusStructure. 

struct FindIntersection
{
    EventQueue *Q;
    StatusStucture *T;
    vector<double> intersections ;
    public: 
    FindIntersection()
    {
        this.Q = new EventQueue(); 
        this.T = new StatusStructure();
        this.right = NULL ;
        this.intersections ; //check
    }
    

    void find_intersection(vector<Line> lines)
    {
        for(int i = 0 ; i < lines.size() ; i++)
        {
            this.Q->insert_line(lines[i]);
        }
        while(!(this->Q).empty())
        {
            int next_event = this->Q->pop_next_event();
            this->handle_event_point(next_event);
        }
    }


    void handle_event_point(TreeNode* p)
    {
        vector<Line> U_p  ;
        for(int i = 0 ; i < p->lines.size() ; i++)
            U_p.push_back(p->lines[i]) ; 
        Line L_p, C_p, L_c;
        vector<vector<Line>> temp ;
        temp = this->T->findSegmentsContain(p->point);
        L_p = temp[0] ;
        C_p = temp[1] ;
        L_c = temp[2] ; 
        vector<Line> U_C;// = U_p + C_p;
        for(int i = 0 ; i < U_p.size() ; i++)
            U_C.push_back(U_p[i]) ;
        for(int i = 0 ; i < C_p.size() ; i++)
            U_C.push_back(C_p[i]) ;
        vector<Line> L_U_C ;// = L_C + U_p;
        for(int i = 0 ; i < L_C.size() ; i++)
            L_U_C.push_back(L_C[i]) ;
        for(int i = 0 ; i < U_p.size() ; i++)
            L_U_C.push_back(U_p[i]) ;

        if L_U_C.size() > 1
            this->intersections.push_back(p->point);
        for(int i = 0 ; i < L_C.size() ; i++)
            this->intersections.delete(p->point,L_C[i]);
        this->T.insert(p->point, U_C);
        this->T._print_name();
        if L_U_C.size() == 0
        {
            Line s_l = this->T.findLeftNeighbour(p->point);
            Line s_r = this->T.findRightNeighbour(p->point);
            this.find_new_event(s_l, s_r, p->point);
        }
        else
        {
            Line s_lm = this->T.findLeftMost(p->point);
            Line s_l = this->T.findLeftNeighbour(p->point);
            this.find_new_event(s_lm, s_l, p->point);
            Line s_rm = this->T.findRightMost(p->point);
            Line s_r = this->T.findRightNeighbour(p->point);
            this.find_new_event(s_rm, s_r, p->point);
        }
    }


    void find_new_event(Line s_l, Line s_r, point p)
    {
        if(s_l.upper_endpoint.size() == 0 || s_r.upper_endpoint.size() == 0 )
            return;
        vector<double> i = s_l.intersect(s_r); //Check
        if(i.size() == 0)
            return;

        double x_i, y_i; 
        x_i = i[0]; y_i = i[1];

        double x_p, y_p;
        x_p = p[0]; y_p = p[0];

        if( (y_i<y_p) || (y_i==y_p && x_i>x_p) )
           this.Q.push_back(i); 
        
    }

//Lines initialisation 

};
void main(){
    int n ;
    vector<Line> lines ;
    vector<double> p1(2),p2(2) ;
    cout <<"Enter number of lines: " ;
    cin >> n ;
    for(int i = 0 ; i < n  ;i++){
        cout <<"\nEnter Line segment points: " ;
        cin >> p1[0] >> p1[1] >> p2[0] >> p2[1] ;
        Line temp = Line(p1,p2) ;
        temp.set_name(i+1) ;
        lines.push_back(temp) ;
    }
    FindIntersection F;
    F.find_intersection(lines) ;
    //write code to plot lines
    
}