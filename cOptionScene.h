#pragma once
#include "cScene.h"

class cOptionScene : public cScene
{
private:
	texture* m_Texture_Back;
	int m_Selected;
	int m_LifeSelected;

public:
	cOptionScene();
	virtual ~cOptionScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

