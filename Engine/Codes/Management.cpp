#include "..\Headers\Management.h"

IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pInput_Device(CInput_Device::Get_Instance())
	, m_pTimer_Manager(CTimer_Manager::Get_Instance())
	, m_pScene_Manager(CScene_Manager::Get_Instance())
	, m_pObject_Manager(CObject_Manager::Get_Instance())
	, m_pComponent_Manager(CComponent_Manager::Get_Instance())
	, m_pPipeLine(CPipeLine::Get_Instance())
{
	Safe_AddRef(m_pInput_Device);
	Safe_AddRef(m_pPipeLine);
	Safe_AddRef(m_pComponent_Manager);
	Safe_AddRef(m_pObject_Manager);
	Safe_AddRef(m_pScene_Manager);
	Safe_AddRef(m_pTimer_Manager);
	Safe_AddRef(m_pGraphic_Device);
}


HRESULT CManagement::Ready_Engine(_uint iNumScenes)
{
	if (nullptr == m_pObject_Manager || 
		nullptr == m_pComponent_Manager)
		return E_FAIL;

	if (FAILED(m_pObject_Manager->Reserve_Object_Manager(iNumScenes)))
		return E_FAIL;

	if (FAILED(m_pComponent_Manager->Reserve_Component_Manager(iNumScenes)))
		return E_FAIL;

	return S_OK;
}

_int CManagement::Update_Engine(_double TimeDelta)
{
	if (nullptr == m_pScene_Manager ||
		nullptr == m_pObject_Manager || 
		nullptr == m_pPipeLine || 
		nullptr == m_pInput_Device)
		return -1;

	if (FAILED(m_pInput_Device->Set_Input_Device_State()))
		return -1;

	if (FAILED(m_pPipeLine->Update_PipeLine()))
		return -1;

	if (0x80000000 & m_pObject_Manager->Update_Object_Manager(TimeDelta))
		return -1;

	if (0x80000000 & m_pScene_Manager->Update_CurrentScene(TimeDelta))
		return -1;

	return _int();
}

HRESULT CManagement::Render_Engine()
{
	if (nullptr == m_pScene_Manager)
		return E_FAIL;

	if (FAILED(m_pScene_Manager->Render_CurrentScene()))
		return E_FAIL;

	return S_OK;
}

HRESULT CManagement::Clear_Engine(_uint iSceneID)
{
	if (nullptr == m_pComponent_Manager ||
		nullptr == m_pObject_Manager)
		return E_FAIL;

	if (FAILED(m_pObject_Manager->Clear_Object_Manager(iSceneID)))
		return E_FAIL;

	if (FAILED(m_pComponent_Manager->Clear_Component_Manager(iSceneID)))
		return E_FAIL;	

	return S_OK;
}


#pragma region DEVICE



HRESULT CManagement::Ready_Graphic_Device(HWND hWnd, CGraphic_Device::WINMODE eMode, _uint iBackSizeX, _uint iBackSizeY, PDIRECT3DDEVICE9 * ppGraphic_Device)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	return m_pGraphic_Device->Ready_Graphic_Device(hWnd, eMode, iBackSizeX, iBackSizeY, ppGraphic_Device);	
}

HRESULT CManagement::Ready_Input_Device(HINSTANCE hInst, HWND hWnd)
{
	if (nullptr == m_pInput_Device)
		return E_FAIL;

	return m_pInput_Device->Ready_Input_Device(hInst, hWnd);
}

_byte CManagement::Get_DIKeyState(_ubyte byKey)
{
	if (nullptr == m_pInput_Device)
		return E_FAIL;

	return m_pInput_Device->Get_DIKeyState(byKey);
}

_byte CManagement::Get_DIMouseKeyState(CInput_Device::DIMOUSEKEY eMouseKey)
{
	if (nullptr == m_pInput_Device)
		return E_FAIL;

	return m_pInput_Device->Get_DIMouseKeyState(eMouseKey);
}

_long CManagement::Get_DIMouseMoveState(CInput_Device::DIMOUSEMOVE eMouseMove)
{
	if (nullptr == m_pInput_Device)
		return E_FAIL;

	return m_pInput_Device->Get_DIMouseMoveState(eMouseMove);
}

#pragma endregion

#pragma region TIMER

