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

Vec ray_to_surf(Vec ray, Vec CamPos, Vec Spos, Vec Swidth){
    double denom = dot(ray, Swidth), t1=0, t2;
    if(denom*denom>1e-10){
        t1 = dot(sub(Spos, CamPos), Swidth)/denom;
        t2 = dot(sub(sum(Spos, Swidth), CamPos), Swidth)/denom;
        if(t2<t1)t1=-t2;
    }
    return ray.scale(t1);
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

Vec CamPos(5, 0, 0), CamDir(-5, 0, 0), lightPos(5, 0, 0), LightDir = Vec(-3, 0, 3).norm();

struct Cube{
public:
    Vec pos = Vec(-5, 0, 0);
    Vec w = Vec(0, 2, 0);
    Vec h = Vec(0, 0, 2);
    // Vec d = Vec(2, 0, 0);
    // Vec h = cross(Vec(1, 0, 0), w).setLength(w.length);
    Vec d = cross(h, w).setLength(w.length);

    double is_on_cube(Vec ray, Vec CamPos){
        double fi_w, fi_h, fi_d;

        Vec R = ray_to_surf(ray, CamPos, pos, w);
        Vec vec_in_cube = sub(R, pos);
        fi_h =  dot(vec_in_cube, h)*dot(vec_in_cube, h) - dot(vec_in_cube, h)*h.squareLen();
        fi_d =  dot(vec_in_cube, d)*dot(vec_in_cube, d) - dot(vec_in_cube, d)*d.squareLen();
        if(fi_h<0 & fi_d<0)return dot(LightDir, w.norm());

        R = ray_to_surf(ray, CamPos, pos, h);
        vec_in_cube = sub(R, pos);
        fi_w =  dot(vec_in_cube, w)*dot(vec_in_cube, w) - dot(vec_in_cube, w)*w.squareLen();
        fi_d =  dot(vec_in_cube, d)*dot(vec_in_cube, d) - dot(vec_in_cube, d)*d.squareLen();
        if(fi_w<=0 & fi_d<=0)return dot(LightDir, h.norm());

        R = ray_to_surf(ray, CamPos, pos, d);
        vec_in_cube = sub(R, pos);
        fi_w =  dot(vec_in_cube, w)*dot(vec_in_cube, w) - dot(vec_in_cube, w)*w.squareLen();
        fi_h =  dot(vec_in_cube, h)*dot(vec_in_cube, h) - dot(vec_in_cube, h)*h.squareLen();
        if(fi_w<=0 & fi_h<=0)return dot(LightDir, d.norm());
        return 0;
    }
};

Cube cube;

void drawScreen(int* screen, int w, int h){

    for(int i=0;i<w;++i){
        for (int j=0; j<h; ++j){

            Vec ray = sum(Vec(w/2-i, h/2-j, 0), CamDir);
            double col = cube.is_on_cube(ray, CamPos);
            if(col<0)col=0;

            int Color = col*255;
            if(Color<0)Color=0;
            if(Color>255)Color=255;

            screen[(j*w+i)*3+0] = Color;
            screen[(j*w+i)*3+1] = Color;
            screen[(j*w+i)*3+2] = Color;

            // vertexes[j*w+i] = sf::Vertex(sf::Vector2f(i, j), 
            //                             sf::Color(screen[(j*w+i)*3+0],
            //                                     screen[(j*w+i)*3+0],
            //                                     screen[(j*w+i)*3+0]));

            // window->draw(vertexes, w*h, sf::Points);
        }
    }
}

int main(){
    
    int w = 400, h = 400;
    int* screen = new int[w*h*3];

    // sf::RenderWindow window(sf::VideoMode(w, h), "3D Graphics");
    // sf::Vertex vertexes[w*h];

    // while (window.isOpen()){

    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear();
        drawScreen(screen, w, h);
    //     window.display();

    // }
    createImage(screen, w, h);

    // delete[] vertexes;
    delete[] screen;

    return 0;
}