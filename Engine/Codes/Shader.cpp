#include "..\Headers\Shader.h"

USING(Engine)

CShader::CShader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CShader::CShader(const CShader & rhs)
	: CComponent(rhs)
	, m_pEffect(rhs.m_pEffect)
{
	Safe_AddRef(m_pEffect);
}

HRESULT CShader::Ready_Component_Prototype(const _tchar * pFilePath)
{
	if (FAILED(D3DXCreateEffectFromFile(m_pGraphic_Device, pFilePath, nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr)))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CShader::Ready_Component(void * pArg)
{
	return S_OK;
}

HRESULT CShader::Set_Value(D3DXHANDLE hParameter, void* pData, _uint iSize)
{
	if (nullptr == m_pEffect)
		return E_FAIL;

	return m_pEffect->SetValue(hParameter, pData, iSize);	
}

HRESULT CShader::Set_Texture(D3DXHANDLE hParameter, IDirect3DBaseTexture9* pTexture)
{
	if (nullptr == m_pEffect)
		return E_FAIL;

	return m_pEffect->SetTexture(hParameter, pTexture);	
}

HRESULT CShader::Begin_Shader()
{
	if (nullptr == m_pEffect)
		return E_FAIL;

	return m_pEffect->Begin(nullptr, 0);
}

HRESULT CShader::End_Shader()
{
	if (nullptr == m_pEffect)
		return E_FAIL;

	return m_pEffect->End();
}

HRESULT CShader::Begin_Pass(_uint iIndex)
{
	if (nullptr == m_pEffect)
		return E_FAIL;

	return m_pEffect->BeginPass(iIndex);
}

HRESULT CShader::End_Pass()
{
	if (nullptr == m_pEffect)
		return E_FAIL;

	return m_pEffect->EndPass();
}

CShader * CShader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, const _tchar * pFilePath)
{
	CShader*	pInstance = new CShader(pGraphic_Device);

	if (FAILED(pInstance->Ready_Component_Prototype(pFilePath)))
	{
		MessageBox(0, L"Failed To Creating CShader", L"System Message", MB_OK);
		Safe_Release(pInstance);		
	}

	return pInstance;
}

CComponent * CShader::Clone_Component(void * pArg)
{
	CShader*	pInstance = new CShader(*this);

	if (FAILED(pInstance->Ready_Component(pArg)))
	{
		MessageBox(0, L"Failed To Creating CShader", L"System Message", MB_OK);
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CShader::Free()
{
	Safe_Release(m_pEffect);

	CComponent::Free();
}
