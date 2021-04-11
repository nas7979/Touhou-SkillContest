#pragma once

class cTimer;
class cPlayer : public cComponent
{
	friend class cObject;
	friend class cGraze;
private:
	cTimer* Timer_FireDelay = nullptr;
	cTimer* Timer_SubFireDelay = nullptr;
	cTimer* Timer_Deathbomb = nullptr;
	bool Fireable;
	bool SubFireable;
	bool Shift;
	bool Dead;
	bool Slowable;
	bool Deathbomb;
	float Graze_Circle_Alpha;
	Vector2 BallPos;
	texture* Bullet1;
	texture* Bullet2;

	cObject* AddBullet(Vector2 Pos, float Direction, int Damage, texture* Image);
	cObject* AddBullet(Vector2 Pos, float Direction, int Damage, texture* Image, cObject* Target);

	void Fire();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cPlayer(cObject* Object);
	~cPlayer();

	void SetSlowable(bool able)
	{
		Slowable = able;
	}
	bool GetDead()
	{
		return Dead;
	}
};

