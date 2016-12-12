#include "Vec2.h"
#include <math.h>
#include "AdvancedMath.h"

Vec2::Vec2() :x(0), y(0)
{
}

Vec2::Vec2(double _x, double _y) : x(_x), y(_y)
{
}
//������Z�q�̒�`
Vec2& Vec2::operator=(const Vec2& v) {
	this->x = v.x;	this->y = v.y;
	return *this;
}
//������Z�q�̒�`
Vec2& Vec2::operator=(const double& v) {
	this->x = v;
	this->y = 0.0;
	return *this;
}
// +=�̒�`
Vec2& Vec2::operator+=(const Vec2& v) {
	this->x += v.x;	this->y += v.y;	return *this;
}
// -=�̒�`
Vec2& Vec2::operator-=(const Vec2& v) {
	this->x -= v.x;	this->y -= v.y;	return *this;
}
// *=�̒�`
Vec2& Vec2::operator*=(double k) {
	this->x *= k;	this->y *= k;	return *this;
}
// /=�̒�`
Vec2& Vec2::operator/=(double k) {
	this->x /= k;	this->y /= k;	return *this;
}

//+�̒�`:	+v
Vec2 Vec2::operator+() {
	return *this;
}
//-�̒�`:	-v
Vec2 Vec2::operator-() {
	return Vec2(-x, -y);
}

//�����̒�`
double Vec2::distanceFrom(Vec2& _vec2) const
{
	return Sqrt(Pow2(_vec2.x - this->x) + Pow2(_vec2.y - this->y));
}

//���ς̒�`
double Vec2::dot(Vec2& _vec2) const
{
	return _vec2.x*this->x + _vec2.y*this->y;
}

//�O�ς̒�`
double Vec2::cross(Vec2& _vec2) const
{
	return _vec2.x*this->y - _vec2.y*this->x;
}

//�����̒�`
double Vec2::length() const
{
	return Sqrt(Pow2(this->x) + Pow2(this->y));
}

//�p�x�̒�`
double Vec2::angle() const
{
	return atan2(this->y, this->x);
}

//Cos��Ԃ�
double Vec2::cos(Vec2& _vec2) const
{
	return dot(_vec2) / (this->length()*_vec2.length());
}
//Sin��Ԃ�
double Vec2::sin(Vec2& _vec2) const
{
	return cross(_vec2) / (this->length()*_vec2.length());
}

//�p�x����Ԃ�
double Vec2::angle(Vec2& _vec2) const
{
	if (cross(_vec2) < 0)
	{
		return -acos(cos(_vec2));
	}
	else
	{
		return acos(cos(_vec2));
	}
}

//�p�x��ύX
void Vec2::rotate(const double& _angle)
{
	Vec2 newVec2;
	newVec2.x = this->x*Cos(_angle) - this->y*Sin(_angle);
	newVec2.y = this->x*Sin(_angle) + this->y*Cos(_angle);
	*this = newVec2;
}
//�p�x��ύX�������̂�Ԃ�
Vec2 Vec2::rotated(const double& _angle) const
{
	Vec2 newVec2;
	newVec2.x = this->x*Cos(_angle) - this->y*Sin(_angle);
	newVec2.y = this->x*Sin(_angle) + this->y*Cos(_angle);
	return newVec2;
}

//���K������
void Vec2::normalize()
{
	*this /= length();
}
//���K���������̂�Ԃ�
Vec2 Vec2::normalized() const
{
	return *this / length();
}

//�p�x��ݒ�
void Vec2::setFromAngle(const double& _angle)
{
	x = Cos(_angle);
	y = Sin(_angle);
}

//�񍀉��Z�q
Vec2 operator+(const Vec2& u, const Vec2& v) {	//vector+vector
	Vec2 w;
	w.x = u.x + v.x;
	w.y = u.y + v.y;
	return w;
}

Vec2 operator-(const Vec2& u, const Vec2& v) {	//vector-vector
	Vec2 w;
	w.x = u.x - v.x;
	w.y = u.y - v.y;
	return w;
}


Vec2 operator*(const Vec2& v, double k) {	//vector*scalar
	Vec2 w;
	w.x = v.x * k;
	w.y = v.y * k;
	return w;
}
Vec2 operator*(double k, const Vec2& v) {	//scalar*vector
	Vec2 w;
	w.x = v.x * k;
	w.y = v.y * k;
	return w;
}
Vec2 operator/(const Vec2& v, double k) {	//vector/scalar
	Vec2 w;
	w.x = v.x / k;
	w.y = v.y / k;
	return w;
}


