#pragma once

#include "singleton.h"

using Vector2 = D3DXVECTOR2;
//C++������ ����ü�� Ŭ������ ���̰� ���� ����
//struct�� �⺻�� public
//class�� �⺻�� private�� �Ǿ�������
//���� ������ ���� ���� �ȿ� �Լ��� ������ �ִ�.
struct texture
{
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;

	texture(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info)
		:texturePtr(texturePtr), info(info)
	{
	}

	void Render(Vector2 pos, Vector2 size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Render(float x, float y, float rot = 0);

	void CenterRender(Vector2 pos, Vector2 size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(float x, float y, float rot = 0);
};

//singleton�� ��ӹ޾Ҵ�. ��𼭵� ������ ��������
class cImageManager : public singleton <cImageManager>
{
private:
	LPD3DXSPRITE m_sprite;
	map<string, texture*> m_images;
	D3DXMATRIX Worldmat;
	LPD3DXFONT m_Font[31];

	//stl���� map�̶�� �ڷ����� �ִµ�
	//�̸����� ���� ã����, ���� ���� ȿ���� �����ش�
private:
	void Init();
	void Release();
public:
	cImageManager();
	virtual ~cImageManager();

	texture* AddImage(const string& key, const string& path);
	texture* FindImage(const string& key);

	void Begin();
	void End();

	void Render(texture* texturePtr, Vector2 pos, Vector2 size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Render(texture* texturePtr, float x, float y, float rot = 0);
	//�»���� �������� �̹��� ������

	void CenterRender(texture* texturePtr, Vector2 pos, Vector2 size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(texture* texturePtr, float x, float y, float rot = 0);
	//����� �������� �̹��� ������

	void RenderText(wstring Text, Vector2 Pos, int Size, D3DCOLOR Color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void RenderTextCenter(wstring Text, Vector2 Pos, int Size, D3DCOLOR Color = D3DCOLOR_ARGB(255, 255, 255, 255));

	void LostDevice();
	void ResetDevice();

	vector<texture*> MakeVector(const string& Key);
	//�Լ��� ���ڴ� �⺻������ 4������ ����ϴ°��� ����.(4���� �Ѿ�� �ް��� ��������)
	//�ڼ��� ������ ���߿� �������Ϳ� �ý��� ĳ�ø� �����Ҷ� �˾ƺ��� ����
};

#define IMAGE cImageManager::GetInstance()
//�Ź� �Լ����� �������� cImageManager::GetInstance()->AddImage();���ִ°��� ����� ���ŷο���
//���� ���� �ٿ��� ����Ѵ