#include "DXUT.h"
#include "cAnimator.h"
#include "cRenderer.h"

cAnimator::cAnimator(cObject* Object, string ImageKey, float Delay, bool Once)
	:cComponent(Object), m_Delay(Delay), m_DefaultDelay(Delay), m_Once(Once)
{
	m_Paused = false;
	m_Images = IMAGE->MakeVector(ImageKey);
	m_pObject->GetComponent<cRenderer>()->SetImage(m_Images.at(0));
	m_CurrentFrame = 1;
	Timer = new cTimer(Delay, [&]()->void {
		if (m_Delay > 0 && m_CurrentFrame < m_Images.size() - 1)
		{
			m_CurrentFrame++;
		}
		else if (m_Delay < 0 && m_CurrentFrame != 0)
		{
			m_CurrentFrame--;
		}
		else if(m_CurrentFrame == m_Images.size() - 1 && m_Delay > 0)
		{
			if (m_Once == true)
			{
				m_Paused = true;
			}
			else
				m_CurrentFrame = 0;
		}
		else
		{
			if (m_Once == true)
			{
				m_Paused = true;
			}
			else
				m_CurrentFrame = m_Images.size() - 1;
		}
		m_pObject->GetComponent<cRenderer>()->SetImage(m_Images.at(m_CurrentFrame));
	}, true);
}

cAnimator::~cAnimator()
{
}

void cAnimator::Init()
{
	
}

void cAnimator::Update()
{
	if(!m_Paused) Timer->Update();
}

void cAnimator::Render()
{

}

void cAnimator::Release()
{
	Timer = nullptr;
	SAFE_DELETE(Timer);
}