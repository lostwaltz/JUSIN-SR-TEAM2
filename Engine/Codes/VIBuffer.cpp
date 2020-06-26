#include "..\Headers\VIBuffer.h"
#include "PipeLine.h"

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & rhs)
	: CComponent(rhs)
	, m_pVBuffer(rhs.m_pVBuffer)
	, m_pIBuffer(rhs.m_pIBuffer)
	, m_iStride(rhs.m_iStride)
	, m_iNumVertices(rhs.m_iNumVertices)
	, m_dwFVF(rhs.m_dwFVF)
	, m_pVerticesPos(rhs.m_pVerticesPos)
	, m_iIndexSize(rhs.m_iIndexSize)
	, m_iNumIndices(rhs.m_iNumIndices)
	, m_iNumPrimitive(rhs.m_iNumPrimitive)
	, m_eIndexFormat(rhs.m_eIndexFormat)
	, m_iNumVerticesX(rhs.m_iNumVerticesX)
	, m_iNumVerticesY(rhs.m_iNumVerticesY)
	, m_iNumVerticesZ(rhs.m_iNumVerticesZ)

{
	Safe_AddRef(m_pIBuffer);
	Safe_AddRef(m_pVBuffer);	
}

HRESULT CVIBuffer::Ready_Component_Prototype()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pVerticesPos = new _float3[m_iNumVertices];

	// �������� �����ϴ� �迭������ �Ҵ��ߴ�. 	
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iStride * m_iNumVertices, 0, m_dwFVF, D3DPOOL_MANAGED, &m_pVBuffer, nullptr)))
		return E_FAIL;	

	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexSize * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIBuffer, nullptr)))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CVIBuffer::Ready_Component(void * pArg)
{
	return S_OK;
}

HRESULT CVIBuffer::Render_VIBuffer()
{
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pVBuffer)
		return E_FAIL;

	// 1. ��ġ��ü�� �����ؾ��� �������۸� ��ġ ������ ���°�� �����ұ��? 
	m_pGraphic_Device->SetStreamSource(0, m_pVBuffer, 0, m_iStride);	
	m_pGraphic_Device->SetFVF(m_dwFVF);
	m_pGraphic_Device->SetIndices(m_pIBuffer);
	m_pGraphic_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumPrimitive);

	return S_OK;
}

_bool CVIBuffer::Picking(HWND hWnd, _matrix WorldMatrix, _float3 * pOut)
{
	// ����Ʈ ���� ���콺 ��ġ�� ������.
	POINT		ptMouse;

	GetCursorPos(&ptMouse);
	ScreenToClient(hWnd, &ptMouse);

	D3DVIEWPORT9		ViewPort;
	m_pGraphic_Device->GetViewport(&ViewPort);

	_float4		vMousePos = _float4(ptMouse.x, ptMouse.y, 0.0f, 0.0f);
		
	// 2���� ���� �����̽��� ��ȯ�Ѵ�.(0, 0, g_iWinCX, g_iWinCY -> -1, 1, 1, -1)
	vMousePos.x = vMousePos.x / (ViewPort.Width * 0.5f) - 1.f;
	vMousePos.y = vMousePos.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;
	vMousePos.w = 1.f;

	CPipeLine* pPipeLine = CPipeLine::Get_Instance();
	if (nullptr == pPipeLine)
		return false;
	Safe_AddRef(pPipeLine);

	_matrix ProjMatrix = pPipeLine->Get_Transform(D3DTS_PROJECTION);
	D3DXMatrixInverse(&ProjMatrix, nullptr, &ProjMatrix);

	D3DXVec4Transform(&vMousePos, &vMousePos, &ProjMatrix);
	
	// �佺���̽� ���� ���콺 ����, ���콺�� �������� ���Ѵ�.
	_float3		vMousePivot = _float3(0.f, 0.f, 0.f);
	_float3		vMouseRay = _float3(vMousePos.x, vMousePos.y, vMousePos.z) - vMousePivot;

	_matrix ViewMatrix = pPipeLine->Get_Transform(D3DTS_VIEW);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	// ���彺���̽� ���� ���콺 ����, ���콺�� �������� ���Ѵ�.
	D3DXVec3TransformCoord(&vMousePivot, &vMousePivot, &ViewMatrix);
	D3DXVec3TransformNormal(&vMouseRay, &vMouseRay, &ViewMatrix);

	// ���÷� ����.
	_matrix	WorldMatrixInverse;
	D3DXMatrixInverse(&WorldMatrixInverse, nullptr, &WorldMatrix);

	// ���ý����̽� ���� ���콺 ����, ���콺�� �������� ���Ѵ�.
	D3DXVec3TransformCoord(&vMousePivot, &vMousePivot, &WorldMatrixInverse);
	D3DXVec3TransformNormal(&vMouseRay, &vMouseRay, &WorldMatrixInverse);

	D3DXVec3Normalize(&vMouseRay, &vMouseRay);


	for (size_t i = 0; i < m_iNumVerticesZ - 1; ++i)
	{
		for (size_t j = 0; j < m_iNumVerticesX - 1; ++j)
		{
			_uint iIndex = i * m_iNumVerticesX + j;

			_uint iIndices[4] = {
				{ iIndex + m_iNumVerticesX },
				{ iIndex + m_iNumVerticesX + 1},
				{ iIndex + 1 },
				{ iIndex },
			};

			_float		fU, fV, fDist;

			// �� ��� �ﰢ��.
			if (true == D3DXIntersectTri(&m_pVerticesPos[iIndices[1]], &m_pVerticesPos[iIndices[0]], &m_pVerticesPos[iIndices[2]], &vMousePivot, &vMouseRay, &fU, &fV, &fDist))
			{
				// *pOut = m_pVerticesPos[iIndices[1]] + (m_pVerticesPos[iIndices[0]] - m_pVerticesPos[iIndices[1]]) * fU + (m_pVerticesPos[iIndices[2]] - m_pVerticesPos[iIndices[1]]) * fV;
				*pOut = vMousePivot + *D3DXVec3Normalize(&vMouseRay, &vMouseRay) * fDist;
			}
				


			// �� �ϴ� �ﰢ��.
			if (true == D3DXIntersectTri(&m_pVerticesPos[iIndices[3]], &m_pVerticesPos[iIndices[2]], &m_pVerticesPos[iIndices[0]], &vMousePivot, &vMouseRay, &fU, &fV, &fDist))
				int a = 10;
		}

	}

	










	Safe_Release(pPipeLine);





	return _bool();
}

void CVIBuffer::Free()
{
	if(false == m_isClone)
		Safe_Delete_Array(m_pVerticesPos);

	Safe_Release(m_pIBuffer);
	Safe_Release(m_pVBuffer);

	CComponent::Free();
}
