#include "Linal.h"
#include <iostream>
#include <math.h>
Vec::Vec(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
    length = sqrt(x*x+y*y+z*z);
}
Vec Vec::scale(double value){
    x*=value;
    y*=value;
    z*=value;
    length = sqrt(x*x+y*y+z*z);
    return *this;
}
double Vec::squareLen(){
    return length*length;
}
Vec Vec::norm(){
    x /= length;
    y /= length;
    z /= length;
    length = sqrt(x*x+y*y+z*z);
    return *this;
}

Vec Vec::setLength(double len){
    norm();
    scale(len);
    return *this;
}

double dot(Vec a, Vec b){
    double res = a.x*b.x + a.y*b.y + a.z*b.z;
    return res;
}

Vec cross(Vec a, Vec b){
    Vec res(a.y*b.z-a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
    return res;
}

Vec sum(Vec a, Vec b){
    Vec res(a.x+b.x, a.y+b.y, a.z+b.z);
    return res;
}

Vec sub(Vec a, Vec b){
    Vec res(a.x-b.x, a.y-b.y, a.z-b.z);
    return res;
}

Vec scalar(Vec a, double value){
    Vec res = a;
    res.scale(value);
    return res;
}