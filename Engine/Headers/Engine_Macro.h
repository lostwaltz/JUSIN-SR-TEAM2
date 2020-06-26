#pragma once

#define BEGIN(NAMESPACE) namespace NAMESPACE {
#define END }

#define USING(NAMESPACE) using namespace NAMESPACE;



#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif


#define MSG_BOX(MESSAGE) MessageBox(0, TEXT(MESSAGE), TEXT("System Error"), MB_OK)



#define DECLARE_SINGLETON(CLASSNAME)										\
	public: static CLASSNAME* Get_Instance();								\
	public: static unsigned long Destroy_Instance();						\
	private:	static CLASSNAME* m_pInstance;

#define IMPLEMENT_SINGLETON(CLASSNAME)										\
	CLASSNAME* CLASSNAME::m_pInstance = nullptr;							\
	CLASSNAME* CLASSNAME::Get_Instance() {												\
	if(nullptr == m_pInstance) {											\
	m_pInstance = new CLASSNAME; }											\
	return m_pInstance;														\
	}																		\
	unsigned long CLASSNAME::Destroy_Instance() {										\
	unsigned long dwRefCnt = 0;												\
	if(nullptr != m_pInstance) {											\
	dwRefCnt = m_pInstance->Release();										\
	if(0 == dwRefCnt) m_pInstance = nullptr;								\
	}																		\
	return dwRefCnt;														\
	}					
	


		

