#pragma once
class cEffect
{
	friend class cEffectManager;
	friend class cSystemManager;

private:

	texture* m_texture;
	Vector2 m_Pos;
	Vector2 m_Size;
	Vector2 m_SizePerFrame;
	float m_Speed;
	float m_Direction;
	float m_Friction;
	float m_Rotate;
	int m_Alpha;
	float m_AlphaPerFrame;
	int m_Depth;
	wstring m_Text;
	int m_Color[3];

	void Init();
	void Update();
	void Render();
	void Release();

public:
	cEffect();
	~cEffect();
};

