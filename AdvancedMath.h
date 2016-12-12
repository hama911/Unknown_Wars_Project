#pragma once

class Color;
class Vec2;

#define Pi 3.14159265359

double Pow2(const double& _double);
double Sqrt(const double& _double);
double Cos(const double& _angle);
double Sin(const double& _angle);

Color RandomColor();
Vec2 RandomVec2(const double& _minX, const double& _minY, const double& _maxX, const double& _maxY);
Vec2 RandomVec2(const int& _minX, const int& _minY, const int& _maxX, const int& _maxY);
double Random(const double& _min, const double& _max);
double Random(const double& _max);
int Random(const int& _min, const int& _max);
int Random(const int& _max);
