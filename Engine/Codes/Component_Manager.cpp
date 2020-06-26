#include "..\Headers\Component_Manager.h"

IMPLEMENT_SINGLETON(CComponent_Manager)

CComponent_Manager::CComponent_Manager()
{

}	

CComponent * CComponent_Manager::Clone_ComponentPointer(_uint eSceneID, const _tchar * pComponentTag, void* pArg)
{
	if (m_iNumScenes <= eSceneID)
		return nullptr;

	CComponent*	pPrototype = Find_Component(eSceneID, pComponentTag);
	if (nullptr == pPrototype)
		return nullptr;

	return pPrototype->Clone_Component(pArg);
}

HRESULT CComponent_Manager::Reserve_Component_Manager(_uint iNumScenes)
{
	if (nullptr != m_pComponents)
		return E_FAIL;

	m_pComponents = new COMPONENTS[iNumScenes];

	m_iNumScenes = iNumScenes;

	return S_OK;
}

HRESULT CComponent_Manager::Add_Component(_uint eSceneID, const _tchar * pComponentTag, CComponent * pComponent)
{
	if (m_iNumScenes <= eSceneID ||
		nullptr == pComponent ||
		nullptr != Find_Component(eSceneID, pComponentTag))
		return E_FAIL;

	m_pComponents[eSceneID].insert(COMPONENTS::value_type(pComponentTag, pComponent));

	return S_OK;
}

HRESULT CComponent_Manager::Clear_Component_Manager(_uint eSceneID)
{
	if (m_iNumScenes <= eSceneID)
		return E_FAIL;

	for (auto& Pair : m_pComponents[eSceneID])
		Safe_Release(Pair.second);

	m_pComponents[eSceneID].clear();

	return S_OK;
}

CComponent * CComponent_Manager::Find_Component(_uint eSceneID, const _tchar * pComponentTag)
{
	auto	iter = find_if(m_pComponents[eSceneID].begin(), m_pComponents[eSceneID].end(), CFinder_Tag(pComponentTag));

	if (iter == m_pComponents[eSceneID].end())
		return nullptr;

	return iter->second;
}

void CComponent_Manager::Free()
{
	for (size_t i = 0; i < m_iNumScenes; i++)
	{
		for (auto& Pair : m_pComponents[i])
			Safe_Release(Pair.second);

		m_pComponents[i].clear();
	}
	Safe_Delete_Array(m_pComponents);
}
