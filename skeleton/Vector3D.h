#pragma once

#include <cmath>

class Vector3D {
public:
    // Constructor por defecto
    Vector3D();

    // Constructor parametrizado
    Vector3D(float nx, float ny, float nz);

    // M�todo para obtener el m�dulo del vector
    float magnitude() const;

    // M�todo para obtener el cuadrado del m�dulo
    float magnitudeSquared() const;

    // M�todo para normalizar el vector
    Vector3D normalize() const;

    // Sobrecarga del operador de asignaci�n
    Vector3D& operator=(const Vector3D& p);

    // Sobrecarga del operador suma
    Vector3D operator+(const Vector3D& v) const;

    // Sobrecarga del operador resta
    Vector3D operator-(const Vector3D& v) const;

    // Sobrecarga del operador multiplicaci�n por escalar
    Vector3D operator*(float f) const;

    // Sobrecarga del operador *= para multiplicar por escalar y asignar
    Vector3D& operator*=(float f);

    // Producto escalar (dot product)
    float dot(const Vector3D& v) const;

    // Producto vectorial (cross product)
    Vector3D cross(const Vector3D& v) const;

private:
    float x, y, z;
};
