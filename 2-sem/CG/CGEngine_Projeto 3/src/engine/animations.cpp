//
// Created by nuno on 07-04-2024.
//
#include <vector>
#include "animations.hpp"

void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv,int P,std::vector<Ponto>p) {
    // gt tem de estar entre 0 e 1
    // P é o número de pontos

    float t = gt * P; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + P-1)%P;
    indices[1] = (indices[0]+1)%P;
    indices[2] = (indices[1]+1)%P;
    indices[3] = (indices[2]+1)%P;

    getCatmullRomPoint(t, p[indices[0]].toVector(), p[indices[1]].toVector(), p[indices[2]].toVector(), p[indices[3]].toVector(), pos, deriv);
}

void multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

void getCatmullRomPoint(float t, std::vector<float> p0, std::vector<float> p1, std::vector<float> p2, std::vector<float> p3, float *pos, float *deriv) {

    // catmull-rom matrix
    float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
                         { 1.0f, -2.5f,  2.0f, -0.5f},
                         {-0.5f,  0.0f,  0.5f,  0.0f},
                         { 0.0f,  1.0f,  0.0f,  0.0f}};

    for(int i = 0; i<3;i++){

        // Compute A = M * P
        float _p[4] {p0[i],p1[i],p2[i],p3[i]};
        float _a[4];
        multMatrixVector(*m,_p,_a);


        float _t[4]={powf(t,3),powf(t,2),t,1.0f};

        pos[i] = 0;
        for (int j = 0;j<4;j++){
            pos[i] += _t[j] * _a[j];
        }
        // compute deriv = T' * A
        deriv[i] = 0;
        float _td[4]={3*powf(t,2),2*powf(t,1),1.0f,0.0f};
        for (int j = 0;j<4;j++){
            deriv[i] += _td[j] * _a[j];
        }

    }

}


void buildRotMatrix(float *x, float *y, float *z, float *m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}


float length(float *v) {

    float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    return res;

}



