#include "DXUT.h"
#include "cMath.h"

using namespace Math;

int Math::sign(float Value)
{
	if (Value > 0) return 1;
	if (Value < 0) return -1;
	return 0;
}

bool Math::CheckCollBoxBox(Vector2 ThisPos, RECT ThisRect, Vector2 OtherPos, RECT OtherRect)
{
	if (((ThisPos.x + ThisRect.left - OtherPos.x + OtherRect.right <= 0 && ThisPos.x + ThisRect.right - OtherPos.x + OtherRect.right >= 0) ||
		(ThisPos.x + ThisRect.right - OtherPos.x + OtherRect.left >= 0 && ThisPos.x + ThisRect.left - OtherPos.x + OtherRect.left <= 0)) &&
		((ThisPos.y + ThisRect.top - OtherPos.y + OtherRect.bottom <= 0 && ThisPos.y + ThisRect.bottom - OtherPos.y + OtherRect.bottom >= 0) ||
		(ThisPos.y + ThisRect.bottom - OtherPos.y + OtherRect.top >= 0 && ThisPos.y + ThisRect.top - OtherPos.y + OtherRect.top <= 0)))
	{
		return true;
	}
	return false;
}

bool Math::CheckCollCirCir(Vector2 ThisPos, float ThisRad, Vector2 OtherPos, float OtherRad)
{
	if (Math::PointDistance(ThisPos, OtherPos) <= ThisRad + OtherRad)
	{
		return true;
	}
	return false;
}

bool Math::CheckCollBoxCir(Vector2 ThisPos, RECT ThisRect, Vector2 OtherPos, float OtherRad)
{
	Vector2 Closest;
	if (OtherPos.x <= ThisPos.x + ThisRect.left) Closest.x = ThisPos.x + ThisRect.left;

	else if (OtherPos.x >= ThisPos.x + ThisRect.right) Closest.x = ThisPos.x + ThisRect.right;

	else Closest.x = OtherPos.x;

	if (OtherPos.y <= ThisPos.y + ThisRect.top) Closest.y = ThisPos.y + ThisRect.top;

	else if (OtherPos.y >= ThisPos.y + ThisRect.bottom) Closest.y = ThisPos.y + ThisRect.bottom;

	else Closest.y = OtherPos.y;

	if (Math::PointDistance(Closest, OtherPos) <= OtherRad)
	{
		return true;
	}
	return false;
}

float Math::PointDistance(Vector2 Pos1, Vector2 Pos2)
{
	float x = Pos2.x - Pos1.x;
	float y = Pos2.y - Pos1.y;
	float Dir = atan(y / x);

	return abs(x * cos(Dir)) + abs(y * sin(Dir));
}

cObject* Math::Nearest(Vector2 Pos, char Name)
{
	list<cObject*> Objects = OBJECT->Find(string(&Name));
	if (Objects.size() == 0) return nullptr;
	Objects.sort([&](cObject *  pPrev, cObject *  pNext)->bool { return Math::PointDistance(Pos,pPrev->GetPosition()) > Math::PointDistance(Pos, pNext->GetPosition()); });

	return Objects.front();
}

cObject* Math::Nearest(Vector2 Pos, int ObjectTag)
{
	list<cObject*> Objects = OBJECT->Find((Tag)ObjectTag);
	if (Objects.size() == 0) return nullptr;
	Objects.sort([&](cObject *  pPrev, cObject *  pNext)->bool { return Math::PointDistance(Pos, pPrev->GetPosition()) < Math::PointDistance(Pos, pNext->GetPosition()); });

	return Objects.front();
}