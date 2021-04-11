#include "DXUT.h"
#include "cTitleScene.h"
#include "cButton.h"

cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	SYSTEM->Initialize();
	m_Texture_Back = IMAGE->FindImage("Back_Title");
	m_Buttons[0] = OBJECT->Create("Start", Vector2(400, 100), -10, Tag::None);
	m_Buttons[0]->AddComponent<cButton>()->SetString(L"Start");
	m_Buttons[1] = OBJECT->Create("How", Vector2(390, 150), -10, Tag::None);
	m_Buttons[1]->AddComponent<cButton>()->SetString(L"How To Play");
	m_Buttons[2] = OBJECT->Create("Replay", Vector2(390, 200), -10, Tag::None);
	m_Buttons[2]->AddComponent<cButton>()->SetString(L"Replay");
	m_Buttons[3] = OBJECT->Create("Ranking", Vector2(380, 250), -10, Tag::None);
	m_Buttons[3]->AddComponent<cButton>()->SetString(L"Ranking");
	m_Buttons[4] = OBJECT->Create("Option", Vector2(370, 300), -10, Tag::None);
	m_Buttons[4]->AddComponent<cButton>()->SetString(L"Option");
	m_Buttons[5] = OBJECT->Create("Credit", Vector2(370, 350), -10, Tag::None);
	m_Buttons[5]->AddComponent<cButton>()->SetString(L"Credit");
	m_Buttons[6] = OBJECT->Create("Quit", Vector2(360, 400), -10, Tag::None);
	m_Buttons[6]->AddComponent<cButton>()->SetString(L"Quit");

	m_Selected = 0;
}

void cTitleScene::Release()
{
}

void cTitleScene::Update()
{
	if (INPUT->KeyPress(VK_DOWN))
	{
		if (m_Selected == 6)
		{
			m_Selected = 0;
			m_Buttons[4]->GetComponent<cButton>()->SetSelected(false);
		}
		else
		{
			m_Buttons[m_Selected]->GetComponent<cButton>()->SetSelected(false);
			m_Selected++;
		}
		SOUND->Play("Select");
	}

	if (INPUT->KeyPress(VK_UP))
	{
		if (m_Selected == 0)
		{
			m_Selected = 6;
			m_Buttons[0]->GetComponent<cButton>()->SetSelected(false);
		}
		else
		{
			m_Buttons[m_Selected]->GetComponent<cButton>()->SetSelected(false);
			m_Selected--;
		}
		SOUND->Play("Select");
	}

	m_Buttons[m_Selected]->GetComponent<cButton>()->SetSelected(true);

	if (INPUT->KeyPress('Z') || INPUT->KeyPress(VK_RETURN))
	{
		switch (m_Selected)
		{
		case 0:
			SCENE->ChangeScene("Ingame");
			SYSTEM->SetIsReplay(false);
			break;
		case 1:
			SCENE->ChangeScene("How");
			break;
		case 2:
			SCENE->ChangeScene("Replay");
			SYSTEM->SetIsReplay(true);
			break;
		case 3:
			SCENE->ChangeScene("Ranking");
			break;
		case 4:
			SCENE->ChangeScene("Option");
			break;
		case 5:
			SCENE->ChangeScene("Credit");
			break;
		case 6:
			exit(0);
			break;
		}
		SOUND->Play("Ok");
	}
}

void cTitleScene::Render()
{
	IMAGE->Render(m_Texture_Back, Vector2(320, 240), Vector2(1.3, 1.3), 0);
	IMAGE->Render(IMAGE->FindImage("Logo"), 10, 0);
}
