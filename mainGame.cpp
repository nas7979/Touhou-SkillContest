#include "DXUT.h"
#include "mainGame.h"

#include "cIngameScene.h"
#include "cLoadingScene.h"
#include "cTitleScene.h"
#include "cHowScene.h"
#include "cResultScene.h"
#include "cRankingScene.h"
#include "cOptionScene.h"
#include "cWinScene.h"
#include "cLoseScene.h"
#include "cCreditScene.h"


mainGame::mainGame()
{

}

mainGame::~mainGame()
{
	Release();	
}

void mainGame::Init()
{
	SCENE->AddScene("Title", new cTitleScene);
	SCENE->AddScene("How", new cHowScene);
	SCENE->AddScene("Ingame", new cIngameScene);
	SCENE->AddScene("Loading", new cLoadingScene);
	SCENE->AddScene("Result", new cResultScene);
	SCENE->AddScene("Ranking", new cRankingScene);
	SCENE->AddScene("Option", new cOptionScene);
	SCENE->AddScene("Win", new cWinScene);
	SCENE->AddScene("Lose", new cLoseScene);
	SCENE->AddScene("Credit", new cCreditScene);

	SCENE->ChangeScene("Loading");
}

void mainGame::Release()
{
	cSoundManager::ReleaseInstance();
	DEBUG_LOG("Sound");
	cImageManager::ReleaseInstance();
	DEBUG_LOG("Image");
	cSceneManager::ReleaseInstance();
	DEBUG_LOG("Scene");
	cEffectManager::ReleaseInstance();
	DEBUG_LOG("Effect");
	cSystemManager::ReleaseInstance();
	DEBUG_LOG("System");
	cObjectManager::ReleaseInstance();
	DEBUG_LOG("Object");
	cInputManager::ReleaseInstance();
	DEBUG_LOG("Input");
}

void mainGame::Update()
{
	SCENE->Update();

	SYSTEM->Update();

	OBJECT->Update();

	EFFECT->Update();

	SOUND->Update();

	INPUT->Update();
}

void mainGame::Render()
{
	IMAGE->Begin();

	SCENE->Render();

	EFFECT->RenderBack();

	OBJECT->Render();

	EFFECT->RenderFront();

	SYSTEM->Render();

	TCHAR _Fps[10];
	swprintf(_Fps, L"%.f",DXUTGetFPS());
	IMAGE->RenderText(_Fps, Vector2(10, 460), 15);

	IMAGE->End();
}

void mainGame::LostDevice()
{
}

void mainGame::ResetDevice()
{
}