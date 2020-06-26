#pragma once

#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	explicit CBase();
	virtual ~CBase() = default;
private:
	unsigned long	m_dwRefCnt = 0; // 레퍼런스카운트
public:
	unsigned long AddRef(); // 레퍼런스카운트를 증가시킨다.
	unsigned long Release(); // 레퍼런스카운트를 감소시킨다(레카가 0이 아닐때). or 삭제한다.(레카가 0일때)
public:
	virtual void Free() = 0;
};

END