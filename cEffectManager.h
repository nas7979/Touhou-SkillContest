#pragma once

#include "singleton.h"
#include "cEffect.h"
#include "cComponent.h"

class cEffectManager : public singleton <cEffectManager>
{
	friend class cComponent;
private:
	list<cEffect*> m_Effects_Back;
	list<cEffect*> m_Effects_Front;

public:
	cEffectManager();
	virtual ~cEffectManager();
	void Init();
	void Update();
	void RenderBack();
	void RenderFront();
	void Release();

	cEffect* Create(string Image, Vector2 Pos, Vector2 Size, int Depth);
	cEffect* Create(texture* Image, Vector2 Pos, Vector2 Size, int Depth);
	void MovementSetting(cEffect* Effect, int Speed, float Direction, float Friction, float Rotate);
	void AlphaSetting(cEffect* Effect, int Alpha, int AlphaPerFrame);
	void SizeSetting(cEffect* Effect, Vector2 SizePerFrame);
	void TextSetting(cEffect* Effect, wstring Text);
	void ColorSetting(cEffect* Effect, int R, int G, int B);
	void SetTimeSpeed();
	void ClearAll();
};

#define EFFECT cEffectManager::GetInstance()