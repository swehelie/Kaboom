#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include "size.h"
using namespace std;

const float s_rad = 1.5;

float record_distance(const Vec3f &pos){
  return pos.norm() - s_rad;
}

bool record_sphere(const Vec3f& origin, Vec3f& dir, Vec3f& pos){
  pos = origin;
  for(size_t i = 0; i < 128; i++){
    float dist = record_distance(pos);
    if(dist < 0){
      return true;
    }
    pos = pos + dir*max(dist*0.1f, 0.01f);
  }
  return false;
}
int main() {
  const int w = 640;
  const int h = 480;
  const float vect = M_PI/3.;
  vector<Vec3f> framebuffer(w*h);

  for(size_t i=0; i < h; i++){
    for(size_t j=0; j<w; j++){
      float x = (j + 0.5) - w/2;
      float y = -(i + 0.5) + h/2;
      float z = -h/(2.*tan(vect/2.));
      Vec3f create;
      if(record_sphere(Vec3f(0,0,3), Vec3f(x, y, z).normalize(), create)){
        framebuffer[j+i*w] = Vec3f(1, 1, 1);
      }
      else{
        framebuffer[j+i*w] = Vec3f(0.2, 0.7, 0.8);
      }
    }
  }
  //saving framebuffer to file
  ofstream ofs("out.png", ios::binary);
  for(size_t i = 0; i < h*w; ++i){
    for(size_t j=0; j < 3; j++){
      ofs << (char)(max(0, min(255, static_cast<int>(255*framebuffer[i][j]))));
    }
  }
  ofs.close();
  return 0;
}