#include "Vector3D.h"
#include <cmath>

// Constructor por defecto
Vector3D::Vector3D() : x(0), y(0), z(0) {}

// Constructor parametrizado
Vector3D::Vector3D(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}

// Método para obtener el módulo del vector
float Vector3D::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Método para obtener el cuadrado del módulo
float Vector3D::magnitudeSquared() const {
    return x * x + y * y + z * z;
}

// Método para normalizar el vector
Vector3D Vector3D::normalize() const {
    float mag = magnitude();
    if (mag == 0) return Vector3D(0, 0, 0); // Evitar división por 0
    return Vector3D(x / mag, y / mag, z / mag);
}

// Sobrecarga del operador de asignación
Vector3D& Vector3D::operator=(const Vector3D& p) {
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}

// Sobrecarga del operador suma
Vector3D Vector3D::operator+(const Vector3D& v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

// Sobrecarga del operador resta
Vector3D Vector3D::operator-(const Vector3D& v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

// Sobrecarga del operador multiplicación por escalar
Vector3D Vector3D::operator*(float f) const {
    return Vector3D(x * f, y * f, z * f);
}

// Sobrecarga del operador *= para multiplicar por escalar y asignar
Vector3D& Vector3D::operator*=(float f) {
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

// Producto escalar (dot product)
float Vector3D::dot(const Vector3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

// Producto vectorial (cross product)
Vector3D Vector3D::cross(const Vector3D& v) const {
    return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}
