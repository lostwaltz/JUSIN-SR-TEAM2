#pragma once

#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	explicit CBase();
	virtual ~CBase() = default;
private:
	unsigned long	m_dwRefCnt = 0; // ���۷���ī��Ʈ
public:
	unsigned long AddRef(); // ���۷���ī��Ʈ�� ������Ų��.
	unsigned long Release(); // ���۷���ī��Ʈ�� ���ҽ�Ų��(��ī�� 0�� �ƴҶ�). or �����Ѵ�.(��ī�� 0�϶�)
public:
	virtual void Free() = 0;
};

END