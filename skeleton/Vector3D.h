#pragma once

#include <cmath>
#include <iostream>

template <typename T = float>
class Vector3D {
public:
    T x; // Componente X del vector
    T y; // Componente Y del vector
    T z; // Componente Z del vector

    // Constructor por defecto que inicializa el vector en (0 0 0)
    Vector3D() noexcept : x(0), y(0), z(0) {}

    // Constructor que inicializa el vector con componentes especificas
    Vector3D(T xComponent, T yComponent, T zComponent) noexcept
        : x(xComponent), y(yComponent), z(zComponent) {}

    // Constructor de copia
    Vector3D(const Vector3D<T>& v) noexcept = default;

    // Constructor de movimiento
    Vector3D(Vector3D<T>&& v) noexcept = default;

    // Metodo para calcular la magnitud longitud del vector
    float getMagnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Metodo que devuelve una version normalizada del vector
    //Vector3D<T> GetNormalized() const {
    //    float magnitude = getMagnitude();
    //    return (magnitude > 0) ? Vector3D<T>(x / magnitude, y / magnitude, z / magnitude) : Vector3D<T>();
    //}

    // Normaliza el vector modificando sus componentes
    void Normalize() {
        float magnitude = getMagnitude();
        if (magnitude > 0) {
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
        }
    }

    // Metodo estatico que calcula el producto punto entre dos vectores
    static T Dot(const Vector3D<T>& v1, const Vector3D<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    // Metodo estatico que calcula el producto cruz entre dos vectores
    static Vector3D<T> Cross(const Vector3D<T>& v1, const Vector3D<T>& v2) {
        return Vector3D<T>(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        );
    }

    // Escala el vector multiplicando cada componente por un escalar
    void Scale(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }

    // Metodo estatico que calcula el angulo entre dos vectores en grados
    static float Angle(const Vector3D<T>& v1, const Vector3D<T>& v2) {
        return std::acos(Dot(v1.GetNormalized(), v2.GetNormalized())) * 180.0f / M_PI;
    }

    // Operador de asignacion copia
    Vector3D<T>& operator=(const Vector3D<T>& other) = default;

    // Operador de suma
    Vector3D<T> operator+(const Vector3D<T>& other) const {
        return Vector3D<T>(x + other.x, y + other.y, z + other.z);
    }

    // Operador de resta
    Vector3D<T> operator-(const Vector3D<T>& other) const {
        return Vector3D<T>(x - other.x, y - other.y, z - other.z);
    }

    // Operador de multiplicacion por un escalar
    Vector3D<T> operator*(const T& scalar) const {
        return Vector3D<T>(x * scalar, y * scalar, z * scalar);
    }

    // Operador de multiplicacion producto cruz con otro vector
    Vector3D<T> operator*(const Vector3D<T>& other) const {
        return Cross(*this, other);
    }

    // Operador de division por un escalar
    Vector3D<T> operator/(const T& scalar) const {
        return Vector3D<T>(x / scalar, y / scalar, z / scalar);
    }

    // Operador de igualdad
    bool operator==(const Vector3D<T>& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    // Operador de desigualdad
    bool operator!=(const Vector3D<T>& other) const {
        return !(*this == other);
    }

    // Sobrecarga del operador de salida para imprimir el vector
    friend std::ostream& operator<<(std::ostream& os, const Vector3D<T>& v) {
        os << "[ " << v.x << " | " << v.y << " | " << v.z << " ]\n";
        return os;
    }
};
