#include "DXUT.h"
#include "cOptionScene.h"
#include "cButton.h"

cOptionScene::cOptionScene()
{
}


cOptionScene::~cOptionScene()
{
}

void cOptionScene::Init()
{
	m_Texture_Back = IMAGE->FindImage("Back_Title");
	m_Selected = 0;
	m_LifeSelected = min(9, SYSTEM->GetStartLife() - 2);
}

void cOptionScene::Release()
{
	if (m_LifeSelected != 9) SYSTEM->SetStartLife(m_LifeSelected + 2);
	else SYSTEM->SetStartLife(100);
}

void cOptionScene::Update()
{
	//if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	//{
	//	if (m_Selected == 1)
	//	{
	//		m_Selected = 0;
	//	}
	//	else
	//	{
	//		m_Selected++;
	//	}
	//	SOUND->Play("Select");
	//}

	//if (GetAsyncKeyState(VK_UP) & 0x0001)
	//{
	//	if (m_Selected == 0)
	//	{
	//		m_Selected = 1;
	//	}
	//	else
	//	{
	//		m_Selected--;
	//	}
	//	SOUND->Play("Select");
	//}

	if (m_Selected == 0)
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x0001)
		{
			if (m_LifeSelected == 1) m_LifeSelected = 9;
			else m_LifeSelected--;
			SOUND->Play("Select");
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
		{
			if (m_LifeSelected == 9) m_LifeSelected = 1;
			else m_LifeSelected++;
			SOUND->Play("Select");
		}
	}

	if (GetAsyncKeyState('X') & 0x0001)
	{
		SCENE->ChangeScene("Title");
		SOUND->Play("Cancel");
	}
}

void cOptionScene::Render()
{
	IMAGE->Render(m_Texture_Back, Vector2(320, 240), Vector2(1.3, 1.3), 0);

	if (m_Selected == 0)
	{
		IMAGE->RenderText(L"시작 잔기", Vector2(100, 150), 30, D3DCOLOR_ARGB(255, 255, 255, 255));
		IMAGE->RenderText(L"3", Vector2(230, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 1 ? 255 : 150, 255, 255, 255));
		IMAGE->RenderText(L"4", Vector2(260, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 2 ? 255 : 150, 255, 255, 255));
		IMAGE->RenderText(L"5", Vector2(290, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 3 ? 255 : 150, 255, 255, 255));
		IMAGE->RenderText(L"6", Vector2(320, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 4 ? 255 : 150, 255, 255, 255));
		IMAGE->RenderText(L"7", Vector2(350, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 5 ? 255 : 150, 255, 255, 255));
		IMAGE->RenderText(L"8", Vector2(380, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 6 ? 255 : 150, 255, 255, 255));
		IMAGE->RenderText(L"9", Vector2(410, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 7 ? 255 : 150, 255, 255, 255));
		IMAGE->RenderText(L"10", Vector2(440, 150), 30, D3DCOLOR_ARGB(m_LifeSelected ==8 ? 255 : 150, 255, 255, 255));
		IMAGE->RenderText(L"Inf", Vector2(480, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 9 ? 255 : 150, 255, 255, 255));
	}
	else
	{
		IMAGE->RenderText(L"시작 잔기", Vector2(100, 150), 30, D3DCOLOR_ARGB(150, 255, 255, 255));
		IMAGE->RenderText(L"3", Vector2(230, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 1 ? 150 : 75, 255, 255, 255));
		IMAGE->RenderText(L"4", Vector2(260, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 2 ? 150 : 75, 255, 255, 255));
		IMAGE->RenderText(L"5", Vector2(290, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 3 ? 150 : 75, 255, 255, 255));
		IMAGE->RenderText(L"6", Vector2(320, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 4 ? 150 : 75, 255, 255, 255));
		IMAGE->RenderText(L"7", Vector2(350, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 5 ? 150 : 75, 255, 255, 255));
		IMAGE->RenderText(L"8", Vector2(380, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 6 ? 150 : 75, 255, 255, 255));
		IMAGE->RenderText(L"9", Vector2(410, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 7 ? 150 : 75, 255, 255, 255));
		IMAGE->RenderText(L"10", Vector2(440, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 8 ? 150 : 75, 255, 255, 255));
		IMAGE->RenderText(L"Inf", Vector2(480, 150), 30, D3DCOLOR_ARGB(m_LifeSelected == 9 ? 150 : 75, 255, 255, 255));
	}

	IMAGE->RenderText(L"시작 잔기 수 설정에 따라 최종 점수에 0~2 가 곱해집니다.", Vector2(100, 180), 20);
}
