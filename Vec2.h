#pragma once

#ifndef Vec2_H
#define Vec2_H

class Vec2 {
public:
	Vec2();
	Vec2(double _x, double _y);
	Vec2& operator=(const Vec2& v);
	Vec2& operator=(const double& v);
	Vec2& operator+=(const Vec2& v);
	Vec2& operator-=(const Vec2& v);
	Vec2& operator*=(double k);
	Vec2& operator/=(double k);
	Vec2 operator+();
	Vec2 operator-();

	double distanceFrom(Vec2& _vec2) const;
	double dot(Vec2& _vec2) const;
	double cross(Vec2& _vec2) const;
	double cos(Vec2& _vec2) const;
	double sin(Vec2& _vec2) const;
	double length() const;
	double angle() const;
	double angle(Vec2& _vec2) const;

	void setFromAngle(const double& _angle);	//単位ベクトルを生成

	void rotate(const double& _angle);
	Vec2 rotated(const double& _angle) const;

	void normalize();
	Vec2 normalized() const;


	double x;
	double y;
};


//二項演算子
Vec2 operator+(const Vec2& u, const Vec2& v);

Vec2 operator-(const Vec2& u, const Vec2& v);

Vec2 operator*(const Vec2& v, double k);
Vec2 operator*(double k, const Vec2& v);
Vec2 operator/(const Vec2& v, double k);


#endif
