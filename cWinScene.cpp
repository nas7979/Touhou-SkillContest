#include "DXUT.h"
#include "cWinScene.h"

cWinScene::cWinScene()
{
}


cWinScene::~cWinScene()
{
}

void cWinScene::Init()
{
	m_Page = 1;
}

void cWinScene::Release()
{
}

void cWinScene::Update()
{
	if (INPUT->KeyPress('Z'))
	{
		if(m_Page != 10) m_Page++;
		else SCENE->ChangeScene("Result");
		SOUND->Play("Ok");
	}
}

void cWinScene::Render()
{
	switch (m_Page)
	{
	case 1: IMAGE->Render(IMAGE->FindImage("Clear1"), Vector2(320, 240), Vector2(1, 1), 0);
		IMAGE->RenderText(L"Z를 눌러 진행", Vector2(500, 30), 20, D3DCOLOR_ARGB(255, 0, 0, 0)); break;
	case 2: IMAGE->Render(IMAGE->FindImage("Clear2"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 3: IMAGE->Render(IMAGE->FindImage("Clear3"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 4: IMAGE->Render(IMAGE->FindImage("Clear4"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 5: IMAGE->Render(IMAGE->FindImage("Clear5"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 6: IMAGE->Render(IMAGE->FindImage("Clear6"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 7: IMAGE->Render(IMAGE->FindImage("Clear7"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 8: IMAGE->Render(IMAGE->FindImage("Clear8"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 9: IMAGE->Render(IMAGE->FindImage("Clear9"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 10: IMAGE->Render(IMAGE->FindImage("Clear10"), Vector2(320, 240), Vector2(1, 1), 0); break;
	}
}
