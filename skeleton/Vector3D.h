#pragma once


#include <math.h>

class Vector3D
{
	float x, y, z;

	Vector3D(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {
		
	}

	float magnitudeSquared() const
	{
		return x * x + y * y + z * z;
	}

	Vector3D& operator=(const Vector3D& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
	}


	Vector3D operator+(const Vector3D& v) const
	{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	/**
	\brief vector difference
	*/
	Vector3D  operator-(const Vector3D& v) const
	{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	/**
	\brief scalar post-multiplication
	*/
	Vector3D operator*(float f) const
	{
		return Vector3D(x * f, y * f, z * f);
	}

	Vector3D& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}


	float dot(const Vector3D& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vector3D cross(const Vector3D& v) const
	{
		return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}


};

