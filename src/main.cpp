#include <iostream>
#include "math.h"
#include "../lib/Linal.h"
#include <fstream>

void printVec(Vec v){
    std::cout << v.x << "\t";
    std::cout << v.y << "\t";
    std::cout << v.z << "\t";
    std::cout << "\n";
}

struct Cube{
    Vec pos = Vec(-5, 0, 0);
    Vec w = Vec(0, 2, 0);
    Vec h = cross(Vec(2, 0, 0), w).setLength(w.length);
    Vec d = cross(h, w).setLength(w.length);

    Vec get_parameter(Vec ray, Vec CamPos, Vec Spos, Vec Swidth){
        Vec res(0, 0, 0);
        double denom = dot(ray, Swidth), t1, t2;
        if(denom>1e-8){
            t1 = dot(sub(Spos, CamPos), Swidth)/denom;
            t2 = dot(sub(sum(Spos, Swidth), CamPos), Swidth)/denom;
            if(t2<t1)t1=t2;
            res = ray.scale(t1);
        }
        return res;
    }


};

void createImage(int* screen, int w, int h){
    std::ofstream image;
    image.open("image.ppm");
    if(image.is_open()){
        image << "P3" << std::endl;
        image << std::to_string(w)<< " "<< std::to_string(h) << std::endl;
        image << "255" << std::endl;

        for (int i = 0; i < h; i++){
            for (int j = 0; j < w; j++){
                image << std::to_string(screen[(i*h+j)*3+0])<<" ";
                image << std::to_string(screen[(i*h+j)*3+1])<<" ";
                image << std::to_string(screen[(i*h+j)*3+2])<< std::endl;
            }
        }
    }
    image.close();
}

int main(){
    
    int w = 400, h = 400;
    int* screen = new int[w*h*3];
    Vec CamPos(5, 0, 0), CamDir(-5, 0, 0);

    Cube cube;

    for(int i=0;i<w;++i){
        for (int j=0; j<h; ++j){
            Vec ray = sum(Vec(i-w/2, j-h/2, 0), CamDir);
            // screen[(i*w+j)*3+1] = 0;
            // screen[(i*w+j)*3+2] = 0;
        }
    }

    createImage(screen, w, h);
    delete[] screen;

    return 0;
}