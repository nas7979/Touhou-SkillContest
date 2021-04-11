#include "DXUT.h"
#include "cLoseScene.h"

cLoseScene::cLoseScene()
{
}


cLoseScene::~cLoseScene()
{
}

void cLoseScene::Init()
{
	m_Page = 1;
}

void cLoseScene::Release()
{
}

void cLoseScene::Update()
{
	if (INPUT->KeyPress('Z'))
	{
		if (m_Page != 3) m_Page++;
		else SCENE->ChangeScene("Result");
		SOUND->Play("Ok");
	}
}

void cLoseScene::Render()
{
	switch (m_Page)
	{
	case 1: IMAGE->Render(IMAGE->FindImage("Over1"), Vector2(320, 240), Vector2(1, 1), 0);
		IMAGE->RenderText(L"Z를 눌러 진행", Vector2(500, 30), 20, D3DCOLOR_ARGB(255, 0, 0, 0)); break;
	case 2: IMAGE->Render(IMAGE->FindImage("Over2"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 3: IMAGE->Render(IMAGE->FindImage("Over3"), Vector2(320, 240), Vector2(1, 1), 0); break;
	}
}
