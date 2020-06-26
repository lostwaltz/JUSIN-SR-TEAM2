#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Terrain final : public CVIBuffer
{
private:
	explicit CVIBuffer_Terrain(PDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Terrain(const CVIBuffer_Terrain& rhs);
	virtual ~CVIBuffer_Terrain() = default;
public:
	virtual HRESULT Ready_Component_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ, _float fInterval);
	virtual HRESULT Ready_Component(void* pArg);	
public:
	static CVIBuffer_Terrain* Create(PDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ, _float fInterval = 1.f);
	virtual CComponent* Clone_Component(void* pArg);
	virtual void Free();
};

END