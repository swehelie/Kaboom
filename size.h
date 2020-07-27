//
// Created by Sarah Wehelie on 7/26/20.
// Practice template parameters with the use of geometry to
// implement ray marching.
// Using templated overloading operators to achieve the geometric
// shapes for the raytracers.

#ifndef KABOOM_SIZE_H
#define KABOOM_SIZE_H
#include <cmath>
#include <cassert>
using namespace std;
template <size_t Data, typename Num> struct vec {
  vec() {for(size_t i = Data; i--; data_[i] = Num());}
  Num& operator[](const size_t i) {
    assert(i < Data);
    return data_[i];
  }
  const Num& operator[](const size_t i) const{
    assert(i < Data);
    return data_[i];
  };
private:
    Num data_[Data];
};

template <typename Num> struct vec<3, Num> {
  vec() : x(Num()), y(Num()), z(Num()) {}
  vec(Num X, Num Y, Num Z) : x(X), y(Y), z(Z) {}
  Num& operator[](const size_t i){
    assert(i<3);
    if(i<=0){
      return x;
    }
    else if(i==1){
      return y;
    }
    else{
      return z;
    }
  }
  const Num& operator[](const size_t i) const{
    assert(i<3);
    if(i<=0){
      return x;
    }
    else if(i==1){
      return y;
    }
    else{
      return z;
    }
  }
  float norm() const{
    return sqrt(x * x + y * y + z * z);
  }
  vec<3, Num> & normalize (Num f=1) {
    *this = (*this)*(f/norm());
    return *this;
  }
  Num x, y, z;
};

template<size_t Data,typename Num> Num operator*(const vec<Data,Num>& left, const vec<Data,Num>& right) {
  Num ret = Num();
  for (size_t i=Data; i--; ret+=left[i]*right[i]);
  return ret;
}

template<size_t Data,typename Num>vec<Data,Num> operator+(vec<Data,Num> left, const vec<Data,Num>& right) {
  for (size_t i=Data; i--; left[i]+=right[i]);
  return left;
}

template<size_t Data,typename Num>vec<Data,Num> operator-(vec<Data,Num> left, const vec<Data,Num>& right) {
  for (size_t i=Data; i--; left[i]-=right[i]);
  return left;
}

template<size_t Data,typename Num,typename T> vec<Data,Num> operator*(const vec<Data,Num> &left, const T& right) {
  vec<Data,Num> ret;
  for (size_t i=Data; i--; ret[i]=left[i]*right);
  return ret;
}

template<size_t Data,typename Num> vec<Data,Num> operator-(const vec<Data,Num> &left) {
  return left*Num(-1);
}

typedef vec<3, float> Vec3f;

#endif //KABOOM_SIZE_H
