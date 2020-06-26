#pragma once

// 1.�����Ӱ����Ҷ� ���� ����.
// 2.��ü�� �������� �����Ҷ� ����ϱ� ����.
#include "Base.h"


// 1�ʿ� ������Ʈ�� 100��ȣ��ȴ�.
// m_dwTimeAcc�� 1�ʿ� 1��ŭ �����ϴ� ����.
// m_dwTimeAcc �������Ӵ� �󸶾� �����ұ�? 0.01�� �����ϴ� ����.

// Player.x + 5.0f * 0.01(��);

BEGIN(Engine)

class CTimer final : public CBase
{
private:
	explicit CTimer();
	virtual ~CTimer() = default;
public:
	HRESULT Ready_Timer();
	_double Compute_TimeDelta();
private:
	_double			m_TimeDelta = 0.0;
private:
	LARGE_INTEGER	m_FrameTime;
	LARGE_INTEGER	m_FixTime;
	LARGE_INTEGER	m_LastTime;
	LARGE_INTEGER	m_CpuTick;
public:
	static CTimer* Create();
	virtual void Free();
};

END