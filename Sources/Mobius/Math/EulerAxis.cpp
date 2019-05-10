//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file EulerAxis.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#include <Mobius/Math/EulerAxis.hpp>

namespace Mobius {
namespace Math {

EulerAxisXYZf::EulerAxisXYZf(float pitch, float yaw, float roll) {
    // Set the components.
    components[0] = pitch; components[1] = yaw; components[2] = roll;
}

EulerAxisXYZf::EulerAxisXYZf() :
    EulerAxisXYZf(0, 0, 0)
{}

EulerAxisXYZf EulerAxisXYZf::operator -() {
    // Return the negated euler axis.
    return EulerAxisXYZf(-components[0], -components[1], -components[2]);
}

EulerAxisXYZf EulerAxisXYZf::operator +(const EulerAxisXYZf& other) {
    // Return the sum of the axes.
    return EulerAxisXYZf(components[0] + other[0], components[1] + other[1], components[2] + other[2]);
}

EulerAxisXYZf& EulerAxisXYZf::operator +=(const EulerAxisXYZf& other) {
    // Return the sum of the axes.
    components[0] += other.components[0]; components[1] += other.components[1]; components[2] += other.components[2];
    return *this;
}

EulerAxisXYZf EulerAxisXYZf::operator -(const EulerAxisXYZf& other) {
    // Return the substract of the axes.
    return EulerAxisXYZf(components[0] - other[0], components[1] - other[1], components[2] - other[2]);
}

EulerAxisXYZf& EulerAxisXYZf::operator -=(const EulerAxisXYZf& other) {
    // Return the sum of the axes.
    components[0] -= other.components[0]; components[1] -= other.components[1]; components[2] -= other.components[2];
    return *this;
}

EulerAxisXYZf EulerAxisXYZf::operator *(const float value) {
    // Return the multiplication of the axes.
    return EulerAxisXYZf(components[0] * value, components[1] * value, components[2] * value);
}

EulerAxisXYZf EulerAxisXYZf::operator /(const float value) {
    // Return the division of the axes.
    return EulerAxisXYZf(components[0] / value, components[1] / value, components[2] / value);
}

float& EulerAxisXYZf::operator[](const int index) {
    return components[index];
}

float const& EulerAxisXYZf::operator[](const int index) const {
    return components[index];
}

}
}
