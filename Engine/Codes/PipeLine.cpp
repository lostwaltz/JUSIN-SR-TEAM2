#include "..\Headers\PipeLine.h"

IMPLEMENT_SINGLETON(CPipeLine)

CPipeLine::CPipeLine()
{

}

HRESULT CPipeLine::Set_Transform(D3DTRANSFORMSTATETYPE eType, _matrix StateMatrix)
{
	switch (eType)
	{
	case D3DTS_VIEW:
		m_ViewMatrix = StateMatrix;
		break;
	case D3DTS_PROJECTION:
		m_ProjMatrix = StateMatrix;
		break;
	}
	return S_OK;
}

HRESULT CPipeLine::Update_PipeLine()
{
	D3DXMatrixInverse(&m_CameraWorldMatrix, nullptr, &m_ViewMatrix);

	return S_OK;
}

void CPipeLine::Free()
{

}
