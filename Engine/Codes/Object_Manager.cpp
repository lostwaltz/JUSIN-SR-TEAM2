#include "..\Headers\Object_Manager.h"

IMPLEMENT_SINGLETON(CObject_Manager)

CObject_Manager::CObject_Manager()
{
}


CGameObject * CObject_Manager::Get_ObjectPointer(_uint iSceneID, const _tchar * pLayerTag, _uint iIndex)
{
	if (m_iNumScenes <= iSceneID)
		return nullptr;

	CLayer*	pLayer = Find_Layer(iSceneID, pLayerTag);
	if (nullptr == pLayer)
		return nullptr;

	return pLayer->Get_ObjectPointer(iIndex);
}

CComponent* CObject_Manager::Get_ComponentPointer(_uint iSceneID, const _tchar * pLayerTag, const _tchar * pComponentTag, _uint iIndex)
{
	if (m_iNumScenes <= iSceneID)
		return nullptr;

	CLayer*	pLayer = Find_Layer(iSceneID, pLayerTag);
	if (nullptr == pLayer)
		return nullptr;

	return pLayer->Get_ComponentPointer(pComponentTag, iIndex);	
}

HRESULT CObject_Manager::Reserve_Object_Manager(_uint iNumScene)
{
	if (nullptr != m_pPrototypes || 
		nullptr != m_pLayers)
		return E_FAIL;

	m_pPrototypes = new PROTOTYPES[iNumScene];
	m_pLayers = new LAYERS[iNumScene];

	m_iNumScenes = iNumScene;

	return S_OK;
}

HRESULT CObject_Manager::Add_Prototype(_uint iPrototypeSceneID, const _tchar * pPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr == pPrototype ||
		m_iNumScenes <= iPrototypeSceneID ||
		nullptr != Find_Prototype(iPrototypeSceneID, pPrototypeTag))
		return E_FAIL;

	m_pPrototypes[iPrototypeSceneID].insert(PROTOTYPES::value_type(pPrototypeTag, pPrototype));

	return S_OK;
}

HRESULT CObject_Manager::Add_Object_ToLayer(_uint iPrototypeSceneID, const _tchar * pPrototypeTag, _uint iSceneID, const _tchar * pLayerTag, void* pArg)
{
	if (m_iNumScenes <= iPrototypeSceneID ||
		m_iNumScenes <= iSceneID)
		return E_FAIL;

	CGameObject* pPrototype = Find_Prototype(iPrototypeSceneID, pPrototypeTag);
	if (nullptr == pPrototype)
		return E_FAIL;

	CGameObject* pGameObject = pPrototype->Clone_GameObject(pArg);
	if (nullptr == pGameObject)
		return E_FAIL;

	CLayer* pLayer = Find_Layer(iSceneID, pLayerTag);
	if (nullptr == pLayer)
	{
		pLayer = CLayer::Create();
		if (nullptr == pLayer)
			goto except;

		if (FAILED(pLayer->Add_Object(pGameObject)))
			goto except;

		m_pLayers[iSceneID].insert(LAYERS::value_type(pLayerTag, pLayer));
	}
	else
	{
		if (FAILED(pLayer->Add_Object(pGameObject)))
			goto except;
	}

	return S_OK;

except:
	Safe_Release(pGameObject);
	return E_FAIL;
}

_int CObject_Manager::Update_Object_Manager(_double TimeDelta)
{
	for (size_t i = 0; i < m_iNumScenes; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
			{
				if (0x80000000 & Pair.second->Update_Layer(TimeDelta))
					return -1;
			}
		}
	}

	for (size_t i = 0; i < m_iNumScenes; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
			{
				if (0x80000000 & Pair.second->Late_Update_Layer(TimeDelta))
					return -1;
			}
		}
	}

	return _int();
}

HRESULT CObject_Manager::Clear_Object_Manager(_uint iSceneID)
{
	if (m_iNumScenes <= iSceneID)
		return E_FAIL;

	for (auto& Pair : m_pLayers[iSceneID])
		Safe_Release(Pair.second);

	m_pLayers[iSceneID].clear();

	for (auto& Pair : m_pPrototypes[iSceneID])
		Safe_Release(Pair.second);

	m_pPrototypes[iSceneID].clear();

	return S_OK;
}

CGameObject * CObject_Manager::Find_Prototype(_uint iPrototypeSceneID, const _tchar * pPrototypeTag)
{
	if (m_iNumScenes <= iPrototypeSceneID)
		return nullptr;

	auto	iter = find_if(m_pPrototypes[iPrototypeSceneID].begin(), m_pPrototypes[iPrototypeSceneID].end(), CFinder_Tag(pPrototypeTag));
	if (iter == m_pPrototypes[iPrototypeSceneID].end())
		return nullptr;

	return iter->second;
}

CLayer * CObject_Manager::Find_Layer(_uint iSceneID, const _tchar * pLayerTag)
{
	if (m_iNumScenes <= iSceneID)
		return nullptr;

	auto	iter = find_if(m_pLayers[iSceneID].begin(), m_pLayers[iSceneID].end(), CFinder_Tag(pLayerTag));
	if (iter == m_pLayers[iSceneID].end())
		return nullptr;

	return iter->second;
}

void CObject_Manager::Free()
{
	for (size_t i = 0; i < m_iNumScenes; i++)
	{
		for (auto& Pair : m_pLayers[i])
			Safe_Release(Pair.second);

		m_pLayers[i].clear();
	}
	Safe_Delete_Array(m_pLayers);

	for (size_t i = 0; i < m_iNumScenes; ++i)
	{
		for (auto& Pair : m_pPrototypes[i])
			Safe_Release(Pair.second);

		m_pPrototypes[i].clear();
	}
	Safe_Delete_Array(m_pPrototypes);
}
