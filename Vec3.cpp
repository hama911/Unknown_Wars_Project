#include"Vec3.h"
#include"Vec2.h"
#include"DxLib.h"
#include"AdvancedMath.h"

Vec3::Vec3() : x(0), y(0), z(0) {};
Vec3::Vec3(Vec2 _vec2)
{
	x = _vec2.x;
	y = _vec2.y;
	z = 0;
};
Vec3::Vec3(VECTOR _vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;
};
Vec3::Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

VECTOR Vec3::VEC() const
{
	return VGet(float(x), float(y), float(z));
}

Vec3& Vec3::operator=(const Vec3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}
Vec3& Vec3::operator+=(const Vec3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}
Vec3& Vec3::operator-=(const Vec3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}
Vec3& Vec3::operator*=(double k)
{
	this->x *= k;
	this->y *= k;
	this->z *= k;
	return *this;
}
Vec3& Vec3::operator/=(double k)
{
	this->x /= k;
	this->y /= k;
	this->z /= k;
	return *this;
}
Vec3 Vec3::operator+()
{
	return *this;
}
Vec3 Vec3::operator-()
{
	return Vec3(-x, -y, -z);
}

void Vec3::normalize()
{
	*this /= length();
}

void Vec3::rotateY(const double& _angle)
{
	Vec3 newVec3;
	newVec3.x = x*Cos(_angle) - z*Sin(_angle);
	newVec3.y = y;
	newVec3.z = x*Sin(_angle) + z*Cos(_angle);
	*this = newVec3;
}

Vec3 Vec3::normalized() const
{
	return *this / length();
}

double Vec3::length() const
{
	return Sqrt(Pow2(x) + Pow2(y) + Pow2(z));
}

//ìÒçÄââéZéq
Vec3 operator+(const Vec3& u, const Vec3& v)
{
	Vec3 w;
	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	return w;
}

Vec3 operator-(const Vec3& u, const Vec3& v)
{
	Vec3 w;
	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
	return w;
}

Vec3 operator*(const Vec3& v, double k)
{
	Vec3 w;
	w.x = v.x * k;
	w.y = v.y * k;
	w.z = v.z * k;
	return w;
}
Vec3 operator*(double k, const Vec3& v)
{
	Vec3 w;
	w.x = v.x * k;
	w.y = v.y * k;
	w.z = v.z * k;
	return w;
}
Vec3 operator/(const Vec3& v, double k)
{
	Vec3 w;
	w.x = v.x / k;
	w.y = v.y / k;
	w.z = v.z / k;
	return w;
}