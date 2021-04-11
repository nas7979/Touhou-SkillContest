#pragma once
#include "cScene.h"

class cHowScene : public cScene
{
private:
	texture* m_Texture_Back;
	int m_Page;
public:
	cHowScene();
	virtual ~cHowScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

