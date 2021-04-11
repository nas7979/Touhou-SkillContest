#pragma once
#include "cScene.h"

struct Rank
{
	char Name[11];
	char Score[15];
};
class cResultScene : public cScene
{
private:
	texture* m_Texture_Back;
	int m_Page;
	bool m_OnWriting;
	wstring m_Name;
	list<Rank> m_Ranking;

public:
	cResultScene();
	virtual ~cResultScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

