#pragma once
#include "cScene.h"

class cCreditScene : public cScene
{
private:
	texture* m_Texture_Back;
public:
	cCreditScene();
	virtual ~cCreditScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

