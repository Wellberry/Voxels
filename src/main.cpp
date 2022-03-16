#include <iostream>
#include "math.h"
#include "../lib/Linal.h"
#include <fstream>
#include <SFML/Graphics.hpp>

void printVec(Vec v){
    std::cout << v.x << "\t";
    std::cout << v.y << "\t";
    std::cout << v.z << "\t";
    std::cout << "\n";
}

Vec CamPos(10, 0, 0), 
    CamDir(-10, 0, 0), 
    lightPos(5, 0, 0), 
    LightDir = Vec(1, 1, 1).norm();

Vec ray_to_closer_surf(Vec ray, Vec pos, Vec norm){
    double denom = dot(ray, norm), t1, t2;
    t1 = dot(sub(pos, CamPos), norm)/denom;
    t2 = dot(sub(sum(pos, norm),CamPos), norm)/denom;
    if(t2>t1)t1=-t2;
    return sum(ray.scale(t1), CamPos);
}

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

struct Cube{
public:
    Vec pos = Vec(-47, 0, 0);
    Vec w = Vec(0, 50, 0);
    Vec h = Vec(0, 0, 50);
    Vec d = Vec(50, 0, 0);

    // Vec h = cross(Vec(1, 0, 0), w).setLength(w.length);
    // Vec d = cross(h, w).setLength(w.length);

private:
    double fi(Vec R, Vec norm){
        //Formula of surfaces: fi(R) = (R-pos, norm)^2 - (R-pos, norm)*norm^2
        return dot(sub(R, pos), norm)*dot(sub(R, pos), norm) - dot(sub(R, pos), norm)*norm.squareLen();
    }

public:
    double is_on_cube(Vec ray){
        double fi_w, fi_h, fi_d;
        Vec toCube(0, 0, 0);

        if(dot(ray, w)*dot(ray, w)>=1e-3){
            toCube = ray_to_closer_surf(ray, pos, w);
            fi_d = fi(toCube, d);
            fi_h = fi(toCube, h);
            if(fi_d<=0 & fi_h<=0){
                if(dot(LightDir, w.norm())>0)return dot(LightDir, w.norm());
                else return 0;
            }
        }
        if(dot(ray, h)*dot(ray, h)>=1e-3){
            toCube = ray_to_closer_surf(ray, pos, h);
            fi_w = fi(toCube, w);
            fi_d = fi(toCube, d);
            if(fi_w<=0 & fi_d<=0){
                if(dot(LightDir, h.norm())>0)return dot(LightDir, h.norm());
                else return 0;
            }
        }
        if(dot(ray, d)*dot(ray, d)>=1e-3){
            toCube = ray_to_closer_surf(ray, pos, d);
            fi_w = fi(toCube, w);
            fi_h = fi(toCube, h);
            if(fi_w<=0 & fi_h<=0){
                if(dot(LightDir, d.norm())>0)return dot(LightDir, d.norm());
                else return 0;
            }
        }
        return 0;
    }
};

Cube cube;

void drawScreen(int* screen, int w, int h){

    for(int j=0;j<h;j++){
        for (int i=0; i<w; i++){

            Vec ray = sum(Vec(0, i-w/2, h/2-j), CamDir);
            double col = cube.is_on_cube(ray);

            int Color = col*255;
            if(Color<=0){
                screen[(j*h+i)*3+0] = 0;
                screen[(j*h+i)*3+1] = 20;
                screen[(j*h+i)*3+2] = 0;
            }else{
                if(Color>255)Color=255;
                screen[(j*h+i)*3+0] = Color;
                screen[(j*h+i)*3+1] = Color;
                screen[(j*h+i)*3+2] = Color;
            }
        }
    }
}

int main(){
    
    int w = 600, h = 400;


    int* screen = new int[w*h*3];
    drawScreen(screen, w, h);
    createImage(screen, w, h);
    delete[] screen;

    return 0;
}