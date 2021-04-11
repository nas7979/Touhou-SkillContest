#pragma once
#include "cScene.h"

class cLoadingScene : public cScene
{
private:
	void LoadingImage(string Key, string Path, int Amount = 0);
	void LoadingSound(string Key, string Path, int Amount = 0, float Volume = 1);

public:
	cLoadingScene();
	virtual ~cLoadingScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

