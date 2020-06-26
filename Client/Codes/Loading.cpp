#include "stdafx.h"
#include "..\Headers\Loading.h"
#include "Terrain.h"
#include "Management.h"
#include "Sky.h"

USING(Client)

CLoading::CLoading(PDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

_uint APIENTRY Thread_Main(void* pArg)
{
	CLoading*		pLoading = (CLoading*)pArg;

	HRESULT	hr = 0;

	EnterCriticalSection(pLoading->Get_CriticalSection());

	switch (pLoading->Get_SceneID())
	{
	case SCENE_STAGE:
		hr = pLoading->Loading_ForStage();
		break;

	/*case SCENE_STAGE2:
		break;*/
	}

	LeaveCriticalSection(pLoading->Get_CriticalSection());

	if (FAILED(hr))
		return -1;

	return 0;
}

HRESULT CLoading::Ready_Loading(SCENEID eSceneID)
{
	m_eSceneID = eSceneID;

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoading::Loading_ForStage()
{
	CManagement*	pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	Safe_AddRef(pManagement);

#pragma region GAMEOBJECT_PROTOTYPE
	if (FAILED(pManagement->Add_GameObject_Prototype(SCENE_STAGE, L"GameObject_Terrain", CTerrain::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(pManagement->Add_GameObject_Prototype(SCENE_STAGE, L"GameObject_Sky", CSky::Create(m_pGraphic_Device))))
		return E_FAIL;
#pragma endregion


#pragma region COMPONENT_PROTOTYPE

	// For.Component_Shader_Terrain
	if (FAILED(pManagement->Add_Component_Prototype(SCENE_STAGE, L"Component_Shader_Terrain", CShader::Create(m_pGraphic_Device, L"../Bin/ShaderFiles/Shader_Terrain.fx"))))
		return E_FAIL;

	// For.Component_Texture_Terrain
	if (FAILED(pManagement->Add_Component_Prototype(SCENE_STAGE, L"Component_Texture_Terrain", CTexture::Create(m_pGraphic_Device, CTexture::TYPE_GENERAL, L"../Bin/Textures/Terrain/Grass_%d.tga", 2))))
		return E_FAIL;

	// For.Component_Texture_Sky
	if (FAILED(pManagement->Add_Component_Prototype(SCENE_STAGE, L"Component_Texture_Sky", CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, L"../Bin/Textures/SkyBox/Burger%d.dds", 4))))
		return E_FAIL;

	// For.Component_VIBuffer_Terrain
	if (FAILED(pManagement->Add_Component_Prototype(SCENE_STAGE, L"Component_VIBuffer_Terrain", CVIBuffer_Terrain::Create(m_pGraphic_Device, 129, 129))))
		return E_FAIL;



#pragma endregion

	m_isFinished = true;

	Safe_Release(pManagement);

	return S_OK;
}

CLoading * CLoading::Create(PDIRECT3DDEVICE9 pGraphic_Device, SCENEID eSceneID)
{
	CLoading*	pInstance = new CLoading(pGraphic_Device);

	if (FAILED(pInstance->Ready_Loading(eSceneID)))
	{
		MSG_BOX("Failed To Creating CLoading");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoading::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);

	DeleteCriticalSection(&m_CriticalSection);

	CloseHandle(m_hThread);

	Safe_Release(m_pGraphic_Device);
}
