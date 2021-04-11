#include "DXUT.h"
#include "cCreditScene.h"

cCreditScene::cCreditScene()
{
}


cCreditScene::~cCreditScene()
{
}

void cCreditScene::Init()
{
	m_Texture_Back = IMAGE->FindImage("Back_Title");
}

void cCreditScene::Release()
{
}

void cCreditScene::Update()
{
	if (INPUT->KeyPress('X'))
	{
		SCENE->ChangeScene("Title");
		SOUND->Play("Cancel");
	}
}

void cCreditScene::Render()
{
	IMAGE->Render(m_Texture_Back, Vector2(320, 240), Vector2(1.3, 1.3), 0);
	IMAGE->RenderText(L"����, �׷���, ���� - ZUN\n\n ���α׷���, �׷��� - Ȳ����", Vector2(70, 100), 50);
}
