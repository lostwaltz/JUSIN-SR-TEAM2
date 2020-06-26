#pragma once

// 1. 장치의 사양을 조사한다.
// 2. 내 장치의 사용수준을 결정한다.
// 3. 위에서 결정해 놓은 사항들을 바탕으로해서 장치를 생성한다.

#include "Base.h"

BEGIN(Engine)

class CGraphic_Device final : public CBase
{
public:
	enum WINMODE { TYPE_FULL, TYPE_WIN, TYPE_END };
public:
	DECLARE_SINGLETON(CGraphic_Device)
private:
	explicit CGraphic_Device();
	virtual ~CGraphic_Device() = default;
public:
	HRESULT Ready_Graphic_Device(HWND hWnd, WINMODE eMode, _uint iBackSizeX, _uint iBackSizeY, PDIRECT3DDEVICE9* ppGraphic_Device);
private:
	PDIRECT3D9			m_pSDK = nullptr;
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
public:
	virtual void Free();
};

END