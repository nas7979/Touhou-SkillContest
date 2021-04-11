#include "DXUT.h"
#include "cImageManager.h"

void texture::Render(Vector2 pos, Vector2 size, float rot, D3DCOLOR color)
{
	IMAGE->Render(this, pos, size, rot, color);
}

void texture::Render(float x, float y, float rot)
{
	IMAGE->Render(this, x, y, rot);
}

void texture::CenterRender(Vector2 pos, Vector2 size, float rot, D3DCOLOR color)
{
	IMAGE->CenterRender(this, pos, size, rot, color);
}

void texture::CenterRender(float x, float y, float rot)
{
	IMAGE->CenterRender(this, x, y, rot);
}

cImageManager::cImageManager()
	:m_sprite(nullptr)
{
	Init();
}


cImageManager::~cImageManager()
{
	Release();
}

//�ҷ��� �̹����� �θ� �̸��� ���
texture* cImageManager::AddImage(const string& key, const string& path)
{
	auto find = m_images.find(key);//�̹� �ִ� �̸��� �ٽ� ������ �ϴ°� �ƴ��� Ȯ���غ���
	if (find == m_images.end())
	{
		LPDIRECT3DTEXTURE9 texturePtr;
		D3DXIMAGE_INFO info;

		if (D3DXCreateTextureFromFileExA(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK)
		{
			texture* text = new texture(texturePtr, info);
			m_images.insert(make_pair(key, text));
			return text;
		}
#pragma region �ε�����
		DEBUG_LOG("ERROR! �̹��� �ε��� �����߽��ϴ�. ���ϰ�θ� �ٽ� Ȯ�����ּ���");
		DEBUG_LOG("\tkey :" << key.c_str() << "\t path : " << path.c_str());
#pragma endregion
		//�̹��� �ε��� �����������(���� ����, cpu�޸� �������) �̰����� ���� �ȴ�
		return nullptr;
	}
	//�̹� �ҷ��� �̹����� �ٽ� �ҷ����� �߰ų�
	//�ٸ� �̹����� ���� �̸����� ���� ������� �̰����� ���� �ȴ�
	return find->second;
}

texture* cImageManager::FindImage(const string& key)
{
	auto find = m_images.find(key);//�̸����� �̹����� ã�ƺ���
	if (find == m_images.end()) return nullptr;//������ nullptr�� ��´�
	return find->second;//������ �װ� ��´�
}

void cImageManager::Init()
{
	D3DXCreateSprite(g_device, &m_sprite);

	D3DXMatrixIdentity(&Worldmat);
	D3DXMatrixScaling(&Worldmat, 2, 2, 1);

	D3DXCreateFontW(DXUTGetD3D9Device(), 12, 0, 0, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, L"���� ��� Bold", &m_Font[12]);
	D3DXCreateFontW(DXUTGetD3D9Device(), 20, 0, 0, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, L"���� ��� Bold", &m_Font[20]);
	D3DXCreateFontW(DXUTGetD3D9Device(), 30, 0, 0, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, L"���� ��� Bold", &m_Font[30]);
}

void cImageManager::Release()
{
	for (auto iter : m_images)
	{
		iter.second->texturePtr->Release();
		SAFE_DELETE(iter.second);
	}
	SAFE_RELEASE(m_Font[12]);
	SAFE_RELEASE(m_Font[20]);
	SAFE_RELEASE(m_Font[30]);

	m_images.clear();
	m_sprite->Release();
}

void cImageManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &Worldmat);
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::Render(texture* texturePtr, Vector2 pos, Vector2 size, float rot, D3DCOLOR color)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;
		Vector2 CenterPos = Vector2(texturePtr->info.Width / 2, texturePtr->info.Height / 2);
		pos -= CenterPos;

		D3DXMatrixTransformation2D(&mat, &CenterPos, 0, &size, &CenterPos, rot, &pos);

		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void cImageManager::Render(texture* texturePtr, float x, float y, float rot)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;

		D3DXMatrixAffineTransformation2D(&mat, 1.f, nullptr, rot, &D3DXVECTOR2(x, y));
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cImageManager::CenterRender(texture* texturePtr, Vector2 pos, Vector2 size, float rot, D3DCOLOR color)
{
	Render(texturePtr, Vector2(pos.x - texturePtr->info.Width / 2, pos.y - texturePtr->info.Height / 2), size, rot, color);
}

void cImageManager::CenterRender(texture* texturePtr, float x, float y, float rot)
{
	Render(texturePtr, x - texturePtr->info.Width / 2, y - texturePtr->info.Height / 2, rot);
}

void cImageManager::RenderText(wstring Text, Vector2 Pos, int Size, D3DCOLOR Color)
{
	LPD3DXFONT Font;
	D3DXMATRIXA16 mat;

	D3DXCreateFontW(DXUTGetD3D9Device(), Size, 0, 0, 1,
		FALSE, HANGUL_CHARSET, 0, 0, 0, L"���� ��� Bold", &Font);

	D3DXMatrixAffineTransformation2D(&mat, 1.f, nullptr, 0, &Pos);
	m_sprite->SetTransform(&mat);
	Font->DrawTextW(m_sprite, Text.c_str(), Text.size(), NULL, DT_CENTER | DT_NOCLIP, Color);
	SAFE_RELEASE(Font);
}

void cImageManager::RenderTextCenter(wstring Text, Vector2 Pos, int Size, D3DCOLOR Color)
{
	D3DXMATRIXA16 mat;

	Pos.x -= Text.size() * Size * 0.25;

	D3DXMatrixAffineTransformation2D(&mat, 1.f, nullptr, 0, &Pos);
	m_sprite->SetTransform(&mat);
	m_Font[Size]->DrawTextW(m_sprite, Text.c_str(), Text.size(), NULL, DT_CENTER | DT_NOCLIP, Color);
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

vector<texture*> cImageManager::MakeVector(const string& Key)
{
	char _Key[50];
	texture* Image;
	sprintf(_Key, "%s1", Key.c_str());
	Image = FindImage(_Key);

	vector<texture*> Result;
	Result.push_back(Image);

	for (int i = 2; true; i++)
	{
		sprintf(_Key, "%s%d", Key.c_str(), i);
		if (Image = FindImage(_Key))
		{
			Result.push_back(Image);
		}
		else
		{
			break;
		}
	}

	return Result;
}