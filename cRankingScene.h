#pragma once
#include "cScene.h"
#include "cResultScene.h"

class cRankingScene : public cScene
{
private:
	texture* m_Texture_Back;
	list<Rank> m_Ranking;

public:
	cRankingScene();
	virtual ~cRankingScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

