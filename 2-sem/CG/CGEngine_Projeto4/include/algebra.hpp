//
// Created by nuno on 18-03-2024.
//
#ifndef ALGEBRA_HPP
#define ALGEBRA_HPP


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include "ponto.hpp"

struct Matrix4x4 {
    float data[4][4]; // 4x4 matrix data
};

struct MatrixPonto4x4 {
    Ponto data[4][4]; // 4x4 matrix data
};

Matrix4x4 multiplyMatrices(const std::vector<Matrix4x4>& matrices);

void matrix4x4ToGLfloat(const Matrix4x4& matrix, GLfloat* glMatrix);

void printMatrix(const Matrix4x4& matrix);

Matrix4x4 inverse(const Matrix4x4& matrix);

MatrixPonto4x4 multiplyMatrixPonto(const Matrix4x4& matrixFloat, MatrixPonto4x4& matrixPonto);

MatrixPonto4x4 multiplyPontoMatrix(MatrixPonto4x4& matrixPonto, const Matrix4x4& matrixFloat);

struct Matrix1x4 {
    float data[1][4]; // 1x4 matrix data
};

struct Matrix4x1 {
    float data[4][1]; // 4x1 matrix data
};
void printPontoMatrix (MatrixPonto4x4& matrix);

Ponto multiplyF_P_V(const Matrix1x4& matrixF, MatrixPonto4x4& matrixP, const Matrix4x1& matrixV);

#endif