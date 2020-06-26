#pragma once

// 1. ��ġ�� ����� �����Ѵ�.
// 2. �� ��ġ�� �������� �����Ѵ�.
// 3. ������ ������ ���� ���׵��� ���������ؼ� ��ġ�� �����Ѵ�.

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