#include "..\Headers\Camera.h"
#include "Transform.h"

CCamera::CCamera(PDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)	
	, m_pPipeLine(CPipeLine::Get_Instance())
{
	Safe_AddRef(m_pPipeLine);

}

CCamera::CCamera(const CCamera & rhs)
	: CGameObject(rhs)
	, m_pPipeLine(rhs.m_pPipeLine)
{
	Safe_AddRef(m_pPipeLine);

}

HRESULT CCamera::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CCamera::Ready_GameObject(void * pArg)
{
	if (nullptr != pArg)
		memcpy(&m_StateDesc, pArg, sizeof(STATEDESC));

	m_pTransformCom = CTransform::Create(m_pGraphic_Device);
	if (nullptr == m_pTransformCom)
		return E_FAIL;

	if (FAILED(m_pTransformCom->Ready_Component(&m_StateDesc.TransformDesc)))
		return E_FAIL;

	_float3		vRight, vUp, vLook, vPosition;

	vPosition = m_StateDesc.vEye;
	D3DXVec3Normalize(&vLook, &(m_StateDesc.vAt - m_StateDesc.vEye));
		
	D3DXVec3Cross(&vRight, &m_StateDesc.vAxisY, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	D3DXVec3Cross(&vUp, &vLook, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

_int CCamera::Update_GameObject(_double TimeDelta)
{
	if (nullptr == m_pPipeLine)
		return -1;

	m_pPipeLine->Set_Transform(D3DTS_VIEW, m_pTransformCom->Get_WorldMatrixInverse());

	_matrix			ProjMatrix;

	D3DXMatrixPerspectiveFovLH(&ProjMatrix, m_StateDesc.fFovy, m_StateDesc.fAspect, m_StateDesc.fNear, m_StateDesc.fFar);
	m_pPipeLine->Set_Transform(D3DTS_PROJECTION, ProjMatrix);

	return _int();
}

_int CCamera::Late_Update_GameObject(_double TimeDelta)
{
	

	return _int();
}

HRESULT CCamera::Render_GameObject()
{
	return S_OK;
}

void CCamera::Free()
{
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pPipeLine);

	CGameObject::Free();
}
