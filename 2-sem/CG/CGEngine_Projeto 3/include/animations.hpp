#include "math.h"
#include "algebra.hpp"
#include "ponto.hpp"

void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv,int P,std::vector<Ponto>p);

void getCatmullRomPoint(float t, std::vector<float> p0, std::vector<float> p1, std::vector<float> p2, std::vector<float> p3, float *pos, float *deriv);

void multMatrixVector(float *m, float *v, float *res);

void buildRotMatrix(float *x, float *y, float *z, float *m);

void cross(float *a, float *b, float *res);

void normalize(float *a);

float length(float *v);