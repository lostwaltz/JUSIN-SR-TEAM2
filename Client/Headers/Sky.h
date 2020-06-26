#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Management.h"

BEGIN(Client)

class CSky final : public CGameObject
{
private:
	explicit CSky(PDIRECT3DDEVICE9 pGraphic_Device);
	explicit CSky(const CSky& rhs);
	virtual ~CSky() = default;
public:
	virtual HRESULT Ready_GameObject_Prototype();
	virtual HRESULT Ready_GameObject(void* pArg);
	virtual _int Update_GameObject(_double TimeDelta);
	virtual _int Late_Update_GameObject(_double TimeDelta);
	virtual HRESULT Render_GameObject();
private:
	CShader*			m_pShaderCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CVIBuffer_Cube*		m_pVIBufferCom = nullptr;	
private:
	HRESULT Add_Component();
	HRESULT SetUp_ConstantTable();
public:
	static CSky* Create(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone_GameObject(void* pArg);
	virtual void Free();
};

END