#include <iostream>
#include "math.h"
#include "../lib/Linal.h"
#include <fstream>

// void printVec(Vec v){
//     std::cout << v.x << "\t";
//     std::cout << v.y << "\t";
//     std::cout << v.z << "\t";
//     std::cout << "\n";
// }

struct Cube{
    Vec pos = Vec(0, 5, 0);
    Vec dir1 = Vec(0, 0, 2);
    Vec dir2 = cross(Vec(0, 2, 0), dir1).setLength(dir1.length);
    Vec dir3 = cross(dir1, dir2).setLength(dir1.length);

    Vec is_cross(Vec cam, Vec ray){
        if( dot(ray, dir1)!=0){
            Vec to_cube = sum(pos, scalar(cam, -1));
            double t = dot(to_cube, dir1)/dot(ray, dir1);
            double t1 = dot(sum(to_cube, dir1), dir1)/dot(ray, dir1);
            if (t>t1) t=t1;
            Vec R = scalar(ray, t);// луч с такой длиной, который достаёт ровно до плоскости грани

            // if( dot(ray, dir2)!=0 && dot(ray, dir3)!=0 ) {
                double t_right = dot(to_cube, dir2)/dot(ray, dir2);
                double t_left = dot(sum(to_cube, dir2), dir2)/dot(ray, dir2);
                double t_up = dot(to_cube, dir3)/dot(ray, dir3);
                double t_down = dot(sum(to_cube, dir3), dir3)/dot(ray, dir3);

                Vec right = scalar(ray, t_right);
                Vec left = scalar(ray, t_left);
                if( (R.x-right.x)*(R.x-left.x)<0 &&
                    (R.y-right.y)*(R.y-left.y)<0 &&
                    (R.z-right.z)*(R.z-left.z)<0 )return R;

                Vec up = scalar(ray, t_up);
                Vec down = scalar(ray, t_down);
                if( (R.x-up.x)*(R.x-down.x)<0 &&
                    (R.y-up.y)*(R.y-down.y)<0 &&
                    (R.z-up.z)*(R.z-down.z)<0 )return R;
            // }
            
        }
        return Vec(0, 0, 0);
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

    Cube cube;
    // printVec(cube.is_cross(Vec(0, 0, -1), Vec(0, 0.2, 1)));

    for(int i=0;i<w;i++){
        for (int j=0; j<h; ++j){
            Vec ray(i-w/2, j-h/2, 5);// z - длина камеры
            // if (cube.is_cross(Vec(0, 0, -5), ray).length!=0)printVec(cube.is_cross(Vec(0, 0, -5), ray));
            // if (cube.is_cross(Vec(0, 0, -5), ray).length!=0) screen[(i*w+j)*3] = 255;
            // else screen[(i*w+j)*3] = 0;
            // screen[(i*w+j)*3+1] = 0;
            // screen[(i*w+j)*3+2] = 0;
        }
    }

    createImage(screen, w, h);
    delete[] screen;

    return 0;
}