#include"Color.h"

Color::Color() : r(0), g(0), b(0)
{
}
Color::Color(const int& _r, const int& _g, const int& _b) : r(_r), g(_g), b(_b)
{
}

void Color::setFromHSV(const double& H, const double& S, const double& V)
{

		int hi;
		double f, p, q, t;
		double nr, ng, nb;
		int ir, ig, ib;

		hi = (int)(H / 60.0f);
		hi = hi == 6 ? 5 : hi %= 6;
		f = H / 60.0f - (double)hi;
		p = V * (1.0f - S);
		q = V * (1.0f - f * S);
		t = V * (1.0f - (1.0f - f) * S);
		switch (hi)
		{
		case 0: nr = V; ng = t; nb = p; break;
		case 1: nr = q; ng = V; nb = p; break;
		case 2: nr = p; ng = V; nb = t; break;
		case 3: nr = p; ng = q; nb = V; break;
		case 4: nr = t; ng = p; nb = V; break;
		case 5: nr = V; ng = p; nb = q; break;
		}

		ir = (int)(nr * 255.0f);
		if (ir > 255) ir = 255;
		else if (ir <   0) ir = 0;

		ig = (int)(ng * 255.0f);
		if (ig > 255) ig = 255;
		else if (ig <   0) ig = 0;

		ib = (int)(nb * 255.0f);
		if (ib > 255) ib = 255;
		else if (ib <   0) ib = 0;

		r = ir;
		g = ig;
		b = ib;
}
unsigned int Color::unsignedInt() const
{
	return (r << 16) + (g << 8) + b;
}