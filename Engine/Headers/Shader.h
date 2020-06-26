#pragma once

// 셰이더파일 하나를 컴파일하여 사용할 수 있도록 한다.
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CShader final : public CComponent
{
private:
	explicit CShader(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CShader(const CShader& rhs);
	virtual ~CShader() = default;
public:
	virtual HRESULT Ready_Component_Prototype(const _tchar* pFilePath);
	virtual HRESULT Ready_Component(void* pArg);
public:
	HRESULT Set_Value(D3DXHANDLE hParameter, void* pData, _uint iSize);
	HRESULT Set_Texture(D3DXHANDLE hParameter, IDirect3DBaseTexture9* pTexture);
	
public:
	HRESULT Begin_Shader();
	HRESULT End_Shader();
	HRESULT Begin_Pass(_uint iIndex);
	HRESULT End_Pass();

private:
	LPD3DXEFFECT			m_pEffect = nullptr;	

	
public:
	static CShader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, const _tchar* pFilePath);
	virtual CComponent* Clone_Component(void* pArg);
	virtual void Free();
};

END