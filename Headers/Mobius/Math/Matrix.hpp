/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Matrix.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppMatrix
#define _ProjectMobius_hppMatrix

#include <Mobius/Math/Vector.hpp>
#include <Mobius/Math/EulerAxis.hpp>

/**
 * 4x4 floating point matrix.
 * Used to transform Vector3 objects in space.
 */
typedef struct cMB_MATH_Matrix44f {
    // ---  Attributes ---
        // -- Public Attributes --
            /** Main components of the matrix object. */
            float components[16];
    // --- /Attributes ---
} cMB_MATH_Matrix44f;

#ifdef __cplusplus
namespace Mobius {
namespace Math {

/**
 * Helper class for the Matrix object.
 */
class Matrix44f : public cMB_MATH_Matrix44f {
    // ---  Subclasses ---
        /**
         * Row accessor helper for the [] operator.
         */
        class RowAccessor {
            // ---  Methods ---
            public:
                /**
                 * Creates a new RowAccessor object.
                 *
                 * @param mat The matrix to access.
                 * @param row The row of the matrix currently accessed.
                 */
                RowAccessor(Matrix44f * mat, const int row);
            
                /**
                 * Accessor operator.
                 * Returns the requested element from the row.
                 *
                 * @param index The index to get in the row.
                 */
                float& operator [](const int index);
            // --- /Methods ---
            
            // ---  Attributes ---
            private:
                /** Pointer to the matrix for this rowaccessor. */
                Matrix44f * _mat;
                /** Index of the accessed row object. */
                const int _row;
            // --- /Attributes ---
        };
    
        /**
         * Constant version of the RowAccessor.
         */
        class ConstRowAccessor {
            // ---  Methods ---
            public:
                /**
                 * Creates a new RowAccessor object.
                 *
                 * @param mat The matrix to access.
                 * @param row The row of the matrix currently accessed.
                 */
                ConstRowAccessor(const Matrix44f * mat, const int row);
            
                /**
                 * Accessor operator.
                 * Returns the requested element from the row.
                 *
                 * @param index The index to get in the row.
                 */
                float const operator [](const int index) const;
            // --- /Methods ---
            
            // ---  Attributes ---
            private:
                /** Pointer to the matrix for this rowaccessor. */
                const Matrix44f * _mat;
                /** Index of the accessed row object. */
                const int _row;
            // --- /Attributes ---
        };
    // --- /Subclasses ---
    // ---  Methods ---
        // -- Class constructors --
        public:
            /**
             * Creates a new matrix with the given data.
             * Allows the user to set each individual value in the matrix.
             */
            Matrix44f(
                float v00, float v01, float v02, float v03,
                float v10, float v11, float v12, float v13,
                float v20, float v21, float v22, float v23,
                float v30, float v31, float v32, float v33
            );
    
            /**
             * Creates a new matrix.
             * The new matrix will be the identity matrix.
             */
            Matrix44f();
    
            /**
             * Allows the creation of a matrix from a raw array.
             */
            Matrix44f(const float * data);
    
            /**
             * Copy constructor.
             * Duplicates the components over into a new matrix.
             */
            Matrix44f(const cMB_MATH_Matrix44f& copy);

        // -- Operators Overloads --
            /**
             * Invert all the matrix's components.
             *
             * @return The inverted matrix.
             */
            Matrix44f operator -();

            /**
             * Add two matrices' components together.
             *
             * @param other The matrix to add to this object's components.
             * @return The sum of both matrices.
             */
            Matrix44f operator +(const Matrix44f& other);
    
            /**
             * Substract the given matrix to this object's components.
             *
             * @param other The matrix to substract from this object's components.
             * @return The substraction of both matrices.
             */
            Matrix44f operator -(const Matrix44f& other);
    
            /**
             * Performs a left multiplication on the givem matrix.
             *
             * @param right The right hand side of the matrix multiplication.
             * @return The multiplied matrix.
             */
            Matrix44f operator *(const Matrix44f& right);
    
            /**
             * Access the components directly.
             * Returns a RowAccessor object to a nice [x][y] format.
             *
             * @param row The requested row in the data.
             * @return A RowAccessor object to query the column.
             */
            RowAccessor operator[](const int row);
    
            /**
             * Access the components directly.
             * Constant version of the same operator.
             *
             * @param row The requested row in the data.
             * @return A ConstRowAccessor object to query the column.
             */
            ConstRowAccessor const operator[](const int row) const;
    
        // -- Public Methods --
            /**
             * Sets the rotation component of the matrix.
             * Rotates by the given axes in degrees.
             *
             * @param rotation The rotation to apply to this matrix.
             * @return A copy of the matrix rotated by the given value.
             */
            Matrix44f rotate(const EulerAxisXYZf& rotation);
    
            /**
             * Sets the translation component of the matrix.
             * Translate by the given vector amount.
             *
             * @param translate The amount to translate the matrix by.
             * @return A copy of the matrix, translated by the given amount.
             */
            Matrix44f translate(const Vector3f& translate);
    
            /**
             * Sets the scale component of the matrix.
             * Scale by the given amount.
             *
             * @param scale The amount to scale the matrix by.
             * @return A copy of the matrix with the correct scale component.
             */
            Matrix44f scale(const float scale);
    
            /**
             * Sets the scale component of the matrix.
             * Scale by the given amount.
             *
             * @param scale The amount to scale the matrix by.
             * @return A copy of the matrix with the correct scale component.
             */
            Matrix44f scale(const Vector3f& scale);
    
            /**
             * Create a new perspective matrix.
             *
             * @param verticalFov The vertical field of view of the matrix.
             * @param aspect The aspect ratio of the perspective. (Aka. width/height)
             * @param near The distance from the viewer to the near clipping plane.
             * @param far The distance from the viewer to the far clipping plane.
             */
            static Matrix44f makePerspective(float verticalFov, float aspect, float near, float far);
    // --- /Methods ---
};

}
}
#endif

#endif /* _ProjectMobius_hppMatrix */
