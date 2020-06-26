#pragma once

// 1.클라이언트에서 중점적으로 사용해야할 기능들을 묶어놓은 클래스.
#include "Graphic_Device.h"
#include "Input_Device.h"
#include "Timer_Manager.h"
#include "Scene_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "PipeLine.h"

BEGIN(Engine)

class ENGINE_DLL CManagement final : public CBase
{
	DECLARE_SINGLETON(CManagement)
private:
	explicit CManagement();
	virtual ~CManagement() = default;
public:
	HRESULT Ready_Engine(_uint iNumScenes);
	_int Update_Engine(_double TimeDelta);
	HRESULT Render_Engine();
	HRESULT Clear_Engine(_uint iSceneID);

#pragma region DEVICE
public:
	HRESULT Ready_Graphic_Device(HWND hWnd, CGraphic_Device::WINMODE eMode, _uint iBackSizeX, _uint iBackSizeY, PDIRECT3DDEVICE9* ppGraphic_Device);
	HRESULT Ready_Input_Device(HINSTANCE hInst, HWND hWnd);
	_byte Get_DIKeyState(_ubyte byKey);
	_byte Get_DIMouseKeyState(CInput_Device::DIMOUSEKEY eMouseKey);
	_long Get_DIMouseMoveState(CInput_Device::DIMOUSEMOVE eMouseMove);	
#pragma endregion

#pragma region TIMER
public:
	HRESULT Add_Timers(const _tchar* pTimerTag);
	_double Compute_TimeDelta(const _tchar* pTimerTag);
#pragma endregion

#pragma region SCENE
public:
	HRESULT SetUp_CurrentScene(CScene* pCurrentScene);
#pragma endregion


#pragma region GAMEOBJECT

public:
	CGameObject* Get_ObjectPointer(_uint iSceneID, const _tchar* pLayerTag, _uint iIndex = 0);
	CComponent* Get_ComponentPointer(_uint iSceneID, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex = 0);
	HRESULT Add_GameObject_Prototype(_uint iSceneID, const _tchar* pPrototypeTag, CGameObject* pPrototype);
	HRESULT Add_Object_ToLayer(_uint iPrototypeSceneID, const _tchar* pPrototypeTag, _uint iLayerSceneID, const _tchar* pLayerTag, void* pArg = nullptr);
#pragma endregion



#pragma region COMPONENT
public:
	CComponent* Clone_Component(_uint eSceneID, const _tchar* pComponentTag, void* pArg = nullptr);
	HRESULT Add_Component_Prototype(_uint eSceneID, const _tchar* pComponentTag, CComponent* pComponent);
	HRESULT Clear_Component_Manager(_uint eSceneID);
#pragma endregion


#pragma region PIPELINE
	_matrix Get_Transform(D3DTRANSFORMSTATETYPE eType);	
	_float3 Get_CamPosition();
#pragma endregion
public:
	static void Release_Engine();

private:
	CGraphic_Device*	m_pGraphic_Device = nullptr;
	CInput_Device*		m_pInput_Device = nullptr;
	CTimer_Manager*		m_pTimer_Manager = nullptr;
	CScene_Manager*		m_pScene_Manager = nullptr;
	CObject_Manager*	m_pObject_Manager = nullptr;
	CComponent_Manager*	m_pComponent_Manager = nullptr;
	CPipeLine*			m_pPipeLine = nullptr;


public:
	virtual void Free();
};

END