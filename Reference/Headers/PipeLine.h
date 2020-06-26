#pragma once

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CPipeLine final : public CBase
{
	DECLARE_SINGLETON(CPipeLine)
private:
	explicit CPipeLine();
	virtual ~CPipeLine() = default;
public:
	_matrix Get_Transform(D3DTRANSFORMSTATETYPE eType) {
		return eType == D3DTS_VIEW ? m_ViewMatrix : m_ProjMatrix; }
	_float3 Get_CamPosition() {
		return *(_float3*)&m_CameraWorldMatrix.m[3][0]; }
public:
	HRESULT Set_Transform(D3DTRANSFORMSTATETYPE eType, _matrix StateMatrix);
public:
	HRESULT Update_PipeLine();
private:
	_matrix			m_CameraWorldMatrix;
	_matrix			m_ViewMatrix;
	_matrix			m_ProjMatrix;
public:
	virtual void Free();
};

END