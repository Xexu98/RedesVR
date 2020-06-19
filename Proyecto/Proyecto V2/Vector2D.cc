#include "Vector2D.h"

Vector2D::Vector2D(double x, double y) : Serializable(), x(x), y(y) {}

Vector2D::Vector2D() : Serializable(), x(0.0), y(0.0) {}

Vector2D::Vector2D(const Vector2D &other) : Serializable(), x(other.x), y(other.y) {}

void Vector2D::to_bin()
{
    alloc_data(2 * sizeof(double));

    memcpy(_data, &x, sizeof(double));
    char *aux = _data + sizeof(double);

    memcpy(aux, &y, sizeof(double));
}

int Vector2D::from_bin(char *data)
{
    try
    {
        alloc_data(2 * sizeof(double));

        //Reconstruir la clase usando el buffer _data
        memcpy(&x, data, sizeof(double));
        char *aux = data + sizeof(double);

        memcpy(&y, aux, sizeof(double));

        return 0;
    }
    catch (std::exception e)
    {
        return -1;
    }
}

void Vector2D::operator+=(const Vector2D &other)
{
    this->x += other.x;
    this->y += other.y;
}

void Vector2D::operator-=(const Vector2D &other)
{
    this->x -= other.x;
    this->y -= other.y;
}

void Vector2D::operator*=(double n)
{
    this->x *= n;
    this->y *= n;
}

void Vector2D::operator/=(double n)
{
    this->x /= n;
    this->y /= n;
}

void Vector2D::operator=(const Vector2D &other)
{
    this->x = other.x;
    this->y = other.y;
}

bool Vector2D::operator==(const Vector2D &other)
{
    return x == other.x && y == other.y;
}

Vector2D operator+(const Vector2D &a, const Vector2D &b)
{
    return Vector2(a.x + b.x, a.y + b.y);
}

Vector2D operator-(const Vector2D &a, const Vector2D &b)
{
    return Vector2(a.x - b.x, a.y - b.y);
}

Vector2D operator*(const Vector2D &a, double n)
{
    return Vector2(a.x * n, a.y * n);
}

Vector2D operator/(const Vector2D &a, double n)
{
    return Vector2(a.x / n, a.y / n);
}