#pragma once

// 화면에 그려야할 객체들응ㄹ 모아놓고 순서에 따라 렌더콜을 해준다.

#include "Component.h"

BEGIN(Engine)

class CGameObject;
class ENGINE_DLL CRenderer final : public CComponent
{
public:
	enum RENDERGROUP { RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHABLEND, RENDER_UI, RENDER_END };
private:
	explicit CRenderer(PDIRECT3DDEVICE9	 pGraphic_Device);	
	virtual ~CRenderer() = default;
public:
	HRESULT Ready_Component_Prototype();
	HRESULT Ready_Component(void* pArg);
public:
	HRESULT Add_RenderGroup(RENDERGROUP eGroup, CGameObject* pGameObject);
	HRESULT Draw_RenderGroup();
private:
	list<CGameObject*>			m_RenderGroup[RENDER_END];
	typedef list<CGameObject*>	RENDERLIST;	
private:
	HRESULT Render_Priority();
	HRESULT Render_NonAlpha();
	HRESULT Render_AlphaBlend();
	HRESULT Render_UI();

public:
	static CRenderer* Create(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone_Component(void* pArg);
	virtual void Free();
};

END