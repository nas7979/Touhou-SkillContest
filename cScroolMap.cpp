#include "DXUT.h"
#include "cScroolMap.h"


cScroolMap::cScroolMap()
	:m_scrool(0)
{
	m_backGround = IMAGE->AddImage("mapBackGround", "./Image/mapBackGround.png");
}

cScroolMap::~cScroolMap()
{
}

void cScroolMap::Update(float speed)
{
	m_scrool += speed * DXUTGetElapsedTime();
}

void cScroolMap::Render()
{
	//�ݺ��Ǵ� ��׶��� �̹����� ���÷� ����Ұ���
	float renderPos = (int)m_scrool % m_backGround->info.Height;
	m_backGround->CenterRender(768 / 2, 600 / 2 + renderPos - m_backGround->info.Height);
	m_backGround->CenterRender(768 / 2, 600 / 2 + renderPos);
}
