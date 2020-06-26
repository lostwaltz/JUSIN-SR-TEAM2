#pragma once

// �ε����� �ǹ��ϴ� Ŭ����.
// ���������� �ε���ü�� ����.
#include "Client_Defines.h"
#include "Scene.h"
#include "Loading.h"

BEGIN(Client)

class CScene_Stage final : public CScene
{
private:
	explicit CScene_Stage(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CScene_Stage() = default;
public:
	virtual HRESULT Ready_Scene();
	virtual _int Update_Scene(_double TimeDelta);
	virtual HRESULT Render_Scene();
private:
	HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
public:
	static CScene_Stage* Create(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free();
};

END