#pragma once
class cRenderer : public cComponent
{
	friend class cObject;
private:
	texture* m_Image;
	int m_Alpha;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cRenderer(cObject* Object);
	~cRenderer();

	texture* GetImage()
	{
		return m_Image;
	}
	void SetImage(texture* Texture)
	{
		m_Image = Texture;
	}

	int GetAlpha()
	{
		return m_Alpha;
	}
	void SetAlpha(int Alpha)
	{
		m_Alpha = Alpha;
	}
};

