#pragma once
#include "singleton.h"

class cScene;//Ŭ������ ���漱���� �����ϴ�
//��������� ���� �߰��ϰ� �ɰ��, ����� ó���������� ������ ����ų�
//���� ����� ������ �߰��ϰ� �Ǿ� ������ �߻��Ҽ� �ִ�.
//�׷��� ������� Ŭ���� �̸��� �߰��ϰ�, cpp���Ͽ� ��������� �߰��ϴ°��� 'Ŭ���� ����' ��� �Ѵ�
class cSceneManager : public singleton<cSceneManager>
{
private:
	//cScene temp; //Ŭ���� ���漱��ÿ��� Ŭ������ �����͸� ����Ҽ� �ִ�
	cScene* m_nowScene;
	cScene* m_nextScene;
	map<string, cScene*> m_scenes;

	void Release();
public:
	cSceneManager();
	virtual ~cSceneManager();

	cScene* AddScene(const string& key, cScene* scenePtr);
	cScene* ChangeScene(const string& key);
	bool GetCurrentSceneKey(string Key)
	{
		return (m_scenes.find(Key)->second == m_nowScene);
	}

	void Update();
	void Render();
};

#define SCENE cSceneManager::GetInstance()

