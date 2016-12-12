#include"AdvancedSystem.h"
#include"DxLib.h"
#include"Vec2.h"

Vec2 MousePos()
{
	int x;
	int y;
	GetMousePoint(&x, &y);
	return{ double(x),double(y) };
}