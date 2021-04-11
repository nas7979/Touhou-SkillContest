#include "DXUT.h"
#include "cResultScene.h"
#include "cButton.h"
#include <fstream>
#include <conio.h>

cResultScene::cResultScene()
{
}


cResultScene::~cResultScene()
{
}

void cResultScene::Init()
{
	m_Texture_Back = IMAGE->FindImage("Back_Result");
	m_Page = 1;
	m_OnWriting = false;
	cin.clear();

	ifstream RankFile_R("Rank.txt");
	for (int i = 0; i < 10; i++)
	{
		m_Ranking.push_back(Rank{ "---------","" });
	}
	for(auto& iter = m_Ranking.begin(); iter != m_Ranking.end(); iter++)
	{
		RankFile_R.getline((*iter).Name, 11);
		RankFile_R.getline((*iter).Score, 14);
	}
	m_Ranking.sort([&](Rank PrevScore, Rank NextScore)->bool {return atol(PrevScore.Score) > atol(NextScore.Score); });
	RankFile_R.close();
}

void cResultScene::Release()
{
	ofstream RankFile_W("Rank.txt", ios::trunc);
	for (auto& iter = m_Ranking.begin(); iter != m_Ranking.end(); iter++)
	{
		RankFile_W << iter->Name << endl;
		RankFile_W << iter->Score << endl;
	}
	m_Ranking.clear();
	m_Name.clear();
	RankFile_W.close();
}

void cResultScene::Update()
{
	if (!m_OnWriting)
	{
		if (INPUT->KeyPress('Z'))
		{
			if (m_Page == 1)
			{
				m_Page++;
				m_OnWriting = true;
			}
			else SCENE->ChangeScene("Title");
			SOUND->Play("Ok");
		}
	}
	else
	{
		if (m_Name.size() > 0 && INPUT->KeyPress(VK_BACK))
		{
			m_Name.pop_back();
		}
		if (m_Name.size() > 0 && INPUT->KeyPress(VK_RETURN))
		{
			m_OnWriting = false;
			auto& iter = m_Ranking.begin();
			for (int i = 0; i < 9; i++)
			{
				iter++;
			}
			if (SYSTEM->GetScore() >= atol(iter->Score))
			{
				for (int i = 0; i < 10; i++)
				{
					iter->Name[i] = ' ';
					iter->Score[i] = ' ';
				}
				for (int i = 0; i < m_Name.size(); i++)
				{
					iter->Name[i] = m_Name[i];
				}
				itoa(SYSTEM->GetScore(), iter->Score, 10);
				m_Ranking.sort([&](Rank PrevScore, Rank NextScore)->bool {return atol(PrevScore.Score) > atol(NextScore.Score); });
			}
		}
		if (m_Name.size() < 10)
		{
			for (int i = 48; i < 91; i++)
			{
				if (m_Name.size() >= 10) break;
				if (INPUT->KeyPress(i))
				{
					m_Name.push_back(i);
					cin.clear();
				}
			}
		}
	}
}

void cResultScene::Render()
{
	IMAGE->Render(m_Texture_Back, Vector2(320, 240), Vector2(1, 1), 0);

	if (m_Page == 1)
	{
		wchar_t Score[50];
		wsprintf(Score, L"Á¡¼ö :                                %d", SYSTEM->GetScore());
		wchar_t Missed[50];
		wsprintf(Missed, L"ÇÇÅº È½¼ö :                         %d", SYSTEM->GetMissed());
		wchar_t Bonus[50];
		wsprintf(Bonus, L"½ºÆç Ä«µå º¸³Ê½º È¹µæ È½¼ö : %d", SYSTEM->GetBonusCount());
		wchar_t Boom[50];
		wsprintf(Boom, L"º½ »ç¿ë È½¼ö :                     %d", SYSTEM->GetBoomCount());
		wchar_t Graze[50];
		wsprintf(Graze, L"±×·¹ÀÌÁî È½¼ö :                   %d", SYSTEM->GetGraze());

		IMAGE->RenderText(Score, Vector2(170, 110), 30);
		IMAGE->RenderText(Missed, Vector2(170, 160), 30);
		IMAGE->RenderText(Bonus, Vector2(170, 210), 30);
		IMAGE->RenderText(Boom, Vector2(170, 260), 30);
		IMAGE->RenderText(Graze, Vector2(170, 310), 30);
	}
	else
	{
		wchar_t Name[50];
		IMAGE->RenderTextCenter(L"ÀÌ¸§À» ÀÔ·ÂÇÏ¼¼¿ä.", Vector2(295, 50), 30);
		IMAGE->RenderTextCenter(L"EnterÅ°¸¦ ´­·¯ ÀÔ·ÂÀ» ¸¶Ä¨´Ï´Ù.", Vector2(295, 85), 12);
		IMAGE->RenderText(m_Name, Vector2(250, 95), 30);

		wstring Ranking_Name[10];
		wstring Ranking_Score[10];
		int i = 0;
		for (auto& iter = m_Ranking.begin(); iter != m_Ranking.end(); iter++)
		{
			if (i != 9) Ranking_Name[i].push_back(i + 49);
			else
			{
				Ranking_Name[i].push_back('1');
				Ranking_Name[i].push_back('0');
			}
			Ranking_Name[i].push_back('.');
			Ranking_Name[i].push_back(' ');
			for (int j = 0; j < 10; j++)
			{
				Ranking_Name[i].push_back((*iter).Name[j]);
				Ranking_Score[i].push_back((*iter).Score[j]);
			}
			IMAGE->RenderText(Ranking_Name[i], Vector2(150, 150 + i * 30), 30);
			IMAGE->RenderText(Ranking_Score[i], Vector2(375, 150 + i * 30), 30);
			i++;
		}
	}
}