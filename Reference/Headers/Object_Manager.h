#pragma once

// 0. ������ü���� �����Ѵ�.
// 1. ȭ�鳻�� �����ؾ��� ��ü���� �� ���ؿ� ���� �׷����ؼ� �����Ѵ�.

#include "Layer.h"

BEGIN(Engine)

class CComponent;
class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
public:
	explicit CObject_Manager();
	virtual ~CObject_Manager() = default;
public:
	CGameObject* Get_ObjectPointer(_uint iSceneID, const _tchar* pLayerTag, _uint iIndex = 0);
	CComponent* Get_ComponentPointer(_uint iSceneID, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex = 0);
public:
	HRESULT Reserve_Object_Manager(_uint iNumScene);
	HRESULT Add_Prototype(_uint iSceneID, const _tchar* pPrototypeTag, CGameObject* pPrototype);
	HRESULT Add_Object_ToLayer(_uint iPrototypeSceneID, const _tchar* pPrototypeTag, _uint iLayerSceneID, const _tchar* pLayerTag, void* pArg = nullptr);
	_int Update_Object_Manager(_double TimeDelta);
	HRESULT Clear_Object_Manager(_uint iSceneID);
private:
	_uint			m_iNumScenes = 0;


private: // For.Prototype_Object
	map<const _tchar*, CGameObject*>*		 m_pPrototypes = nullptr;
	typedef map<const _tchar*, CGameObject*> PROTOTYPES;

private: // For.Active_Object
	map<const _tchar*, CLayer*>*			m_pLayers = nullptr;
	typedef map<const _tchar*, CLayer*>		LAYERS;
public:
	CGameObject* Find_Prototype(_uint iPrototypeSceneID, const _tchar* pPrototypeTag);
	CLayer* Find_Layer(_uint iSceneID, const _tchar* pLayerTag);
public:
	virtual void Free();
};

END