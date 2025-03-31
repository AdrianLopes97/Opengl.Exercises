#ifndef APPLY_TRANSFORMATION_TRIANGLE_H
#define APPLY_TRANSFORMATION_TRIANGLE_H

void loadIdentity(float matrix[4][4]);
void createTranslationMatrix(float matrix[4][4], float tx, float ty, float tz);
void createScaleMatrix(float matrix[4][4], float sx, float sy, float sz);
void createRotationMatrixZ(float matrix[4][4], float angle);
void multiplyMatrices(float result[4][4], float a[4][4], float b[4][4]);

#endif