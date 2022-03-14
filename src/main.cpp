#include <iostream>
#include "math.h"
#include "../lib/Linal.h"
#include <fstream>
// #include "SFML/Graphics.hpp"

void printVec(Vec v){
    std::cout << v.x << "\t";
    std::cout << v.y << "\t";
    std::cout << v.z << "\t";
    std::cout << "\n";
}

struct Cube{
public:
    Vec pos = Vec(-5, 0, 0);
    Vec w = Vec(0, 2, 0);
    Vec h = cross(Vec(2, 0, 0), w).setLength(w.length);
    Vec d = cross(h, w).setLength(w.length);

    Vec ray_to_surf(Vec ray, Vec CamPos, Vec Spos, Vec Swidth){
        Vec res(0, 0, 0);
        double denom = dot(ray, Swidth), t1, t2;
        if(denom!=0){
            t1 = dot(sub(Spos, CamPos), Swidth)/denom;
            t2 = dot(sub(sum(Spos, Swidth), CamPos), Swidth)/denom;
            if(t2<t1)t1=t2;
            res = ray.scale(t1);
        }
        return res;
    }

    double is_on_cube(Vec ray, Vec CamPos){
        Vec R = ray_to_surf(ray, CamPos, pos, w);
        Vec vec_in_cube = sub(R, pos);
        double fi_h =  dot(vec_in_cube, h)*dot(vec_in_cube, h) - dot(vec_in_cube, h)*h.squareLen();
        double fi_d =  dot(vec_in_cube, d)*dot(vec_in_cube, d) - dot(vec_in_cube, d)*d.squareLen();
        if(fi_h<=0 & fi_d<=0)return dot(ray.norm(), w.scale(-1).norm());

        R = ray_to_surf(ray, CamPos, pos, h);
        vec_in_cube = sub(R, pos);
        double fi_w =  dot(vec_in_cube, w)*dot(vec_in_cube, w) - dot(vec_in_cube, w)*w.squareLen();
        fi_d =  dot(vec_in_cube, d)*dot(vec_in_cube, d) - dot(vec_in_cube, d)*d.squareLen();
        if(fi_w<=0 & fi_d<=0)return dot(ray.norm(), h.scale(-1).norm());

        R = ray_to_surf(ray, CamPos, pos, d);
        vec_in_cube = sub(R, pos);
        fi_w =  dot(vec_in_cube, w)*dot(vec_in_cube, w) - dot(vec_in_cube, w)*w.squareLen();
        fi_h =  dot(vec_in_cube, h)*dot(vec_in_cube, h) - dot(vec_in_cube, h)*h.squareLen();
        if(fi_w<=0 & fi_h<=0)return dot(ray.norm(), d.scale(-1).norm());
        return 0;
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
            // Vec ray = sum(Vec(i-w/2, j-h/2, 0), CamDir);
            // double col = cube.is_on_cube(ray, CamPos);
            // if(col<0)col*=-1;
            Vec r0(50, 0, 0), wid(100, -30, 0), R(w/2-i, h/2-j, 0);
            R = sub(R, r0);
            double fi = dot(R, wid)*dot(R, wid) - dot(R, wid)*wid.squareLen();
            if(fi<0)fi=0;
            if(fi>255)fi=255;
            screen[(j*w+i)*3+0] = fi;

            r0 = Vec(0, 0, 0); wid = Vec(15, 50, 0); R = Vec(w/2-i, h/2-j, 0);
            R = sub(R, r0);
            fi = dot(R, wid)*dot(R, wid) - dot(R, wid)*wid.squareLen();
            if(fi<0)fi=0;
            if(fi>255)fi=255;
            screen[(j*w+i)*3+1] = fi;
            screen[(j*w+i)*3+2] = fi/2;
        }
    }

    createImage(screen, w, h);
    delete[] screen;

    return 0;
}