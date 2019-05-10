/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Vector.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppVector
#define _ProjectMobius_hppVector

/**
 * 3D Vector object.
 * Used to represent a point in 3D space.
 */
typedef struct cMB_MATH_Vector3f {
    // ---  Attributes ---
        // -- Public Attributes --
            /** Main components of the vector object. */
            float components[3];
    // --- /Attributes ---
} cMB_MATH_Vector3f;

#ifdef __cplusplus
namespace Mobius {
namespace Math {

/**
 * Helper class for the Vector object.
 */
class Vector3f : public cMB_MATH_Vector3f {
    // ---  Methods ---
    public:
        // -- Class constructors --
            /**
             * Creates a new vector with the given data.
             *
             * @param x The x component of the vector.
             * @param y The y component of the vector.
             * @param z The z component of the vector.
             */
            Vector3f(float x, float y, float z);

            /**
             * Creates a new vector with all components set to 0.
             */
            Vector3f();

            /**
             * Creates a new vector copied from the base struct.
             */
            Vector3f(const cMB_MATH_Vector3f& copy);

        // -- Operators Overloads --
            /**
             * Invert a Vector's components.
             *
             * @return The inverted vector.
             */
            Vector3f operator -();

            /**
             * Add two vector's components together.
             *
             * @param other The vector to add to this object's components.
             * @return The sum of both vectors.
             */
            Vector3f operator +(const Vector3f& other);
    
            /**
             * Add two vector's components together.
             *
             * @param other The vector to add to this object's components.
             * @return The modified vector.
             */
            Vector3f& operator +=(const Vector3f& other);

            /**
             * Substract the given vector to this object's components.
             *
             * @param other The vector to substract from this object's components.
             * @return The substraction of both vectors.
             */
            Vector3f operator -(const Vector3f& other);
    
            /**
             * Substract the given vector to this object's components.
             *
             * @param other The vector to substract from this object's components.
             * @return The modified vector.
             */
            Vector3f& operator -=(const Vector3f& other);

            /**
             * Multiply the vector's component by the given value.
             *
             * @param value The value to multiply the vector's components by.
             * @return The multiplied vector.
             */
            Vector3f operator *(const float value);

            /**
             * Divide the vector's component by the given value.
             *
             * @param value The value to divide the vector's components by.
             * @return The divided vector.
             */
            Vector3f operator /(const float value);

            /**
             * Access the components directly.
             * Simplifies working with Vector3f objects.
             *
             * @param index The requested data index.
             * @return The requested object.
             */
            float& operator[](const int index);

            /**
             * Const version of the accessing operator.
             * Simplifies working with Vector3f objects.
             *
             * @param index The requested data index.
             * @return The requested object.
             */
            float const& operator[](const int index) const;

        // -- Public Methods --
            /**
             * Return the dot product of the two given vectors.
             *
             * @param other The other vector to dot this object with.
             * @return The dot product of both vectors.
             */
            float dot(const Vector3f& other);

            /**
             * Return the magnitude of the given vector.
             *
             * @return The magnitude of the vector object.
             */
            float magnitude();

            /**
             * Return a normalized version of the vector.
             *
             * @return A copy of the vector, normalized.
             */
            Vector3f normalized();

        // -- Static Methods --
            /**
             * Returns the forward vector (aka. +1 on the z axis.)
             */
            static Vector3f forward();

            /**
             * Returns the right vector (aka. +1 on the x axis.)
             */
            static Vector3f right();

            /**
             * Returns the up vector (aka. +1 on the y axis.)
             */
            static Vector3f up();
    // --- /Methods ---
};

}
}
#endif

#endif /* _ProjectMobius_hppVector */
