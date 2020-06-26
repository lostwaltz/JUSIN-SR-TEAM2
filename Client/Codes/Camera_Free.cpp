#include "stdafx.h"
#include "..\Headers\Camera_Free.h"
#include "Management.h"

CCamera_Free::CCamera_Free(PDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{
}

CCamera_Free::CCamera_Free(const CCamera_Free & rhs)
	: CCamera(rhs)
{

}

HRESULT CCamera_Free::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CCamera_Free::Ready_GameObject(void * pArg)
{
	if (CCamera::Ready_GameObject(pArg))
		return E_FAIL;

	return S_OK;
}

_int CCamera_Free::Update_GameObject(_double TimeDelta)
{
	CManagement*		pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return -1;

	Safe_AddRef(pManagement);

	if (pManagement->Get_DIKeyState(DIK_W) & 0x80)
	{
		m_pTransformCom->Go_Straight(TimeDelta);
	}

	if (pManagement->Get_DIKeyState(DIK_S) & 0x80)
	{
		m_pTransformCom->Go_BackWard(TimeDelta);
	}

	if (pManagement->Get_DIKeyState(DIK_A) & 0x80)
	{
		m_pTransformCom->Go_Left(TimeDelta);
	}

	if (pManagement->Get_DIKeyState(DIK_D) & 0x80)
	{
		m_pTransformCom->Go_Right(TimeDelta);
	}

	_long	MouseMove = 0;

	if (MouseMove = pManagement->Get_DIMouseMoveState(CInput_Device::DIMM_X))
	{
		m_pTransformCom->Rotation_Axis(_float3(0.f, 1.f, 0.f), TimeDelta * (MouseMove / 7.0));
	}

	if (MouseMove = pManagement->Get_DIMouseMoveState(CInput_Device::DIMM_Y))
	{
		m_pTransformCom->Rotation_Axis(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), TimeDelta * (MouseMove / 7.0));
	}


	if (0 < pManagement->Get_DIMouseMoveState(CInput_Device::DIMM_WHEEL))
	{
		m_StateDesc.fFovy -= TimeDelta;
	}
	else if (0 > pManagement->Get_DIMouseMoveState(CInput_Device::DIMM_WHEEL))
		m_StateDesc.fFovy += TimeDelta;

	Safe_Release(pManagement);

	return CCamera::Update_GameObject(TimeDelta);
}

_int CCamera_Free::Late_Update_GameObject(_double TimeDelta)
{
	return CCamera::Late_Update_GameObject(TimeDelta);
}

HRESULT CCamera_Free::Render_GameObject()
{
	return S_OK;
}

CCamera_Free * CCamera_Free::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CCamera_Free*	pInstance = new CCamera_Free(pGraphic_Device);

	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("Failed To Creating CLoading");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCamera_Free::Clone_GameObject(void * pArg)
{
	CCamera_Free*	pInstance = new CCamera_Free(*this);

	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("Failed To Creating CLoading");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCamera_Free::Free()
{
	CCamera::Free();
}
