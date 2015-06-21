/* 
 * File:   Vector.h
 * Author: dorian
 * https://github.com/simplerr/Project-Mayhem/tree/178acb0ff06d60c99b1891e4e40644ce8a056764
 *
 * Created on 23 de abril de 2015, 13:20
 */

#ifndef VECTOR_H
#define	VECTOR_H

#include <assert.h>
#include <math.h>

/**
 * Clase representando un vector de dos puntos y en el que se 
 * han sobreescrito operadores a conveniencia para su uso en colisiones.
 */
class Vector {
public:

    /**
     * default constructor.
     * does nothing for speed.
     */
    Vector() {
        x = 0;
        y = 0;
    };

    /**
     * construct vector from x,y components.
     * @param x
     * @param y
     */
    Vector(float x, float y) {
        this->x = x;
        this->y = y;
    };

    /**
     * set vector to zero.
     */
    void zero() {
        x = 0;
        y = 0;
    }

    /**
     * negate vector.
     */
    void negate() {
        x = -x;
        y = -y;
    }

    /**
     * add another vector to this vector.
     * @param vector
     */
    void add(const Vector &vector) {
        x += vector.x;
        y += vector.y;
    }

    /**
     * subtract another vector from this vector.
     * @param vector
     */
    void subtract(const Vector &vector) {
        x -= vector.x;
        y -= vector.y;
    }

    /**
     * multiply this vector by a scalar.
     * @param scalar
     */
    void multiply(float scalar) {
        x *= scalar;
        y *= scalar;
    }

    /**
     * divide this vector by a scalar.
     * @param scalar
     */
    void divide(float scalar) {
        assert(scalar != 0);
        const float inv = 1.0f / scalar;
        x *= inv;
        y *= inv;
    }

    /**
     * calculate dot product of this vector with another vector.
     * @param vector
     * @return 
     */
    float dot(const Vector &vector) const {
        return x * vector.x + y * vector.y;
    }

    Vector cross(float s) {
        return Vector(-s * y, s * x);
    }

    /**
     * calculate length of vector squared
     * @return 
     */
    float lengthSquared() const {
        return x * x + y*y;
    }

    /**
     * calculate length of vector.
     * @return 
     */
    float length() const {
        return sqrt(x * x + y * y);
    }

    /**
     * normalize vector and return reference to normalized self.
     * @return 
     */
    Vector& normalize() {
        const float magnitude = sqrt(x * x + y * y);
        if (magnitude > EPSILON) {
            const float scale = 1.0f / magnitude;
            x *= scale;
            y *= scale;
        }
        return *this;
    }

    /**
     * return unit length vector
     * @return 
     */
    Vector unit() const {
        Vector vector(*this);
        vector.normalize();
        return vector;
    }

    /**
     * test if vector is normalized.
     * @return 
     */
    bool normalized() const {
        return equal(length(), 1);
    }

    /**
     * equals operator
     * @param other
     * @return 
     */
    bool operator==(const Vector &other) const {
        if (equal(x, other.x) && equal(y, other.y))
            return true;
        else
            return false;
    }

    /**
     * not equals operator
     * @param other
     * @return 
     */
    bool operator!=(const Vector &other) const {
        return !(*this == other);
    }

    /**
     * element access
     * @param i
     * @return 
     */
    float& operator[](int i) {
        assert(i >= 0);
        assert(i <= 2);
        return *(&x + i);
    }

    /**
     * element access (const)
     * @param i
     * @return 
     */
    const float& operator[](int i) const {
        assert(i >= 0);
        assert(i <= 2);
        return *(&x + i);
    }

    friend inline Vector operator-(const Vector &a);
    friend inline Vector operator+(const Vector &a, const Vector &b);
    friend inline Vector operator-(const Vector &a, const Vector &b);
    //    friend inline Vector operator*(const Vector &a, const Vector &b);
    friend inline Vector& operator+=(Vector &a, const Vector &b);
    friend inline Vector& operator-=(Vector &a, const Vector &b);
    //    friend inline Vector& operator*=(Vector &a, const Vector &b);
    //
    friend inline Vector operator*(const Vector &a, float s);
    friend inline Vector operator/(const Vector &a, float s);
    friend inline Vector& operator*=(Vector &a, float s);
    friend inline Vector& operator/=(Vector &a, float s);
    friend inline Vector operator*(float s, const Vector &a);
    friend inline Vector& operator*=(float s, Vector &a);

    float x; ///< x component of vector
    float y; ///< y component of vector

private:
    constexpr static const float EPSILON = 0.00001f; ///< floating point EPSILON for single precision.

    inline bool equal(float a, float b) const {
        const float d = a - b;
        if (d < EPSILON && d>-EPSILON)
            return true;
        else
            return false;
    }
};

inline Vector operator-(const Vector &a) {
    return Vector(-a.x, -a.y);
}

inline Vector operator+(const Vector &a, const Vector &b) {
    return Vector(a.x + b.x, a.y + b.y);
}

inline Vector operator-(const Vector &a, const Vector &b) {
    return Vector(a.x - b.x, a.y - b.y);
}

inline Vector& operator+=(Vector &a, const Vector &b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

inline Vector& operator-=(Vector &a, const Vector &b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

inline Vector operator*(const Vector &a, float s) {
    return Vector(a.x*s, a.y * s);
}

inline Vector operator/(const Vector &a, float s) {
    assert(s != 0);
    return Vector(a.x / s, a.y / s);
}

inline Vector& operator*=(Vector &a, float s) {
    a.x *= s;
    a.y *= s;
    return a;
}

inline Vector& operator/=(Vector &a, float s) {
    assert(s != 0);
    a.x /= s;
    a.y /= s;
    return a;
}

inline Vector operator*(float s, const Vector &a) {
    return Vector(a.x*s, a.y * s);
}

inline Vector& operator*=(float s, Vector &a) {
    a.x *= s;
    a.y *= s;
    return a;
}

#endif	/* VECTOR_H */

