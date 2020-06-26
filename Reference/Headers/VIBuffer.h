#pragma once

// VIBuffer -> Vertex Index Buffer
// 1. �������� �����ϴ� ��ü. 
// 2. �����ϰ� �ִ� �������� ȭ�鿡 �׷��ִ� ��Ȱ.
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer() = default;
public:
	virtual HRESULT Ready_Component_Prototype();
	virtual HRESULT Ready_Component(void* pArg);
	virtual HRESULT Render_VIBuffer();	
public:
	_bool Picking(HWND hWnd, _matrix WorldMatrix, _float3* pOut);

protected: // For.VertexBuffer
	PDIRECT3DVERTEXBUFFER9		m_pVBuffer = nullptr;
	_uint						m_iStride = 0;
	_uint						m_iNumVerticesX = 0;
	_uint						m_iNumVerticesY = 0;
	_uint						m_iNumVerticesZ = 0;
	_uint						m_iNumVertices = 0;
	_ulong						m_dwFVF = 0;

protected:
	PDIRECT3DINDEXBUFFER9		m_pIBuffer = nullptr;
	_uint						m_iIndexSize = 0;
	_uint						m_iNumIndices = 0;
	_uint						m_iNumPrimitive = 0;
	D3DFORMAT					m_eIndexFormat;

protected:
	_float3*					m_pVerticesPos = nullptr;

public:	
	virtual CComponent* Clone_Component(void* pArg) = 0;
	virtual void Free();
};

END