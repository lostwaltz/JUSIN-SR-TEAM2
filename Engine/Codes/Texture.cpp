#include "..\Headers\Texture.h"
#include "Shader.h"

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CTexture::CTexture(const CTexture & rhs)
	: CComponent(rhs)
	, m_Textures(rhs.m_Textures)
{
	for (auto& pTexture : m_Textures)
		Safe_AddRef(pTexture);

}

HRESULT CTexture::Set_TextureOnShader(CShader * pShader, D3DXHANDLE hParameter, _uint iIndex)
{
	if (nullptr == pShader || 
		m_Textures.size() <= iIndex)
		return E_FAIL;
	
	return pShader->Set_Texture(hParameter, m_Textures[iIndex]);	
}

HRESULT CTexture::Ready_Component_Prototype(TYPE eType, const _tchar* pTextureFilePath, _uint iNumTextures)
{
	m_Textures.reserve(iNumTextures);	
	
	for (size_t i = 0; i < iNumTextures; i++)
	{
		IDirect3DBaseTexture9*		pTexture = nullptr;

		_tchar		szFilePath[MAX_PATH] = L"";
		
		wsprintf(szFilePath, pTextureFilePath, i);

		switch (eType)
		{
		case TYPE_CUBE:
			if (FAILED(D3DXCreateCubeTextureFromFile(m_pGraphic_Device, szFilePath, (PDIRECT3DCUBETEXTURE9*)&pTexture)))
				return E_FAIL;
			break;
		case TYPE_GENERAL:
			if (FAILED(D3DXCreateTextureFromFile(m_pGraphic_Device, szFilePath, (PDIRECT3DTEXTURE9*)&pTexture)))
				return E_FAIL;
			break;
		}

		

		

		m_Textures.push_back(pTexture);
	}	

	return S_OK;
}

HRESULT CTexture::Ready_Component(void * pArg)
{
	return S_OK;
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pGraphic_Device, TYPE eType, const _tchar * pTextureFilePath, _uint iNumTextures)
{
	CTexture*	pInstance = new CTexture(pGraphic_Device);

	if (FAILED(pInstance->Ready_Component_Prototype(eType, pTextureFilePath, iNumTextures)))
	{
		MessageBox(0, L"Failed To Creating CVIBuffer", L"System Message", MB_OK);
			
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CTexture::Clone_Component(void * pArg)
{
	CTexture*	pInstance = new CTexture(*this);

	if (FAILED(pInstance->Ready_Component(pArg)))
	{
		MessageBox(0, L"Failed To Creating CVIBuffer", L"System Message", MB_OK);
		
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTexture::Free()
{
	for (auto& pTexture : m_Textures)
		Safe_Release(pTexture);

	m_Textures.clear();

	CComponent::Free();
}
