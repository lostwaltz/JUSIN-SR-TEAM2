#pragma once

#include "Client_Defines.h"
#include "Management.h"

BEGIN(Client)

class CMainApp final : public CBase
{
private:
	explicit CMainApp();
	virtual ~CMainApp() = default;
public:
	HRESULT Ready_MainApp();
	_int Update_MainApp(_double TimeDelta);
	HRESULT Render_MainApp();
private:
	PDIRECT3DDEVICE9		m_pGraphic_Device = nullptr;
	CManagement*			m_pManagement = nullptr;
	CRenderer*				m_pRenderer = nullptr;
private:
	HRESULT Ready_Default_Setting();
	HRESULT Ready_Start_Scene(SCENEID eNextSceneID);
	HRESULT Ready_Default_GameObject();
	HRESULT Ready_Default_Component();

public:
	static CMainApp* Create();
	virtual void Free();
};

END