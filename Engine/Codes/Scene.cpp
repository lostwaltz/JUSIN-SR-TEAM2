#include "..\Headers\Scene.h"

CScene::CScene(PDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CScene::Ready_Scene()
{
	return S_OK;
}

_int CScene::Update_Scene(_double TimeDelta)
{
	return _int();
}

HRESULT CScene::Render_Scene()
{
	return S_OK;
}

void CScene::Free()
{
	Safe_Release(m_pGraphic_Device);
}
