#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CLoading final : public CBase
{
private:
	explicit CLoading(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoading() = default;
public:
	SCENEID Get_SceneID() const {
		return m_eSceneID; }
	CRITICAL_SECTION* Get_CriticalSection() {
		return &m_CriticalSection; }
	const _tchar* Get_LoadingText() const {
		return m_szLoading; }
	_bool Get_Finished() const { 
		return m_isFinished; }
public:
	HRESULT Ready_Loading(SCENEID eSceneID); //스레드를 생성한다.
	HRESULT Loading_ForStage();
private:
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	CRITICAL_SECTION	m_CriticalSection;
private:
	SCENEID			m_eSceneID = SCENE_END;
	HANDLE			m_hThread = 0;
	_uint			m_iLoading;
	_tchar			m_szLoading[MAX_PATH] = L"";
	_bool			m_isFinished = false;

public:
	static CLoading* Create(PDIRECT3DDEVICE9 pGraphic_Device, SCENEID eSceneID);
	virtual void Free();
};

END