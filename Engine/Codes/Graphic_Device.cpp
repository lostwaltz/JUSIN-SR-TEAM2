#include "..\Headers\Graphic_Device.h"

USING(Engine)
IMPLEMENT_SINGLETON(CGraphic_Device)

CGraphic_Device::CGraphic_Device()
{

}

HRESULT CGraphic_Device::Ready_Graphic_Device(HWND hWnd, WINMODE eMode, _uint iBackSizeX, _uint iBackSizeY, PDIRECT3DDEVICE9* ppGraphic_Device)
{	
	if (nullptr != m_pSDK)
		return E_FAIL;	

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	if (nullptr == m_pSDK)
		return E_FAIL;

	// 1. 장치의 사양을 조사한다.
	D3DCAPS9		Caps;
	ZeroMemory(&Caps, sizeof(D3DCAPS9));
	
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps)))
		return E_FAIL;
		
	// 2. 내 장치의 사용수준을 결정한다.
	_ulong dwBehaviorFlag = 0;

	if (Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		dwBehaviorFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		dwBehaviorFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;	

	dwBehaviorFlag |= D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS			PresentParameter;
	ZeroMemory(&PresentParameter, sizeof(D3DPRESENT_PARAMETERS));

	/*				
	UINT                FullScreen_RefreshRateInHz;
	UINT                PresentationInterval;
	*/

	PresentParameter.BackBufferCount = 1;
	PresentParameter.BackBufferWidth = iBackSizeX;
	PresentParameter.BackBufferHeight = iBackSizeY;
	PresentParameter.BackBufferFormat = D3DFMT_A8R8G8B8;

	PresentParameter.MultiSampleType = D3DMULTISAMPLE_NONE;
	PresentParameter.MultiSampleQuality = 0;

	PresentParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
	PresentParameter.hDeviceWindow = hWnd;
	PresentParameter.Windowed = eMode;

	PresentParameter.EnableAutoDepthStencil = TRUE;
	PresentParameter.AutoDepthStencilFormat = D3DFMT_D24S8;

	PresentParameter.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	PresentParameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// 3. 위에서 결정해 놓은 사항들을 바탕으로해서 장치를 생성한다.
	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, dwBehaviorFlag, &PresentParameter, &m_pGraphic_Device)))
		return E_FAIL;

	*ppGraphic_Device = m_pGraphic_Device;

	Safe_AddRef(m_pGraphic_Device);

	return S_OK;
}

void CGraphic_Device::Free()
{
	if (0 != Safe_Release(m_pGraphic_Device))
		MSG_BOX("Failed To Releasing IDirect3DDevice9");

	if(0 != Safe_Release(m_pSDK))
		MSG_BOX("Failed To Releasing IDirect3D9");
}
