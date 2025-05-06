//
// Created by nuno on 24-03-2024.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "ponto.hpp"
#include "draw.hpp"
#include "algebra.hpp"

using namespace std;

void parseBezierPatch(const std::string& path, std::vector<std::vector<int>>& patchIndices, std::vector<Ponto>& controlPoints) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        return;
    }

    std::string line;

    // Parse number of patches
    int numPatches;
    std::getline(file, line);
    std::istringstream ssPatches(line);
    ssPatches >> numPatches;

    // Parse patch indices
    for (int i = 0; i < numPatches; ++i) {
        std::getline(file, line);
        std::istringstream issIndices(line);
        std::string indexStr;
        std::vector<int> indices;
        while (std::getline(issIndices, indexStr, ',')) {
            std::istringstream ss(indexStr);
            int index;
            ss >> index;
            indices.push_back(index);
        }
        patchIndices.push_back(indices);
    }

    // Parse number of control points
    int numControlPoints;
    file >> numControlPoints;
    file.ignore();  // ignore the newline character

    for (int i = 0; i < numControlPoints; ++i) {
        double x, y, z;
        std::getline(file, line);
        std::istringstream iss(line);

        char comma;
        iss >> x >> comma >> y >> comma >> z;  // Read values separated by commas

        Ponto p = Ponto(x, y, z);
        controlPoints.push_back(p);
    }

    file.close();
}

