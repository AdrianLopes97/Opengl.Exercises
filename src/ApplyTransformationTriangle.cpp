#include <cmath>
#include "ApplyTransformationTriangle.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to create an identity matrix
void loadIdentity(float matrix[4][4]) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            matrix[i][j] = (i == j) ? 1.0f : 0.0f;
}

// Function to create a translation matrix
void createTranslationMatrix(float matrix[4][4], float tx, float ty, float tz) {
    loadIdentity(matrix);
    matrix[3][0] = tx;
    matrix[3][1] = ty;
    matrix[3][2] = tz;
}

// Function to create a scale matrix
void createScaleMatrix(float matrix[4][4], float sx, float sy, float sz) {
    loadIdentity(matrix);
    matrix[0][0] = sx;
    matrix[1][1] = sy;
    matrix[2][2] = sz;
}

// Function to create a rotation matrix around the Z axis
void createRotationMatrixZ(float matrix[4][4], float angle) {
    loadIdentity(matrix);
    float radians = angle * M_PI / 180.0f;
    matrix[0][0] = cos(radians);
    matrix[0][1] = -sin(radians);
    matrix[1][0] = sin(radians);
    matrix[1][1] = cos(radians);
}

void multiplyMatrices(float result[4][4], float a[4][4], float b[4][4]) {
    float temp[4][4] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                temp[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    // Copy the result to the final array
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            result[i][j] = temp[i][j];
}