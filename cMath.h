#pragma once
#include "stdafx.h"
using Vector2 = D3DXVECTOR2;

class cObject;

namespace Math
{
	int sign(float Value);

	bool CheckCollBoxBox(Vector2 ThisPos, RECT ThisRect, Vector2 OtherPos, RECT OtherRect);
	bool CheckCollCirCir(Vector2 ThisPos, float ThisRad, Vector2 OtherPos, float OtherRad);
	bool CheckCollBoxCir(Vector2 ThisPos, RECT ThisRect, Vector2 OtherPos, float OtherRad);

	float PointDistance(Vector2 Pos1, Vector2 Pos2);

	cObject* Nearest(Vector2 Pos, char Name);
	cObject* Nearest(Vector2 Pos, int ObjectTag);
}