HRESULT CManagement::Add_Timers(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Add_Timers(pTimerTag);	
}

_double CManagement::Compute_TimeDelta(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return 0.0;

	return m_pTimer_Manager->Compute_TimeDelta(pTimerTag);
}

#pragma endregion

#pragma  region SCENE

HRESULT CManagement::SetUp_CurrentScene(CScene * pCurrentScene)
{
	if (nullptr == m_pScene_Manager)
		return E_FAIL;

	return m_pScene_Manager->SetUp_CurrentScene(pCurrentScene);
}

#pragma endregion


#pragma region GAMEOBJECT

CGameObject * CManagement::Get_ObjectPointer(_uint iSceneID, const _tchar * pLayerTag, _uint iIndex)
{
	if (nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Get_ObjectPointer(iSceneID, pLayerTag, iIndex);
}

CComponent * CManagement::Get_ComponentPointer(_uint iSceneID, const _tchar * pLayerTag, const _tchar * pComponentTag, _uint iIndex)
{
	if (nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Get_ComponentPointer(iSceneID, pLayerTag, pComponentTag, iIndex);
}

HRESULT CManagement::Add_GameObject_Prototype(_uint iSceneID, const _tchar * pPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_Prototype(iSceneID, pPrototypeTag, pPrototype);
}

HRESULT CManagement::Add_Object_ToLayer(_uint iPrototypeSceneID, const _tchar * pPrototypeTag, _uint iLayerSceneID, const _tchar * pLayerTag, void * pArg)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_Object_ToLayer(iPrototypeSceneID, pPrototypeTag, iLayerSceneID, pLayerTag, pArg);
}

#pragma endregion


#pragma region COMPONENT

CComponent * CManagement::Clone_Component(_uint eSceneID, const _tchar * pComponentTag, void * pArg)
{
	if (nullptr == m_pComponent_Manager)
		return nullptr;

	return m_pComponent_Manager->Clone_ComponentPointer(eSceneID, pComponentTag, pArg);
}

HRESULT CManagement::Add_Component_Prototype(_uint eSceneID, const _tchar * pComponentTag, CComponent * pComponent)
{
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	return m_pComponent_Manager->Add_Component(eSceneID, pComponentTag, pComponent);	
}

HRESULT CManagement::Clear_Component_Manager(_uint eSceneID)
{
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	return m_pComponent_Manager->Clear_Component_Manager(eSceneID);
}

#pragma endregion

_matrix CManagement::Get_Transform(D3DTRANSFORMSTATETYPE eType)
{
	if (nullptr == m_pPipeLine)
		return _matrix();

	return m_pPipeLine->Get_Transform(eType);
}

_float3 CManagement::Get_CamPosition()
{
	if (nullptr == m_pPipeLine)
		return _float3();

	return m_pPipeLine->Get_CamPosition();
}

void CManagement::Release_Engine()
{
	if (0 != CManagement::Get_Instance()->Destroy_Instance())
		MSG_BOX("Failed To Release CManagement");

	if (0 != CObject_Manager::Get_Instance()->Destroy_Instance())
		MSG_BOX("Failed To Release CObject_Manager");

	if (0 != CComponent_Manager::Get_Instance()->Destroy_Instance())
		MSG_BOX("Failed To Release CComponent_Manager");

	if (0 != CScene_Manager::Get_Instance()->Destroy_Instance())
		MSG_BOX("Failed To Release CScene_Manager");

	if (0 != CTimer_Manager::Get_Instance()->Destroy_Instance())
		MSG_BOX("Failed To Release CTimer_Manager");

	if (0 != CPipeLine::Get_Instance()->Destroy_Instance())
		MSG_BOX("Failed To Release CPipeLine");

	if (0 != CInput_Device::Get_Instance()->Destroy_Instance())
		MSG_BOX("Failed To Release CInput_Device");

	if (0 != CGraphic_Device::Get_Instance()->Destroy_Instance())
		MSG_BOX("Failed To Release CGraphic_Device");
}


void CManagement::Free()
{
	Safe_Release(m_pPipeLine);
	Safe_Release(m_pComponent_Manager);
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pScene_Manager);
	Safe_Release(m_pTimer_Manager);
	Safe_Release(m_pInput_Device);
	Safe_Release(m_pGraphic_Device);
}
