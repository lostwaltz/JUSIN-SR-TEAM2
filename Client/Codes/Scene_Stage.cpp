#include "stdafx.h"
#include "..\Headers\Scene_Stage.h"
#include "Management.h"
#include "Camera_Free.h"

CScene_Stage::CScene_Stage(PDIRECT3DDEVICE9 pGraphic_Device)
	: CScene(pGraphic_Device)
{

}

HRESULT CScene_Stage::Ready_Scene()
{
	if (FAILED(Ready_Layer_Camera(L"Layer_Camera")))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(L"Layer_BackGround")))
		return E_FAIL;

	
	return S_OK;
}

_int CScene_Stage::Update_Scene(_double TimeDelta)
{
	return _int();
}

HRESULT CScene_Stage::Render_Scene()
{
	return S_OK;
}

HRESULT CScene_Stage::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CManagement*	pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	Safe_AddRef(pManagement);

	CCamera::STATEDESC			StateDesc;
	StateDesc.vEye = _float3(0.f, 10.0f, -12.0f);
	StateDesc.vAt = _float3(0.f, 0.f, 0.f);
	StateDesc.vAxisY = _float3(0.f, 1.f, 0.f);

	StateDesc.fFovy = D3DXToRadian(60.0f);
	StateDesc.fAspect = _float(g_iWinSizeX) / g_iWinSizeY;
	StateDesc.fNear = 0.2f;
	StateDesc.fFar = 300.f;

	StateDesc.TransformDesc.SpeedPerSec = 5.f;
	StateDesc.TransformDesc.RotatePerSec = D3DXToRadian(90.0f);

	if (FAILED(pManagement->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Camera_Free", SCENE_STAGE, pLayerTag, &StateDesc)))
		return E_FAIL;

	Safe_Release(pManagement);

	return S_OK;

}

HRESULT CScene_Stage::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CManagement*	pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	Safe_AddRef(pManagement);	

	if (FAILED(pManagement->Add_Object_ToLayer(SCENE_STAGE, L"GameObject_Terrain", SCENE_STAGE, pLayerTag)))
		return E_FAIL;

	if (FAILED(pManagement->Add_Object_ToLayer(SCENE_STAGE, L"GameObject_Sky", SCENE_STAGE, pLayerTag)))
		return E_FAIL;

	Safe_Release(pManagement);

	return S_OK;
}

CScene_Stage * CScene_Stage::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CScene_Stage*	pInstance = new CScene_Stage(pGraphic_Device);

	if (FAILED(pInstance->Ready_Scene()))
	{
		MSG_BOX("Failed To Create CScene_Stage");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Stage::Free()
{


	CScene::Free();
}
