#include "DXUT.h"
#include "cEffectManager.h"


cEffectManager::cEffectManager()
{
	Init();
}


cEffectManager::~cEffectManager()
{
	Release();
}

void cEffectManager::Init()
{

}

void cEffectManager::Update()
{
	for (auto& iter = m_Effects_Back.begin(); iter != m_Effects_Back.end();)
	{
		(*iter)->Update();
		if ((*iter)->m_Alpha <= 0 || (*iter)->m_Size.x <= 0 || (*iter)->m_Size.y <= 0)
		{
			SAFE_DELETE((*iter));
			iter = m_Effects_Back.erase(iter);
		}
		else iter++;
	}
	for (auto& iter = m_Effects_Front.begin(); iter != m_Effects_Front.end();)
	{
		(*iter)->Update();
		if ((*iter)->m_Alpha <= 0 || (*iter)->m_Size.x <= 0 || (*iter)->m_Size.y <= 0)
		{
			SAFE_DELETE((*iter));
			iter = m_Effects_Front.erase(iter);
		}
		else iter++;
	}
}

void cEffectManager::RenderBack()
{
	list<cEffect*> RenderList = m_Effects_Back;
	RenderList.sort([&](cEffect *  pPrev, cEffect *  pNext)->bool { return pPrev->m_Depth > pNext->m_Depth; });
	for (auto& iter = RenderList.begin(); iter != RenderList.end();)
	{
		(*iter)->Render();
		iter++;
	}
	RenderList.clear();
}

void cEffectManager::RenderFront()
{
	list<cEffect*> RenderList = m_Effects_Front;
	RenderList.sort([&](cEffect *  pPrev, cEffect *  pNext)->bool { return pPrev->m_Depth > pNext->m_Depth; });
	for (auto& iter = RenderList.begin(); iter != RenderList.end();)
	{
		(*iter)->Render();
		iter++;
	}
	RenderList.clear();
}

void cEffectManager::Release()
{
	for (auto& iter = m_Effects_Back.begin(); iter != m_Effects_Back.end();)
	{
		SAFE_DELETE((*iter));
		iter++;
	}
	for (auto& iter = m_Effects_Front.begin(); iter != m_Effects_Front.end();)
	{
		SAFE_DELETE((*iter));
		iter++;
	}
	m_Effects_Back.clear();
	m_Effects_Front.clear();
}

cEffect* cEffectManager::Create(string Image, Vector2 Pos, Vector2 Size, int Depth)
{
	cEffect* a = new cEffect();
	a->m_texture = IMAGE->FindImage(Image);
	a->m_Pos = Pos;
	a->m_Size = Size;
	a->m_Depth = Depth;
	a->Init();
	if (Depth >= 0)
		m_Effects_Back.push_back(a);
	else
		m_Effects_Front.push_back(a);
	return a;
}

cEffect* cEffectManager::Create(texture* Image, Vector2 Pos, Vector2 Size, int Depth)
{
	cEffect* a = new cEffect();
	a->m_texture = Image;
	a->m_Pos = Pos;
	a->m_Size = Size;
	a->m_Depth = Depth;
	a->Init();
	if (Depth >= 0)
		m_Effects_Back.push_back(a);
	else
		m_Effects_Front.push_back(a);
	return a;
}

void cEffectManager::MovementSetting(cEffect* Effect, int Speed, float Direction, float Friction, float Rotate)
{
	Effect->m_Speed = Speed * SYSTEM->GetTimeSpeed();
	Effect->m_Direction = Direction;
	Effect->m_Friction = 1 - (1 - Friction) * SYSTEM->GetTimeSpeed();
	Effect->m_Rotate = Rotate;
}

void cEffectManager::AlphaSetting(cEffect* Effect, int Alpha, int AlphaPerFrame)
{
	Effect->m_Alpha = Alpha;
	Effect->m_AlphaPerFrame = AlphaPerFrame * SYSTEM->GetTimeSpeed();
}

void cEffectManager::SizeSetting(cEffect* Effect, Vector2 SizePerFrame)
{
	Effect->m_SizePerFrame = SizePerFrame * SYSTEM->GetTimeSpeed();
}

void cEffectManager::TextSetting(cEffect* Effect, wstring Text)
{
	Effect->m_Text = Text;
}

void cEffectManager::ColorSetting(cEffect* Effect, int R, int G, int B)
{
	Effect->m_Color[0] = R;
	Effect->m_Color[1] = G;
	Effect->m_Color[2] = B;
}

void cEffectManager::SetTimeSpeed()
{
	for (auto& iter = m_Effects_Back.begin(); iter != m_Effects_Back.end();)
	{
		(*iter)->m_Speed *= SYSTEM->GetTimeSpeed();
		(*iter)->m_AlphaPerFrame *= SYSTEM->GetTimeSpeed();
		(*iter)->m_SizePerFrame *= SYSTEM->GetTimeSpeed();
		(*iter)->m_Friction = 1 - (1 - (*iter)->m_Friction) * SYSTEM->GetTimeSpeed();
		iter++;
	}
	for (auto& iter = m_Effects_Front.begin(); iter != m_Effects_Front.end();)
	{
		(*iter)->m_Speed *= SYSTEM->GetTimeSpeed();
		(*iter)->m_AlphaPerFrame *= SYSTEM->GetTimeSpeed();
		(*iter)->m_SizePerFrame *= SYSTEM->GetTimeSpeed();
		(*iter)->m_Friction = 1 - (1 - (*iter)->m_Friction) * SYSTEM->GetTimeSpeed();
		iter++;
	}
}

void cEffectManager::ClearAll()
{
	Release();
}