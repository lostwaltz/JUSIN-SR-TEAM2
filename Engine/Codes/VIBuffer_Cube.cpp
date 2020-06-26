#include "..\Headers\VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube(PDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer_Cube & rhs)
	: CVIBuffer(rhs)
{

}

HRESULT CVIBuffer_Cube::Ready_Component_Prototype()
{
	// 1. 어떤 정점, 어떤 인덱스들을 정의할건지. 


	// For.Vertices
	m_iStride = sizeof(VTXCUBETEX);
	m_iNumVertices = 8;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

	// For.Indices
	m_iIndexSize = sizeof(_ushort);
	m_iNumPrimitive = 12;
	m_iNumIndices = m_iNumPrimitive * 3;
	m_eIndexFormat = D3DFMT_INDEX16;

	// 2. 위에 정의된 대로 버퍼를 생성하고.
	if (FAILED(CVIBuffer::Ready_Component_Prototype()))
		return E_FAIL;
	
	// 3. 생성된 버퍼에 값을 채우고. 

	// For.Vertices
	VTXCUBETEX*		pVertices = nullptr;

	m_pVBuffer->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = m_pVerticesPos[0] = _float3(-0.5f, 0.5f, -0.5f);
	pVertices[0].vTexUV = pVertices[0].vPosition;
	D3DXVec3Normalize(&pVertices[0].vTexUV, &pVertices[0].vTexUV);

	pVertices[1].vPosition = m_pVerticesPos[1] = _float3(0.5f, 0.5f, -0.5f);
	pVertices[1].vTexUV = pVertices[1].vPosition;
	D3DXVec3Normalize(&pVertices[1].vTexUV, &pVertices[1].vTexUV);

	pVertices[2].vPosition = m_pVerticesPos[2] = _float3(0.5f, -0.5f, -0.5f);
	pVertices[2].vTexUV = pVertices[2].vPosition;
	D3DXVec3Normalize(&pVertices[2].vTexUV, &pVertices[2].vTexUV);

	pVertices[3].vPosition = m_pVerticesPos[3] = _float3(-0.5f, -0.5f, -0.5f);
	pVertices[3].vTexUV = pVertices[3].vPosition;
	D3DXVec3Normalize(&pVertices[3].vTexUV, &pVertices[3].vTexUV);

	pVertices[4].vPosition = m_pVerticesPos[4] = _float3(-0.5f, 0.5f, 0.5f);
	pVertices[4].vTexUV = pVertices[4].vPosition;
	D3DXVec3Normalize(&pVertices[4].vTexUV, &pVertices[4].vTexUV);

	pVertices[5].vPosition = m_pVerticesPos[5] = _float3(0.5f, 0.5f, 0.5f);
	pVertices[5].vTexUV = pVertices[5].vPosition;
	D3DXVec3Normalize(&pVertices[5].vTexUV, &pVertices[5].vTexUV);

	pVertices[6].vPosition = m_pVerticesPos[6] = _float3(0.5f, -0.5f, 0.5f);
	pVertices[6].vTexUV = pVertices[6].vPosition;
	D3DXVec3Normalize(&pVertices[6].vTexUV, &pVertices[6].vTexUV);

	pVertices[7].vPosition = m_pVerticesPos[7] = _float3(-0.5f, -0.5f, 0.5f);
	pVertices[7].vTexUV = pVertices[7].vPosition;
	D3DXVec3Normalize(&pVertices[7].vTexUV, &pVertices[7].vTexUV);

	m_pVBuffer->Unlock();

	_ushort*	pIndices = nullptr;

	m_pIBuffer->Lock(0, 0, (void**)&pIndices, 0);

	_uint		iIndex = 0;

	// +x
	pIndices[iIndex++] = 1; pIndices[iIndex++] = 5; pIndices[iIndex++] = 6;
	pIndices[iIndex++] = 1; pIndices[iIndex++] = 6; pIndices[iIndex++] = 2;

	// -x
	pIndices[iIndex++] = 4; pIndices[iIndex++] = 0; pIndices[iIndex++] = 3;
	pIndices[iIndex++] = 4; pIndices[iIndex++] = 3; pIndices[iIndex++] = 7;

	// y
	pIndices[iIndex++] = 4; pIndices[iIndex++] = 5; pIndices[iIndex++] = 1;
	pIndices[iIndex++] = 4; pIndices[iIndex++] = 1; pIndices[iIndex++] = 0;

	// -y
	pIndices[iIndex++] = 3; pIndices[iIndex++] = 2; pIndices[iIndex++] = 6;
	pIndices[iIndex++] = 3; pIndices[iIndex++] = 6; pIndices[iIndex++] = 7;

	// z
	pIndices[iIndex++] = 5; pIndices[iIndex++] = 4; pIndices[iIndex++] = 7;
	pIndices[iIndex++] = 5; pIndices[iIndex++] = 7; pIndices[iIndex++] = 6;

	// -z
	pIndices[iIndex++] = 0; pIndices[iIndex++] = 1; pIndices[iIndex++] = 2;
	pIndices[iIndex++] = 0; pIndices[iIndex++] = 2; pIndices[iIndex++] = 3;

	m_pIBuffer->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Cube::Ready_Component(void * pArg)
{
	return S_OK;
}

CVIBuffer_Cube * CVIBuffer_Cube::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Cube*	pInstance = new CVIBuffer_Cube(pGraphic_Device);

	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		MessageBox(0, L"Failed To Creating CVIBuffer_Cube", L"System Message", MB_OK);

		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Cube::Clone_Component(void * pArg)
{
	CVIBuffer_Cube*	pInstance = new CVIBuffer_Cube(*this);

	if (FAILED(pInstance->Ready_Component(pArg)))
	{
		MessageBox(0, L"Failed To Creating CVIBuffer_Cube", L"System Message", MB_OK);

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Cube::Free()
{
	CVIBuffer::Free();
}
