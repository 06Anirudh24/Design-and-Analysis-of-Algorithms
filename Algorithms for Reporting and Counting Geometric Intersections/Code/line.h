#include<math.h>
#include<stdlib.h>
#include <cmath>
#include<tgmath.h>
#include<typeinfo>
#define _USE_MATH_DEFINES
using namespace std;
private class Line{
    vector<double> upper_endpoint ;
    vector<double> lower_endpoint ; 
    public:
    Line(vector<double> vector<double> );
    vector<double> intersect(Line line);
    void set_name(int i)
    int point_location(vector<double>);
    double get_lower_angle();
    double get_upper_angle();
    double get_x(int y);
    int is_vertical();
    double compare_lower(vector<double>, Line);
};
