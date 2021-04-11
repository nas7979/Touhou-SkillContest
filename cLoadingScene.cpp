#include "DXUT.h"
#include "cLoadingScene.h"


cLoadingScene::cLoadingScene()
{
}

cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	LoadingImage("Player_Idle", "Player/Player_Idle",4);
	LoadingImage("Player_MoveSide", "Player/Player_MoveSide", 7);
	LoadingImage("PlayerBullet", "Player/PlayerBullet", 2);
	LoadingImage("PlayerBall", "Player/PlayerBall");
	LoadingImage("Graze_Circle", "Player/Graze_Circle");
	LoadingImage("HitPoint", "Player/HitPoint");

	LoadingImage("Remi_Idle1", "Enemy/Boss/Remi_Idle1");
	LoadingImage("Remi_Move", "Enemy/Boss/Remi_Move", 2);
	LoadingImage("Remi_Bat", "Enemy/Boss/Remi_Bat", 5);
	LoadingImage("Flan_Idle", "Enemy/Boss/Flan_Idle", 6);
	LoadingImage("Flan_Move", "Enemy/Boss/Flan_Move", 2);
	LoadingImage("Zako1_Idle", "Enemy/Zako/Zako1", 6);
	LoadingImage("Zako1_Move", "Enemy/Zako/Zako1_Move", 4);
	LoadingImage("Zako2_Idle", "Enemy/Zako/Zako2", 6);
	LoadingImage("Zako2_Move", "Enemy/Zako/Zako2_Move", 4);
	LoadingImage("Zako3_Idle", "Enemy/Zako/Zako3", 6);
	LoadingImage("Zako3_Move", "Enemy/Zako/Zako3_Move", 4);
	LoadingImage("Zako4_Idle", "Enemy/Zako/Zako4", 4);
	LoadingImage("Zako4_Move", "Enemy/Zako/Zako4", 4);
	LoadingImage("Zako5_Idle", "Enemy/Zako/Zako5", 4);
	LoadingImage("Zako5_Move", "Enemy/Zako/Zako5", 4);
	LoadingImage("Zako6_Idle", "Enemy/Zako/Zako6", 8);
	LoadingImage("Zako6_Move", "Enemy/Zako/Zako6", 8);

	LoadingImage("Bullet_Ring", "Bullet/Bullet_Ring", 16);
	LoadingImage("Bullet_Been", "Bullet/Bullet_Been", 16);
	LoadingImage("Bullet_Circle", "Bullet/Bullet_Circle", 16);
	LoadingImage("Bullet_Rice", "Bullet/Bullet_Rice", 16);
	LoadingImage("Bullet_LargeRing", "Bullet/Bullet_LargeRing", 4);
	LoadingImage("Bullet_Fire", "Bullet/Bullet_Fire", 4);
	LoadingImage("Bullet_LargeCircle", "Bullet/Bullet_LargeCircle", 8);

	LoadingImage("ST1_Background", "Background/ST1_Background");
	LoadingImage("Back_Slow", "Background/Back_Slow");
	LoadingImage("Back_Remi", "Background/Back_Remi");
	LoadingImage("Back_Flan", "Background/Back_Flan");
	LoadingImage("Back_Title", "Background/Back_Title");
	LoadingImage("Back_Result", "Background/Back_Result");

	LoadingImage("Face_Remi", "Face/Face_Remi");
	LoadingImage("Face_Saku", "Face/Face_Saku");
	LoadingImage("Face_Flan", "Face/Face_Flan");

	LoadingImage("BulletHit", "Effect/BulletHit");
	LoadingImage("Bullet_FireEffect", "Effect/Bullet_FireEffect", 8);
	LoadingImage("Bullet_CreateEffect", "Effect/Bullet_CreateEffect", 8);
	LoadingImage("EnemyDeath", "Effect/EnemyDeath", 2);
	LoadingImage("Graze", "Effect/Graze", 4);
	LoadingImage("BossEffect", "Effect/BossEffect", 4);
	LoadingImage("Enemy_Circle", "Effect/Enemy_Circle");
	LoadingImage("Wave", "Effect/Wave");

	LoadingImage("Front", "UI/Front");
	LoadingImage("+", "UI/+");
	LoadingImage("", "UI/", 9);
	LoadingImage("0", "UI/0");
	LoadingImage("Gage", "UI/Gage");
	LoadingImage("Max", "UI/Max");
	LoadingImage("Life", "UI/Life");
	LoadingImage("BossHpBar", "UI/BossHpBar");
	LoadingImage("Enemy", "UI/Enemy");
	LoadingImage("SpellName", "UI/SpellName", 2);
	LoadingImage("Enemy_Life", "UI/Enemy_Life");
	LoadingImage("SpellBonus", "UI/SpellBonus");
	LoadingImage("How", "UI/How", 3);
	LoadingImage("Clear", "UI/Clear", 10);
	LoadingImage("Over", "UI/Over", 3);
	LoadingImage("Logo", "UI/Logo");

	LoadingImage("Item", "Item/Item", 6);
	LoadingImage("Item1Marker", "Item/Item1Marker");
	LoadingImage("Item2Marker", "Item/Item2Marker");
	LoadingImage("Item3Marker", "Item/Item3Marker");
	LoadingImage("Item4Marker", "Item/Item4Marker");
	LoadingImage("Item5Marker", "Item/Item5Marker");
	LoadingImage("Item6Marker", "Item/Item6Marker");

	LoadingSound("PlayerShot", "se_plst00");
	LoadingSound("Bonus", "se_bonus", 2);
	LoadingSound("Cancel", "se_cancel00");
	LoadingSound("Spell", "se_cat00", 0, 1.5);
	LoadingSound("PlayerSpell", "se_cat00", 0, 1.5);
	LoadingSound("BulletHit", "se_damage00");
	LoadingSound("EnemyDeath", "se_enep", 2);
	LoadingSound("Extend", "se_extend");
	LoadingSound("Graze", "se_graze");
	LoadingSound("Gun", "se_gun00");
	LoadingSound("Item", "se_item00");
	LoadingSound("Kira", "se_kira", 3);
	LoadingSound("Laser", "se_lazer", 2);
	LoadingSound("Ok", "se_ok00");
	LoadingSound("Select", "se_select00");
	LoadingSound("Pause", "se_pause");
	LoadingSound("PlayerDeath", "se_pldead00");
	LoadingSound("Power", "se_power", 2);
	LoadingSound("PowerUp", "se_powerup", 0, 2);
	LoadingSound("BulletShot", "se_tan", 3);
	LoadingSound("TimeOut", "se_timeout", 0, 3);
	LoadingSound("Field_Thema", "Field_Thema", 0, 2.5);
	LoadingSound("Remi_Thema", "Remi_Thema", 0, 3);
	LoadingSound("Flan_Thema", "Flan_Thema", 0, 3);

	SCENE->ChangeScene("Title");
}

