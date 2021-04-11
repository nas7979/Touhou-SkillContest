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

//불러올 이미지를 부를 이름과 경로
texture* cImageManager::AddImage(const string& key, const string& path)
{
	auto find = m_images.find(key);//이미 있는 이름을 다시 쓰려고 하는게 아닌지 확인해본다
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
#pragma region 로딩실패
		DEBUG_LOG("ERROR! 이미지 로딩에 실패했습니다. 파일경로를 다시 확인해주세요");
		DEBUG_LOG("\tkey :" << key.c_str() << "\t path : " << path.c_str());
#pragma endregion
		//이미지 로딩이 실패했을경우(없는 파일, cpu메모리 부족등등) 이곳으로 오게 된다
		return nullptr;
	}
	//이미 불러온 이미지를 다시 불러오려 했거나
	//다른 이미지를 같은 이름으로 쓰고 있을경우 이곳으로 오게 된다
	return find->second;
}

texture* cImageManager::FindImage(const string& key)
{
	auto find = m_images.find(key);//이름으로 이미지를 찾아본다
	if (find == m_images.end()) return nullptr;//없으면 nullptr을 뱉는다
	return find->second;//있으면 그걸 뱉는다
}

void cImageManager::Init()
{
	D3DXCreateSprite(g_device, &m_sprite);

	D3DXMatrixIdentity(&Worldmat);
	D3DXMatrixScaling(&Worldmat, 2, 2, 1);

	D3DXCreateFontW(DXUTGetD3D9Device(), 12, 0, 0, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, L"맑은 고딕 Bold", &m_Font[12]);
	D3DXCreateFontW(DXUTGetD3D9Device(), 20, 0, 0, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, L"맑은 고딕 Bold", &m_Font[20]);
	D3DXCreateFontW(DXUTGetD3D9Device(), 30, 0, 0, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, L"맑은 고딕 Bold", &m_Font[30]);
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
		FALSE, HANGUL_CHARSET, 0, 0, 0, L"맑은 고딕 Bold", &Font);

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