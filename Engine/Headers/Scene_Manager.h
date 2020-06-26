#pragma once

#include "Scene.h"

BEGIN(Engine)

class CScene_Manager final : public CBase
{
	DECLARE_SINGLETON(CScene_Manager)
private:
	explicit CScene_Manager();
	virtual ~CScene_Manager() = default;
public:
	HRESULT SetUp_CurrentScene(CScene* pCurrentScene);
	_int Update_CurrentScene(_double TimeDelta);
	HRESULT Render_CurrentScene();
private:
	CScene*			m_pCurrentScene = nullptr;
public:
	virtual void Free();
};

END