void cLoadingScene::Update()
{

}

void cLoadingScene::Render()
{

}

void cLoadingScene::Release()
{

}

void cLoadingScene::LoadingImage(string Key, string Path, int Amount)
{
	if (Amount == 0)
	{
		char _Path[100];
		sprintf(_Path, "./Image/%s.png",Path.c_str());
		IMAGE->AddImage(Key.c_str(), _Path);
		DEBUG_LOG(_Path);
	}
	else
	{
		for (int i = 1; i <= Amount; i++)
		{
			char _Path[100];
			char _Key[50];
			sprintf(_Path, "./Image/%s%d.png", Path.c_str(),i);
			sprintf(_Key, "%s%d", Key.c_str(), i);
			IMAGE->AddImage(_Key, _Path);
		}
	}
}

void cLoadingScene::LoadingSound(string Key, string Path, int Amount, float Volume)
{
	if (Amount == 0)
	{
		char _Path[100];
		sprintf(_Path, "./Sound/%s.wav", Path.c_str());
		SOUND->AddSound(Key, _Path, Volume);
		DEBUG_LOG(_Path);
	}
	else
	{
		for (int i = 1; i <= Amount; i++)
		{
			char _Path[100];
			char _Key[50];
			sprintf(_Path, "./Sound/%s%d.wav", Path.c_str(), i);
			sprintf(_Key, "%s%d", Key.c_str(), i);
			SOUND->AddSound(_Key, _Path, Volume);
			DEBUG_LOG(_Path);
		}
	}
}