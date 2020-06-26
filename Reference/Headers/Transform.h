#pragma once

// 1. 객체의 상태를 가진다. (게임 세계 == 월드 스페이스) 월드변환 행렬.

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };
public:
	typedef struct tagStateDesc
	{
		_double SpeedPerSec = 0.0;
		_double RotatePerSec = 0.0;
	}STATEDESC;
private:
	explicit CTransform(PDIRECT3DDEVICE9 pGraphic_Device);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;
public: // Getter
	_float3 Get_State(STATE eState) const {
		return *(_float3*)&m_WorldMatrix.m[eState][0]; }
	_float3 Get_Scaled() const {
		return _float3(D3DXVec3Length(((_float3*)&m_WorldMatrix.m[STATE_RIGHT][0])), 
			D3DXVec3Length(((_float3*)&m_WorldMatrix.m[STATE_UP][0])), 
			D3DXVec3Length(((_float3*)&m_WorldMatrix.m[STATE_LOOK][0]))); }
	_matrix Get_WorldMatrix();
	_matrix Get_WorldMatrixInverse();

public: // Setter
	void Set_State(STATE eState, _float3 vState);

public:
	virtual HRESULT Ready_Component_Prototype();
	virtual HRESULT Ready_Component(void* pArg);

public: // For.Movement
	HRESULT Go_Straight(_double TimeDelta); // 현재월드스페이스 상에서 바라보고 있는 방향으로 가.
	HRESULT Go_BackWard(_double TimeDelta);
	HRESULT Go_Right(_double TimeDelta);
	HRESULT Go_Left(_double TimeDelta);

public: // For.Rotation
	HRESULT SetUp_Rotation(_float3 vAxis, _float fRadian);
	HRESULT Rotation_Axis(_float3 vAxis, _double TimeDelta);
private:
	STATEDESC		m_StateDesc;
	_matrix			m_WorldMatrix;
public:
	static CTransform* Create(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone_Component(void* pArg);
	virtual void Free();
};

END