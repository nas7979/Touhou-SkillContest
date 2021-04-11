#pragma once
#include "cScene.h"

class cTitleScene : public cScene
{
private:
	texture* m_Texture_Back;
	cObject* m_Buttons[7];
	int m_Selected;
	
public:
	cTitleScene();
	virtual ~cTitleScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};