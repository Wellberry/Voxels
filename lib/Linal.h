#ifndef LINAL_H
#define LINAL_H

class Vec {
public:
    double x, y, z, length;
    Vec(double x, double y, double z);

    Vec scale(double value);
    double squareLen();
    Vec norm();
    Vec setLength(double length);
};
//Operations:
double dot(Vec a, Vec b);
Vec cross(Vec a, Vec b);
Vec sum(Vec a, Vec b);
Vec scalar(Vec a, double value);

#endif