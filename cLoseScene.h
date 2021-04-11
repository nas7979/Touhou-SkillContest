#pragma once
#include "cScene.h"

class cLoseScene : public cScene
{
private:
	int m_Page;
public:
	cLoseScene();
	virtual ~cLoseScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

