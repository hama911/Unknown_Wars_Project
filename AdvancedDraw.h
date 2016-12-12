#pragma once
#include"DxLib.h"

class Color;
class Vec2;

void DrawLineAA(const Vec2& pos1, const Vec2& pos2, const Color& color, const double& thickness = 1.0);
void DrawBoxAA(const Vec2& pos1, const Vec2& pos2, const Color& color, const bool& FillFlag = false, const double& thickness = 1.0);
void DrawCircleAA(const Vec2& pos, const float& r, const Color& color, const bool& fillflag = true);

void DrawFormatString(const Vec2& pos, const Color& color, const TCHAR *FormatString, ...);

VECTOR VGet(const Vec2& vec2);