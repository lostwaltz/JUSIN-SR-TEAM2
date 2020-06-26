#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "Transform.h"
#include "VIBuffer_Rect.h"
#include "VIBuffer_Cube.h"
#include "VIBuffer_Terrain.h"


BEGIN(Engine)

class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
private:
	explicit CComponent_Manager();
	virtual ~CComponent_Manager() = default;
public:
	CComponent* Clone_ComponentPointer(_uint eSceneID, const _tchar* pComponentTag, void* pArg = nullptr);
public:
	HRESULT Reserve_Component_Manager(_uint iNumScenes);
	HRESULT Add_Component(_uint eSceneID, const _tchar* pComponentTag, CComponent* pComponent);
	HRESULT Clear_Component_Manager(_uint eSceneID);
private:
	_uint			m_iNumScenes = 0;
private:
	map<const _tchar*, CComponent*>*			m_pComponents = nullptr; // Prototype
	typedef map<const _tchar*, CComponent*>		COMPONENTS;	
private:
	CComponent* Find_Component(_uint eSceneID, const _tchar* pComponentTag);
public:
	virtual void Free();
};

END