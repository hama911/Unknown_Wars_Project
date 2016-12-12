#include"AdvancedMath.h"
#include<math.h>
#include"Color.h"
#include"Vec2.h"
#include"DxLib.h"

double Pow2(const double& _double)
{
	return _double*_double;
}

double Sqrt(const double& _double)
{
	return sqrt(_double);
}

double Cos(const double& _angle)
{
	return cos(_angle);
}

double Sin(const double& _angle)
{
	return sin(_angle);
}

Color RandomColor()
{
	return{ GetRand(255),GetRand(255),GetRand(255) };
}
Vec2 RandomVec2(const double& _minX, const double& _minY, const double& _maxX, const double& _maxY)
{
	return{ Random(_maxX - _minX) + _minX,Random(_maxY - _minY) + _minY };
}
Vec2 RandomVec2(const int& _minX, const int& _minY, const int& _maxX, const int& _maxY)
{
	return{ double(GetRand(_maxX - _minX) + _minX),double(GetRand(_maxY - _minY) + _minY )};
}
double Random(const double& _min, const double& _max)
{
	return Random(_max - _min) + _min;
}
double Random(const double& _max)
{
	return GetRand(int(_max * 65536)) / 65536.0;
}
int Random(const int& _min, const int& _max)
{
	return GetRand(_max - _min) + _min;
}
int Random(const int& _max)
{
	return GetRand(_max);
}