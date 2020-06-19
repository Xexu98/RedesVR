#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string.h>
#include <string>

#include "Serializable.h"

struct Vector2D : public Serializable
{
    double x;
    double y;

    Vector2D();
    Vector2D(const Vector2D &other);
    Vector2D(double x, double y);

    virtual void to_bin();
    virtual int from_bin(char *data);

    void operator+=(const Vector2D &other);
    void operator-=(const Vector2D &other);
    void operator*=(double n);
    void operator/=(double n);
    void operator=(const Vector2D &other);
    bool operator==(const Vector2D &other);
};

Vector2D operator+(const Vector2D &a, const Vector2D &b);
Vector2D operator-(const Vector2D &a, const Vector2D &b);
Vector2D operator*(const Vector2D &a, double n);
Vector2D operator/(const Vector2D &a, double n);

#endif