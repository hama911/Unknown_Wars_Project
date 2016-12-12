#pragma once

#include"DxLib.h"
#include"Vec2.h"

#ifndef Vec3_H
#define Vec3_H

class Vec3
{
public:
	Vec3();
	Vec3(Vec2 _vec2);
	Vec3(VECTOR _vec);
	Vec3(double _x, double _y, double _z);
	Vec3& operator=(const Vec3& v);
	Vec3& operator+=(const Vec3& v);
	Vec3& operator-=(const Vec3& v);
	Vec3& operator*=(double k);
	Vec3& operator/=(double k);
	Vec3 operator+();
	Vec3 operator-();

	void rotateY(const double& _angle);
	void normalize();
	Vec3 normalized() const;
	double length() const;

	VECTOR VEC() const;

	double x;
	double y;
	double z;
};

//ìÒçÄââéZéq
Vec3 operator+(const Vec3& u, const Vec3& v);

Vec3 operator-(const Vec3& u, const Vec3& v);

Vec3 operator*(const Vec3& v, double k);
Vec3 operator*(double k, const Vec3& v);
Vec3 operator/(const Vec3& v, double k);


#endif
