#pragma once

#ifndef Color_H
#define Color_H


class Color
{
public:
	Color();
	Color(const int& _r, const int& _g, const int& _b);
	void setFromHSV(const double& H, const double& S = 1, const double& V = 1);
	unsigned int unsignedInt() const;

	int r;
	int g;
	int b;
	int a;	//アルファ色
};


#endif