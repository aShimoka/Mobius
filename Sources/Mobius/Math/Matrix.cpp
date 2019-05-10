//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Matrix.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#include <Mobius/Math/Matrix.hpp>

#include <cmath>

#define PI 3.14159265359

namespace Mobius {
namespace Math {

/**
 * Simple helpers for degree-sin and cosine.
 */
float __degSin(float v) { return sin(v * PI / 180.f); }
float __degCos(float v) { return cos(v * PI / 180.f); }
float __degTan(float v) { return tan(v * PI / 180.f); }

Matrix44f::RowAccessor::RowAccessor(Matrix44f * mat, const int row) :
    _mat(mat), _row(row)
{}

float& Matrix44f::RowAccessor::operator [](const int index) {
    // Return the value in the matrix.
    return _mat->components[_row * 4 + index];
}

Matrix44f::ConstRowAccessor::ConstRowAccessor(const Matrix44f * mat, const int row) :
    _mat(mat), _row(row)
{}

float const Matrix44f::ConstRowAccessor::operator [](const int index) const {
    // Return the value in the matrix.
    return _mat->components[_row * 4 + index];
}

Matrix44f::Matrix44f(
    float v00, float v01, float v02, float v03,
    float v10, float v11, float v12, float v13,
    float v20, float v21, float v22, float v23,
    float v30, float v31, float v32, float v33
) {
    // Set all the values in the components array.
    components[0x0] = v00; components[0x1] = v01; components[0x2] = v02; components[0x3] = v03;
    components[0x4] = v10; components[0x5] = v11; components[0x6] = v12; components[0x7] = v13;
    components[0x8] = v20; components[0x9] = v21; components[0xA] = v22; components[0xB] = v23;
    components[0xC] = v30; components[0xD] = v31; components[0xE] = v32; components[0xF] = v33;
}

Matrix44f::Matrix44f() {
    // Create the identity matrix.
    components[0x0] = 1; components[0x1] = 0; components[0x2] = 0; components[0x3] = 0;
    components[0x4] = 0; components[0x5] = 1; components[0x6] = 0; components[0x7] = 0;
    components[0x8] = 0; components[0x9] = 0; components[0xA] = 1; components[0xB] = 0;
    components[0xC] = 0; components[0xD] = 0; components[0xE] = 0; components[0xF] = 1;
}

Matrix44f::Matrix44f(const float * data) {
    // Set the data of the matrix.
    const float * d = data; float * m = components;
    for (; d < data + 16; d++, m++) *m = *d;
}

Matrix44f::Matrix44f(const cMB_MATH_Matrix44f& copy) :
    Matrix44f(copy.components) // Call the array constructor.
{}

Matrix44f Matrix44f::operator -() {
    // Copy the matrix.
    Matrix44f copy = Matrix44f(*this);
    
    // Invert all the values.
    for (float * m = copy.components; m < copy.components + 16; m++) *m = -(*m);
    
    // Return the copy.
    return copy;
}

Matrix44f Matrix44f::operator +(const Matrix44f& other) {
    // Create the output matrix.
    Matrix44f copy = Matrix44f(*this);
    
    // Add all the values together.
    const float * oM = other.components; float * cM = copy.components;
    for (; oM < other.components + 16; oM++, cM++) *cM += *oM;
    
    // Return the copy.
    return copy;
}

Matrix44f Matrix44f::operator -(const Matrix44f& other) {
    // Create the output matrix.
    Matrix44f copy = Matrix44f(*this);
    
    // Add all the values together.
    const float * oM = other.components; float * cM = copy.components;
    for (; oM < other.components + 16; oM++, cM++) *cM -= *oM;
    
    // Return the copy.
    return copy;
}

Matrix44f Matrix44f::operator *(const Matrix44f& right) {
    // Create the output matrix.
    Matrix44f copy = Matrix44f(*this);
    
    // Perform the matrix multiplication.
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
        copy[i][j] =
            (*this)[i][0] * right[0][j] +
            (*this)[i][1] * right[1][j] +
            (*this)[i][2] * right[2][j] +
            (*this)[i][3] * right[3][j];
    }
    
    // Return the copy.
    return copy;
}

Matrix44f::RowAccessor Matrix44f::operator[] (const int row) {
    // Return the RowAccessor.
    return Matrix44f::RowAccessor(this, row);
}

Matrix44f::ConstRowAccessor const Matrix44f::operator[] (const int row) const {
    // Return the ConstRowAccessor.
    return Matrix44f::ConstRowAccessor(this, row);
}

Matrix44f Matrix44f::rotate(const EulerAxisXYZf& rotation) {
    // Compute all the sines and cosines.
    float sx = __degSin(rotation[0]); float cx = __degCos(rotation[0]);
    float sy = __degSin(rotation[1]); float cy = __degCos(rotation[1]);
    float sz = __degSin(rotation[2]); float cz = __degCos(rotation[2]);
    
    // Create the new matrix.
    return (*this) * Matrix44f(
                          cy *  cz,                   -cy *  sz,        sy, 0,
        sx *  sy *  cz +  cx *  sz, -sx *  sy *  sz +  cx *  cz, -sx *  cy, 0,
       -cx *  sy *  cz +  sx *  sz,  cx *  sy *  sz +  sx *  cz,        cx *  cy, 0,
                                0,                      0,               0, 1
    );
}

Matrix44f Matrix44f::translate(const Vector3f& translate) {
    // Return the added matrices.
    return (*this) + Matrix44f (
                   0,            0,            0,            0,
                   0,            0,            0,            0,
                   0,            0,            0,            0,
        translate[0], translate[1], translate[2],            1
    );
}

Matrix44f Matrix44f::scale(const float scale) {
    // Return the multiplied matrices.
    return Matrix44f (
        scale,     0,      0,    0,
             0, scale,     0,    0,
             0,     0, scale,    0,
             0,     0,     0,    1
    ) * (*this);
}

Matrix44f Matrix44f::scale(const Vector3f& scale) {
    // Return the multiplied matrices.
    return Matrix44f (
        scale[0],       0,        0,      0,
               0, scale[1],       0,      0,
               0,       0, scale[2],      0,
               0,       0,        0,      1
    ) * (*this);
}

Matrix44f Matrix44f::makePerspective(float verticalFov, float aspect, float near, float far) {
    // Prepare the resulting matrix.
    Matrix44f result;
    
    // Get the tan of half of the fov.
    float tanTheta = __degTan(verticalFov / 2);
    
    // Compute the limits of the frustrum.
    float top = tanTheta * near;
    float right = top * aspect;
    float bottom = -top;
    float left = -right;
    
    // Compute the frustrum.
    result.components[0] = (2.f * near) / ( right - left);
    result.components[1] = 0.f;
    result.components[2] = 0.f;
    result.components[3] = 0.f;
    
    result.components[4] = 0.f;
    result.components[5] = (2.f * near) / (top - bottom);
    result.components[6] = 0.f;
    result.components[7] = 0.f;
    
    result.components[8] = (right + left) / (right - left);
    result.components[9] = (top + bottom) / (top - bottom);
    result.components[10] = -(far + near) / (far - near);
    result.components[11] = -1.f;
    
    result.components[12] = 0.f;
    result.components[13] = 0.f;
    result.components[14] = -(2.f * far * near) / (far - near);
    result.components[15] = 0.f;
    
    // Return the resulting matrix;
    return result;
}

}
}
