#include "DXUT.h"
#include "cButton.h"

cButton::cButton(cObject* Object)
	:cComponent(Object)
{
}


cButton::~cButton()
{
}

void cButton::Init()
{
	m_Selected = false;
	m_Color = D3DCOLOR_ARGB(150, 255, 255, 255);
	m_Size = 50;
}

void cButton::Update()
{
	if (m_Selected && m_Size == 50)
	{
		m_Color = D3DCOLOR_ARGB(255, 255, 255, 255);
		m_Size = 65;
		m_pObject->Translate(Vector2(-50, 0));
	}
	if (!m_Selected && m_Size == 65)
	{
		m_Color = D3DCOLOR_ARGB(150, 255, 255, 255);
		m_Size = 50;
		m_pObject->Translate(Vector2(50, 0));
	}
}

void cButton::Render()
{
	IMAGE->RenderText(m_Text, m_pObject->GetPosition(), m_Size, m_Color);
}

void cButton::Release()
{
	m_Text.clear();
}