#include <iostream>
#include <cmath>
#include "../lib/Linal.h"

void printVec(Vec v){
    std::cout << v.x << "\t";
    std::cout << v.y << "\t";
    std::cout << v.z << "\t";
    std::cout << "\n";
}

int main(){

    Vec v1(1, 0, 1);
    v1.setLength(15);
    printVec(v1);
    std::cout << v1.length << "\n\n";
    std::cout << 10.6066*sqrt(2) << "\n";

    return 0;
}