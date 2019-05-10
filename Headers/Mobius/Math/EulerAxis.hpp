
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file EulerAxis.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppEulerAxis
#define _ProjectMobius_hppEulerAxis

/**
 * 3D EulerAxis rotation representation.
 * Used to represent a rotation around the XY and Z axes.
 */
typedef struct cMB_MATH_EulerAxisXYZf {
    // ---  Attributes ---
        // -- Public Attributes --
            /** Main components of the vector object. */
            float components[3];
    // --- /Attributes ---
} cMB_MATH_EulerAxisXYZf;


#ifdef __cplusplus
namespace Mobius {
namespace Math {

/**
 * Helper class for the EulerAxis object.
 */
class EulerAxisXYZf : public cMB_MATH_EulerAxisXYZf {
    // ---  Methods ---
    public:
        // -- Class constructors --
            /**
             * Creates a new euler axis with the given data.
             *
             * @param pitch The rotation around the x axis.
             * @param yaw The rotation around the y axis.
             * @param roll The rotation around the z axis.
             */
            EulerAxisXYZf(float pitch, float yaw, float roll);

            /**
             * Creates a new euler axis with all components set to 0.
             */
            EulerAxisXYZf();

            /**
             * Creates a new euler axis from a base struct copy.
             */
            EulerAxisXYZf(const cMB_MATH_EulerAxisXYZf& copy);

        // -- Operators Overloads --
            /**
             * Invert a euler axis' components.
             *
             * @return The inverted euler axis.
             */
            EulerAxisXYZf operator -();

            /**
             * Add two euler axis' components together.
             *
             * @param other The euler axis to add to this object's components.
             * @return The sum of both euler axes.
             */
            EulerAxisXYZf operator +(const EulerAxisXYZf& other);

            /**
             * Add two euler axis' components together.
             *
             * @param other The euler axis to add to this object's components.
             * @return The modified object.
             */
            EulerAxisXYZf& operator +=(const EulerAxisXYZf& other);

            /**
             * Substract the given euler axis to this object's components.
             *
             * @param other The euler axis to substract from this object's components.
             * @return The substraction of both euler axes.
             */
            EulerAxisXYZf operator -(const EulerAxisXYZf& other);

            /**
             * Substract the given euler axis to this object's components.
             *
             * @param other The euler axis to substract from this object's components.
             * @return The modified object.
             */
            EulerAxisXYZf& operator -=(const EulerAxisXYZf& other);

            /**
             * Multiply the euler axis' component by the given value.
             *
             * @param value The value to multiply the euler axis' components by.
             * @return The multiplied euler axis.
             */
            EulerAxisXYZf operator *(const float value);

            /**
             * Divide the euler axis' component by the given value.
             *
             * @param value The value to divide the euler axis' components by.
             * @return The divided euler axis.
             */
            EulerAxisXYZf operator /(const float value);

            /**
             * Access the components directly.
             * Simplifies working with EulerAxisXYZf objects.
             *
             * @param index The requested data index.
             * @return The requested object.
             */
            float& operator[](const int index);

            /**
             * Const version of the accessing operator.
             * Simplifies working with EulerAxisXYZf objects.
             *
             * @param index The requested data index.
             * @return The requested object.
             */
            float const& operator[](const int index) const;
    // --- /Methods ---
};

}
}
#endif


#endif /* _ProjectMobius_hppEulerAxis */
