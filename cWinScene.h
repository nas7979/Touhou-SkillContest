#pragma once
#include "cScene.h"

class cWinScene : public cScene
{
private:
	int m_Page;
public:
	cWinScene();
	virtual ~cWinScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

