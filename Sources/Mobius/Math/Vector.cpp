/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Vector.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#include <Mobius/Math/Vector.hpp>

#include <cmath>

namespace Mobius {
namespace Math {

Vector3f::Vector3f(float x, float y, float z) {
    components[0] = x; components[1] = y; components[2] = z;
}

Vector3f::Vector3f() :
    Vector3f(0, 0, 0) {}

Vector3f Vector3f::operator -() {
    // Return the inverted vector.
    return Vector3f(-components[0], -components[1], -components[2]);
}

Vector3f Vector3f::operator +(const Vector3f& other) {
    // Return the sum of the components.
    return Vector3f(components[0] + other[0], components[1] + other[1], components[2] + other[2]);
}

Vector3f& Vector3f::operator +=(const Vector3f& other) {
    // Return the sum of the components.
    components[0] += other.components[0]; components[1] += other.components[1]; components[2] += other.components[2];
    return *this;
}

Vector3f Vector3f::operator -(const Vector3f& other) {
    // Return the substraction of the components.
    return Vector3f(components[0] - other[0], components[1] - other[1], components[2] - other[2]);
}

Vector3f& Vector3f::operator -=(const Vector3f& other) {
    // Return the substraction of the components.
    components[0] -= other.components[0]; components[1] -= other.components[1]; components[2] -= other.components[2];
    return *this;
}

Vector3f Vector3f::operator *(const float value) {
    // Return the multiplication of the components.
    return Vector3f(components[0] * value, components[1] * value, components[2] * value);
}

Vector3f Vector3f::operator /(const float value) {
    // Return the division of the components.
    return Vector3f(components[0] / value, components[1] / value, components[2] / value);
}

float& Vector3f::operator[](const int index) {
    // Return the component.
    return components[index];
}

float const& Vector3f::operator[](const int index) const {
    // Return the component.
    return components[index];
}

float Vector3f::dot(const Vector3f& other) {
    // Return the dot product.
    return (components[0] * other[0]) + (components[1] * other[1]) + (components[2] * other[2]);
}

float Vector3f::magnitude() {
    // Return the magnitude of the vector.
    return sqrt(pow(components[0], 2) + pow(components[1], 2) + pow(components[2], 2));
}

Vector3f Vector3f::normalized() {
    // Return the normalized vector.
    return (*this) / magnitude();
}

Vector3f Vector3f::forward() {
    // Return the forward vector.
    return Vector3f(0, 0, 1);
}

Vector3f Vector3f::right() {
    // Return the right vector.
    return Vector3f(1, 0, 0);
}

Vector3f Vector3f::up() {
    // Return the up vector.
    return Vector3f(0, 1, 0);
}

}
}
