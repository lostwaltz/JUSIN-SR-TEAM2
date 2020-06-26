#include "..\Headers\Component.h"

CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
	, m_isClone(false)
{
	Safe_AddRef(m_pGraphic_Device);
}

CComponent::CComponent(const CComponent & rhs)
	: m_pGraphic_Device(rhs.m_pGraphic_Device)
	, m_isClone(true)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CComponent::Ready_Component_Prototype()
{
	return S_OK;
}

HRESULT CComponent::Ready_Component(void * pArg)
{
	return S_OK;
}

void CComponent::Free()
{
	Safe_Release(m_pGraphic_Device);
}
