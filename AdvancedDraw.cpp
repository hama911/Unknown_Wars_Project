#include "AdvancedDraw.h"
#include "Color.h"
#include "Vec2.h"
#include "Dxlib.h"


void DrawLineAA(const Vec2& pos1, const Vec2& pos2, const Color& color, const double& thickness)
{
	DrawLineAA(float(pos1.x), float(pos1.y), float(pos2.x), float(pos2.y), color.unsignedInt(), float(thickness));
}
void DrawBoxAA(const Vec2& pos1, const Vec2& pos2, const Color& color, const bool& fillFlag, const double& thickness)
{
	DrawBoxAA(float(pos1.x), float(pos1.y), float(pos2.x), float(pos2.y), color.unsignedInt(), fillFlag, float(thickness));
}
void DrawCircleAA(const Vec2& pos, const float& r, const Color& color, const bool& fillflag)
{
	DrawCircleAA(float(pos.x), float(pos.y), float(r), 32, color.unsignedInt(), fillflag);
}

void DrawFormatString(const Vec2& pos, const Color& color, const TCHAR *FormatString, ...)
{
	DrawFormatString(int(pos.x), int(pos.y), color.unsignedInt(), FormatString);
}

VECTOR VGet(const Vec2& vec2)
{
	return VGet(float(vec2.x), 0, float(-vec2.y));
}