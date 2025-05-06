//
// Created by nuno on 18-03-2024.
//


#include <iostream>
#include "ponto.hpp"
#include "algebra.hpp"

Matrix4x4 multiplyMatrices(const std::vector<Matrix4x4>& matrices) {

    // Init com a identidade
    Matrix4x4 result{};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }

    // Multiplicar todas as matrizes pela ordem
    for (Matrix4x4 matrix : matrices) {
        Matrix4x4 tempResult{};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                tempResult.data[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    tempResult.data[i][j] += result.data[i][k] * matrix.data[k][j];
                }
            }
        }
        result = tempResult;
    }
    return result;
}

void matrix4x4ToGLfloat(const Matrix4x4& matrix, GLfloat* glMatrix) {
    int index = 0;
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            glMatrix[index++] = matrix.data[row][col];
        }
    }
}

void printMatrix(const Matrix4x4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix.data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printPontoMatrix (MatrixPonto4x4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix.data[i][j].toString() << " ";
        }
        std::cout << std::endl;
    }
}

// Function to calculate the determinant of a 3x3 submatrix
float determinant3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

// Function to calculate the determinant of a 4x4 matrix
float determinant4x4(const Matrix4x4& matrix) {
    float a = matrix.data[0][0];
    float b = matrix.data[0][1];
    float c = matrix.data[0][2];
    float d = matrix.data[0][3];
    float e = matrix.data[1][0];
    float f = matrix.data[1][1];
    float g = matrix.data[1][2];
    float h = matrix.data[1][3];
    float i = matrix.data[2][0];
    float j = matrix.data[2][1];
    float k = matrix.data[2][2];
    float l = matrix.data[2][3];
    float m = matrix.data[3][0];
    float n = matrix.data[3][1];
    float o = matrix.data[3][2];
    float p = matrix.data[3][3];

    float cofactorA = determinant3x3(f, g, h, j, k, l, n, o, p);
    float cofactorB = determinant3x3(e, g, h, i, k, l, m, o, p);
    float cofactorC = determinant3x3(e, f, h, i, j, l, m, n, p);
    float cofactorD = determinant3x3(e, f, g, i, j, k, m, n, o);

    return a * cofactorA - b * cofactorB + c * cofactorC - d * cofactorD;
}

// Function to calculate the cofactor of a 3x3 submatrix
float cofactor3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    return determinant3x3(e, f, g, h, i, d, b, c, a);
}

// Function to calculate the inverse of a 4x4 matrix
Matrix4x4 inverse(const Matrix4x4& matrix) {
    Matrix4x4 result;
    float det = determinant4x4(matrix);
    if (std::abs(det) < 1e-6) {
        std::cerr << "Matrix is singular, cannot compute inverse." << std::endl;
        return result; // Return identity matrix as default when matrix is singular
    }

    // Calculate each element of the inverse matrix using cofactors
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            // Calculate cofactor for this element
            float cofactor = cofactor3x3(matrix.data[(row + 1) % 4][(col + 1) % 4],
                                         matrix.data[(row + 1) % 4][(col + 2) % 4],
                                         matrix.data[(row + 1) % 4][(col + 3) % 4],
                                         matrix.data[(row + 2) % 4][(col + 1) % 4],
                                         matrix.data[(row + 2) % 4][(col + 2) % 4],
                                         matrix.data[(row + 2) % 4][(col + 3) % 4],
                                         matrix.data[(row + 3) % 4][(col + 1) % 4],
                                         matrix.data[(row + 3) % 4][(col + 2) % 4],
                                         matrix.data[(row + 3) % 4][(col + 3) % 4]);
            // Apply the sign change to alternate elements
            result.data[col][row] = ((row + col) % 2 == 0 ? 1 : -1) * cofactor / det;
        }
    }
    return result;
}

MatrixPonto4x4 multiplyMatrixPonto(const Matrix4x4& matrixFloat, MatrixPonto4x4& matrixPonto) {
    MatrixPonto4x4 resultMatrix;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Ponto result = {0.0, 0.0, 0.0};

            for (int k = 0; k < 4; ++k) {
                result.setX(result.getX() + matrixFloat.data[i][k] * matrixPonto.data[k][j].getX());
                result.setY(result.getY() + matrixFloat.data[i][k] * matrixPonto.data[k][j].getY());
                result.setZ(result.getZ() + matrixFloat.data[i][k] * matrixPonto.data[k][j].getZ());
            }

            resultMatrix.data[i][j] = result;
        }
    }

    return resultMatrix;
}

MatrixPonto4x4 multiplyPontoMatrix(MatrixPonto4x4& matrixPonto, const Matrix4x4& matrixFloat) {
    MatrixPonto4x4 resultMatrix;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Ponto result = {0.0, 0.0, 0.0};

            for (int k = 0; k < 4; ++k) {
                result.setX(result.getX() + matrixPonto.data[i][k].getX() * matrixFloat.data[k][j]);
                result.setY(result.getY() + matrixPonto.data[i][k].getY() * matrixFloat.data[k][j]);
                result.setZ(result.getZ() + matrixPonto.data[i][k].getZ() * matrixFloat.data[k][j]);
            }

            resultMatrix.data[i][j] = result;
        }
    }

    return resultMatrix;
}

Ponto multiplyF_P_V(const Matrix1x4& matrixF, MatrixPonto4x4& matrixP, const Matrix4x1& matrixV) {

    Ponto result = {0.0, 0.0, 0.0};

    // Multiply matrixF with matrixP
    Ponto temp[4] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            temp[i].setX(temp[i].getX() + matrixF.data[0][j] * matrixP.data[j][i].getX());
            temp[i].setY(temp[i].getY() + matrixF.data[0][j] * matrixP.data[j][i].getY());
            temp[i].setZ(temp[i].getZ() + matrixF.data[0][j] * matrixP.data[j][i].getZ());
        }
    }

    // Multiply the result with matrixV to get the final point
    for (int i = 0; i < 4; ++i) {
        result.setX(result.getX() + temp[i].getX() * matrixV.data[i][0]);
        result.setY(result.getY() + temp[i].getY() * matrixV.data[i][0]);
        result.setZ(result.getZ() + temp[i].getZ() * matrixV.data[i][0]);
    }

    return result;
}


