#include "..\Headers\Layer.h"

CLayer::CLayer()
{

}

CGameObject * CLayer::Get_ObjectPointer(_uint iIndex)
{
	if (m_ObjectList.size() <= iIndex)
		return nullptr;

	auto	iter = m_ObjectList.begin();

	for (size_t i = 0; i < iIndex; ++i)
		++iter;

	return *iter;
}

CComponent * CLayer::Get_ComponentPointer(const _tchar * pComponentTag, _uint iIndex)
{
	/*if (m_ObjectList.size() <= iIndex)
		return nullptr;

	auto	iter = m_ObjectList.begin();

	for (size_t i = 0; i < iIndex; ++i)
		++iter;	

	return (*iter)->Find_Component(pComponentTag);*/

	return nullptr;
}

HRESULT CLayer::Ready_Layer()
{
	return S_OK;
}

HRESULT CLayer::Add_Object(CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_ObjectList.push_back(pGameObject);

	return S_OK;
}

_int CLayer::Update_Layer(_double TimeDelta)
{
	

	for (auto& pGameObject : m_ObjectList)
	{
		if (nullptr != pGameObject)
		{
			if (0x80000000 & pGameObject->Update_GameObject(TimeDelta))
				return -1;
		}			
	}

	return _int(0);
}

_int CLayer::Late_Update_Layer(_double TimeDelta)
{
	for (auto& pGameObject : m_ObjectList)
	{
		if (nullptr != pGameObject)
		{
			if (0x80000000 & pGameObject->Late_Update_GameObject(TimeDelta))
				return -1;
		}
	}
	return 0;
}

CLayer * CLayer::Create()
{
	CLayer*	pInstance = new CLayer();

	if (FAILED(pInstance->Ready_Layer()))
	{
		MSG_BOX("Failed To Creating CLayer");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLayer::Free()
{
	for (auto& pGameObject : m_ObjectList)
		Safe_Release(pGameObject);

	m_ObjectList.clear();
}
