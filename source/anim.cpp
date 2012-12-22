#include "anim.h"
#include "s3e.h"

#include <map>
#include <string>
using namespace std;

map<string, STYLEFUNC> stylefs;

double linear(double t,double b, double c, double d){
    return b+c*t/d;}

double quadIn(double t,double b, double c, double d){
    double p = t/d;
    return c*p*p + b;
}