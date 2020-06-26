#include "..\Headers\GameObject.h"
#include "Management.h"

CGameObject::CGameObject(PDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

CGameObject::CGameObject(const CGameObject & rhs)
	: m_pGraphic_Device(rhs.m_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameObject::Ready_GameObject_Prototype()
{

	return S_OK;
}

HRESULT CGameObject::Ready_GameObject(void * pArg)
{

		
	return S_OK;
}

_int CGameObject::Update_GameObject(_double TimeDelta)
{

	return _int();
}

_int CGameObject::Late_Update_GameObject(_double TimeDelta)
{

	return _int();
}

HRESULT CGameObject::Render_GameObject()
{

	return S_OK;
}

HRESULT CGameObject::Add_Component(_uint iPrototypeSceneID, const _tchar* pPrototypeTag, const _tchar * pComponentTag, CComponent** ppOut, void* pArg)
{
	if (nullptr != Find_Component(pComponentTag))
		return E_FAIL;

	CManagement*	pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	Safe_AddRef(pManagement);

	CComponent*	pComponent = pManagement->Clone_Component(iPrototypeSceneID, pPrototypeTag, pArg);
	if (nullptr == pComponent)
		return E_FAIL;

	m_Components.insert(COMPONENTS::value_type(pComponentTag, pComponent));

	*ppOut = pComponent;

	Safe_AddRef(pComponent);

	Safe_Release(pManagement);

	return S_OK;
}

CComponent * CGameObject::Find_Component(const _tchar * pComponentTag)
{
	auto	iter = find_if(m_Components.begin(), m_Components.end(), CFinder_Tag(pComponentTag));

	if(iter == m_Components.end())		
		return nullptr;

	return iter->second;
}

void CGameObject::Free()
{
	for (auto& Pair : m_Components)
		Safe_Release(Pair.second);

	m_Components.clear();

	Safe_Release(m_pGraphic_Device);
}
