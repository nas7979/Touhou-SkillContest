#include "DXUT.h"
#include "cFace.h"
#include "cPlayer.h"

cFace::cFace(cObject* Object)
	:cComponent(Object)
{
}


cFace::~cFace()
{
}

void cFace::Init()
{
	m_Speed = 1050;
	m_TextSpeed = 1100;
	m_TextY = 0;
	m_TextX = 0;
	m_IsEnemy = true;
	m_Texture_SpellName[0] = IMAGE->FindImage("SpellName1");
	m_Texture_SpellName[1] = IMAGE->FindImage("SpellName2");
}

void cFace::Update()
{
	if (m_Speed > 0.3)
	{
		if (m_IsEnemy)
		{
			m_pObject->Translate(Vector2(-m_Speed, 0) * DeltaTime);
		}
		else
		{
			m_pObject->Translate(Vector2(m_Speed, 0) * DeltaTime);
			m_TextSpeed = 500;
		}
		m_Speed *= 0.92;
	}
	else
	{
		m_pObject->Scale(Vector2(0.05,0.05));
		m_pObject->GetComponent<cRenderer>()->SetAlpha(m_pObject->GetComponent<cRenderer>()->GetAlpha() - 8);
		if (m_pObject->GetComponent<cRenderer>()->GetAlpha() <= 0)
		{
			m_pObject->GetComponent<cRenderer>()->SetEnable(false);
		}
		if (m_IsEnemy)
		{
			if (m_TextSpeed > 5)
			{
				m_TextY += m_TextSpeed * DeltaTime;
				m_TextSpeed *= 0.936;
			}
		}
		else
		{
			if (m_TextSpeed > 5)
			{
				m_TextY += m_TextSpeed * DeltaTime;
			}
			else if(m_TextSpeed < 1)
			{
				m_TextX += 500 * DeltaTime;
				if(m_TextX < -100) m_pObject->Destroy();
			}
			m_TextSpeed *= 0.935;
		}
	}
}

void cFace::Render()
{
	if (m_IsEnemy)
	{
		IMAGE->Render(m_Texture_SpellName[0], 128, 300 - m_TextY);
		IMAGE->RenderTextCenter(m_Text, Vector2(280, 306 - m_TextY), 20, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	else
	{
		IMAGE->Render(m_Texture_SpellName[1], Vector2(0 - m_TextX, 300 + m_TextY), m_pObject->GetScale(), 0, 0x90ffffff);
		IMAGE->RenderTextCenter(m_Text, Vector2(128 - m_TextX, 306 + m_TextY), 20, D3DCOLOR_ARGB(0x90, 75, 30, 220));
	}

}

void cFace::Release()
{

}