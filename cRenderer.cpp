#include "DXUT.h"
#include "cRenderer.h"

cRenderer::cRenderer(cObject* Object)
	:cComponent(Object)
{
}

cRenderer::~cRenderer()
{
}

void cRenderer::Init()
{
	m_Alpha = 255;
}

void cRenderer::Update()
{

}

void cRenderer::Render()
{
	IMAGE->Render(m_Image, m_pObject->GetPosition(), m_pObject->GetScale(), m_pObject->GetRotate(), D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));
}

void cRenderer::Release()
{

}
