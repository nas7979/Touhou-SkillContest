#include "DXUT.h"
#include "cRankingScene.h"
#include <fstream>

cRankingScene::cRankingScene()
{
}


cRankingScene::~cRankingScene()
{
}

void cRankingScene::Init()
{
	m_Texture_Back = IMAGE->FindImage("Back_Title");

	ifstream RankFile_R("Rank.txt");
	for (int i = 0; i < 10; i++)
	{
		m_Ranking.push_back(Rank{ "---------","" });
	}
	for (auto& iter = m_Ranking.begin(); iter != m_Ranking.end(); iter++)
	{
		RankFile_R.getline((*iter).Name, 11);
		RankFile_R.getline((*iter).Score, 14);
	}
	RankFile_R.close();
}

void cRankingScene::Release()
{
	m_Ranking.clear();
}

void cRankingScene::Update()
{
	if (GetAsyncKeyState('X') & 0x0001)
	{
		SCENE->ChangeScene("Title");
		SOUND->Play("Cancel");
	}
}

void cRankingScene::Render()
{
	IMAGE->Render(m_Texture_Back, Vector2(320, 240), Vector2(1.3, 1.3), 0);

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
		IMAGE->RenderText(Ranking_Name[i], Vector2(150, 100 + i * 30), 30);
		IMAGE->RenderText(Ranking_Score[i], Vector2(375, 100 + i * 30), 30);
		i++;
	}
}