std::vector<std::vector<Ponto>> drawBezier(const std::string& path, int tesselation) {

    Matrix4x4 _M = { -1.0f, 3.0f, -3.0f, 1.0f ,
                     3.0f, -6.0f, 3.0f, 0.0f ,
                     -3.0f, 3.0f, 0.0f, 0.0f ,
                     1.0f,  0.0f, 0.0f, 0.0f }; // Matriz fixa

    Matrix4x4 _M_transpose = _M;
    std::vector<std::vector<int>> patchIndices;
    std::vector<Ponto> controlPoints;
    parseBezierPatch(path, patchIndices, controlPoints);
    std::vector<Ponto> vp;
    std::vector<Ponto> vn;
    std::vector<Ponto> vt; // Texture coordinates vector




    for (int patch = 0; patch < patchIndices.size(); ++patch){

        // Set texture coordinates for this patch
        std::vector<Ponto> aux; // Texture coordinates vector
        for (int a = 0; a<16;++a){
            aux.push_back(controlPoints[patchIndices[patch][a]]);
        }
        //construir a Matriz dos Pontos de Controlo
        MatrixPonto4x4 P  = {controlPoints[patchIndices[patch][0]],controlPoints[patchIndices[patch][1]],controlPoints[patchIndices[patch][2]],controlPoints[patchIndices[patch][3]],
                             controlPoints[patchIndices[patch][4]],controlPoints[patchIndices[patch][5]],controlPoints[patchIndices[patch][6]],controlPoints[patchIndices[patch][7]],
                             controlPoints[patchIndices[patch][8]],controlPoints[patchIndices[patch][9]],controlPoints[patchIndices[patch][10]],controlPoints[patchIndices[patch][11]],
                             controlPoints[patchIndices[patch][12]],controlPoints[patchIndices[patch][13]],controlPoints[patchIndices[patch][14]],controlPoints[patchIndices[patch][15]],};

        //multiplicar a Matriz por _M * P * _M_transpose
        MatrixPonto4x4 T = multiplyMatrixPonto(_M,P);
        MatrixPonto4x4 PrePro = multiplyPontoMatrix(T,_M_transpose);
        float step = 1.0f / static_cast<float>(tesselation);


        for (int u = 0; u < tesselation; ++u){

            for (int v = 0; v < tesselation; ++v){

                // u e v / tess, Normalizar

                float u2 = (float) u * step;
                float v2 = (float) v * step;


                Matrix1x4 matrixU = {{static_cast<float>(pow(u2,3)), static_cast<float>(pow(u2,2)), static_cast<float>(pow(u2,1)), 1}};
                Matrix4x1 matrixV = {{static_cast<float>(pow(v2,3)), static_cast<float>(pow(v2,2)), static_cast<float>(pow(v2,1)), 1}};
                Ponto p0 = multiplyF_P_V(matrixU,PrePro,matrixV);

                // normais
                Matrix1x4 matrixUD = {{static_cast<float>(3*pow(u2,2)), static_cast<float>(2*pow(u2,1)), static_cast<float>(1), 0}};
                Matrix4x1 matrixVD = {{static_cast<float>(3*pow(v2,2)), static_cast<float>(2*pow(v2,1)), static_cast<float>(1), 0}};

                Ponto p0t1 = multiplyF_P_V(matrixUD,PrePro,matrixV);
                Ponto p0t2 = multiplyF_P_V(matrixU,PrePro,matrixVD);

                Ponto ntemp0 = p0t2.crossProduct(p0t1);
                Ponto n0 = ntemp0.normalize();


                Matrix1x4 matrixU1 = {{static_cast<float>(pow(u2,3)), static_cast<float>(pow(u2,2)), static_cast<float>(pow(u2,1)), 1}};
                Matrix4x1 matrixV1 = {{static_cast<float>(pow(v2+step,3)), static_cast<float>(pow(v2+step,2)), static_cast<float>(pow(v2+step,1)), 1}};
                Ponto p1 = multiplyF_P_V(matrixU1,PrePro,matrixV1);

                // normais
                Matrix1x4 matrixUD1 = {{static_cast<float>(3*pow(u2,2)), static_cast<float>(2*pow(u2,1)), static_cast<float>(1), 0}};
                Matrix4x1 matrixVD1 = {{static_cast<float>(3*pow((v2+step),2)), static_cast<float>(2*pow((v2+step),1)), static_cast<float>(1), 0}};

                Ponto p1t1 = multiplyF_P_V(matrixUD1,PrePro,matrixV1);
                Ponto p1t2 = multiplyF_P_V(matrixU1,PrePro,matrixVD1);

                Ponto ntemp1 = p1t2.crossProduct(p1t1);
                Ponto n1 = ntemp1.normalize();

                Matrix1x4 matrixU2 = {{static_cast<float>(pow(u2+step,3)), static_cast<float>(pow(u2+step,2)), static_cast<float>(pow(u2+step,1)), 1}};
                Matrix4x1 matrixV2 = {{static_cast<float>(pow(v2,3)), static_cast<float>(pow(v2,2)), static_cast<float>(pow(v2,1)), 1}};
                Ponto p2 = multiplyF_P_V(matrixU2,PrePro,matrixV2);

                // normais
                Matrix1x4 matrixUD2 = {{static_cast<float>(3*pow((u2+step),2)), static_cast<float>(2*pow((u2+step),1)), static_cast<float>(1), 0}};
                Matrix4x1 matrixVD2 = {{static_cast<float>(3*pow(v2,2)), static_cast<float>(2*pow(v2,1)), static_cast<float>(1), 0}};

                Ponto p2t1 = multiplyF_P_V(matrixUD2,PrePro,matrixV2);
                Ponto p2t2 = multiplyF_P_V(matrixU2,PrePro,matrixVD2);

                Ponto ntemp2 = p2t2.crossProduct(p2t1);
                Ponto n2 = ntemp2.normalize();


                Matrix1x4 matrixU3 = {{static_cast<float>(pow(u2+step,3)), static_cast<float>(pow(u2+step,2)), static_cast<float>(pow(u2+step,1)), 1}};
                Matrix4x1 matrixV3 = {{static_cast<float>(pow(v2+step,3)), static_cast<float>(pow(v2+step,2)), static_cast<float>(pow(v2+step,1)), 1}};
                Ponto p3 = multiplyF_P_V(matrixU3,PrePro,matrixV3);

                // normais
                Matrix1x4 matrixUD3 = {{static_cast<float>(3*pow((u2+step),2)), static_cast<float>(2*pow((u2+step),1)), static_cast<float>(1), 0}};
                Matrix4x1 matrixVD3 = {{static_cast<float>(3*pow((v2+step),2)), static_cast<float>(2*pow((v2+step),1)), static_cast<float>(1), 0}};

                Ponto p3t1 = multiplyF_P_V(matrixUD3,PrePro,matrixV3);
                Ponto p3t2 = multiplyF_P_V(matrixU3,PrePro,matrixVD3);

                Ponto ntemp3 = p3t2.crossProduct(p3t1);
                Ponto n3 = ntemp3.normalize();


                vp.push_back(p0);
                vn.push_back(n0);
                vt.push_back(Ponto(1.0f - v2, 1.0f - u2, 0));

                vp.push_back(p1);
                vn.push_back(n1);
                vt.push_back(Ponto(1.0f - (v2+step),  1.0f - u2, 0));

                vp.push_back(p2);
                vn.push_back(n2);
                vt.push_back(Ponto( 1.0f - (v2), 1.0f-(u2+step), 0));


                vp.push_back(p1);
                vn.push_back(n1);
                vt.push_back(Ponto(1.0f - (v2+step), 1.0f - u2, 0));

                vp.push_back(p3);
                vn.push_back(n3);
                vt.push_back(Ponto( 1.0f - (v2 + step) , 1.0f -(u2 + step) , 0));

                vp.push_back(p2);
                vn.push_back(n2);
                vt.push_back(Ponto( 1.0f- (v2), 1.0f - (u2+step), 0));

            }
        }
    }
    std::vector<std::vector<Ponto>> res;
    res.push_back(vp);
    res.push_back(vn);
    res.push_back(vt);
    return res;
}
