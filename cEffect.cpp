#include "DXUT.h"
#include "cEffect.h"


cEffect::cEffect()
{
}


cEffect::~cEffect()
{
}

void cEffect::Init()
{
	m_Alpha = 255;
	m_AlphaPerFrame = 0;
	m_SizePerFrame = Vector2(0, 0);
	m_Friction = 1;
	m_Speed = 0;
	m_Rotate = 0;
	m_Direction = 0;
	m_Text = L"";
	m_Color[0] = 255;
	m_Color[1] = 255;
	m_Color[2] = 255;
}

void cEffect::Update()
{
	m_Pos += Vector2(m_Speed * cos(D3DXToRadian(m_Direction)) * DeltaTime, m_Speed * sin(D3DXToRadian(m_Direction)) * DeltaTime);
	m_Size += m_SizePerFrame;
	m_Speed *= m_Friction;
	m_Alpha += m_AlphaPerFrame;
}

void cEffect::Render()
{
	if(m_texture != nullptr)
	IMAGE->Render(m_texture, m_Pos, m_Size, m_Rotate, D3DCOLOR_ARGB(min(m_Alpha, 255), m_Color[0], m_Color[1], m_Color[2]));
	else
	IMAGE->RenderTextCenter(m_Text, m_Pos, m_Size.x, D3DCOLOR_ARGB(min(m_Alpha, 255), m_Color[0], m_Color[1], m_Color[2]));
}

void cEffect::Release()
{
	m_Text.clear();
}