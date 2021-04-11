#pragma once

class cGraze : public cComponent
{
	friend class cObject;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	cObject* m_Player;

public:
	cGraze(cObject* Object);
	~cGraze();

};

