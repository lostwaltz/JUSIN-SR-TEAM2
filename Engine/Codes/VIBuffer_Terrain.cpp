#include "..\Headers\VIBuffer_Terrain.h"

CVIBuffer_Terrain::CVIBuffer_Terrain(PDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Terrain::CVIBuffer_Terrain(const CVIBuffer_Terrain & rhs)
	: CVIBuffer(rhs)
{

}

HRESULT CVIBuffer_Terrain::Ready_Component_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ, _float fInterval)
{
	// 1. 어떤 정점, 어떤 인덱스들을 정의할건지. 

	// For.Vertices
	m_iStride = sizeof(VTXNORTEX);
	m_iNumVerticesX = iNumVerticesX;
	m_iNumVerticesY = 1;
	m_iNumVerticesZ = iNumVerticesZ;

	m_iNumVertices = iNumVerticesX * iNumVerticesZ;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	// For.Indices
	m_iIndexSize = sizeof(_ulong);
	m_iNumPrimitive = (iNumVerticesX - 1) * (iNumVerticesZ - 1) * 2;
	m_iNumIndices = m_iNumPrimitive * 3;
	m_eIndexFormat = D3DFMT_INDEX32;

	// 2. 위에 정의된 대로 버퍼를 생성하고.
	if (FAILED(CVIBuffer::Ready_Component_Prototype()))
		return E_FAIL;
	
	// 3. 생성된 버퍼에 값을 채우고. 

	// For.Vertices
	VTXNORTEX*		pVertices = nullptr;

	m_pVBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (size_t i = 0; i < iNumVerticesZ; ++i)
	{
		for (size_t j = 0; j < iNumVerticesX; ++j)
		{
			_uint iIndex = i * iNumVerticesX + j;

			pVertices[iIndex].vPosition = m_pVerticesPos[iIndex] = _float3(j * fInterval, 0.f, i * fInterval);
			pVertices[iIndex].vNormal = _float3(0.0f, 0.f, 0.f);
			pVertices[iIndex].vTexUV = _float2(j / _float(iNumVerticesX - 1), i / _float(iNumVerticesZ - 1));
		}
	}


	m_pVBuffer->Unlock();

	_ulong*	pIndices = nullptr;

	_uint		iNumIndices = 0;

	m_pIBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (size_t i = 0; i < iNumVerticesZ - 1; ++i)
	{
		for (size_t j = 0; j < iNumVerticesX - 1; ++j)
		{
			_uint iIndex = i * iNumVerticesX + j;

			_uint iIndices[4] = {
				{ iIndex + iNumVerticesX }, 
				{ iIndex + iNumVerticesX + 1},
				{ iIndex + 1 },
				{ iIndex },
			};

			// 오른쪽 위 삼각형.
			pIndices[iNumIndices++] = iIndices[0];
			pIndices[iNumIndices++] = iIndices[1];
			pIndices[iNumIndices++] = iIndices[2];

			// 왼쪽 하단 삼각형. 
			pIndices[iNumIndices++] = iIndices[0];
			pIndices[iNumIndices++] = iIndices[2];
			pIndices[iNumIndices++] = iIndices[3];
		}
	}
	
	m_pIBuffer->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Terrain::Ready_Component(void * pArg)
{
	return S_OK;
}

CVIBuffer_Terrain * CVIBuffer_Terrain::Create(PDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ, _float fInterval)
{
	CVIBuffer_Terrain*	pInstance = new CVIBuffer_Terrain(pGraphic_Device);

	if (FAILED(pInstance->Ready_Component_Prototype(iNumVerticesX, iNumVerticesZ, fInterval)))
	{
		MessageBox(0, L"Failed To Creating CVIBuffer_Terrain", L"System Message", MB_OK);

		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Terrain::Clone_Component(void * pArg)
{
	CVIBuffer_Terrain*	pInstance = new CVIBuffer_Terrain(*this);

	if (FAILED(pInstance->Ready_Component(pArg)))
	{
		MessageBox(0, L"Failed To Creating CVIBuffer_Terrain", L"System Message", MB_OK);

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Terrain::Free()
{
	CVIBuffer::Free();
}
