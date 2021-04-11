#pragma once
#include "cScene.h"

class cIngameScene : public cScene
{
private:
	texture* m_Texture_Background;
	texture* m_Texture_Slow;
	texture* m_Texture_Remi;
	texture* m_Texture_Flan;
	texture* m_Texture_Enemy;
	float m_Background_y;
	float m_Background_Speed;
	float m_Slow_Alpha;
	float m_Time;
	int m_Last;
	Vector2 m_CreatePos;
public:
	cIngameScene();
	virtual ~cIngameScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

