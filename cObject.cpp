#include "DXUT.h"
#include "cObject.h"

cObject::cObject()
{
	
}

cObject::~cObject()
{

}

void cObject::Init()
{
	
}

void cObject::Update()
{
	
}

void cObject::Render()
{
	
}

void cObject::Release()
{
	for (auto iter : m_Components)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_Components.clear();
}