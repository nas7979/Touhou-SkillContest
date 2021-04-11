#include "DXUT.h"
#include "cHowScene.h"

cHowScene::cHowScene()
{
}


cHowScene::~cHowScene()
{
}

void cHowScene::Init()
{
	m_Texture_Back = IMAGE->FindImage("Back_Title");
	m_Page = 1;
}

void cHowScene::Release()
{
}

void cHowScene::Update()
{
	if (INPUT->KeyPress(VK_LEFT))
	{
		if (m_Page != 1)
		{
			m_Page--;
			SOUND->Play("Select");
		}
	}

	if (INPUT->KeyPress(VK_RIGHT))
	{
		if (m_Page != 3)
		{
			m_Page++;
			SOUND->Play("Select");
		}
	}

	if (INPUT->KeyPress('X'))
	{
		SCENE->ChangeScene("Title");
		SOUND->Play("Cancel");
	}
}

void cHowScene::Render()
{
	IMAGE->Render(m_Texture_Back, Vector2(320, 240), Vector2(1.3, 1.3), 0);

	switch (m_Page)
	{
	case 1: IMAGE->Render(IMAGE->FindImage("How1"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 2: IMAGE->Render(IMAGE->FindImage("How2"), Vector2(320, 240), Vector2(1, 1), 0); break;
	case 3: IMAGE->Render(IMAGE->FindImage("How3"), Vector2(320, 240), Vector2(1, 1), 0); break;
	}
}
