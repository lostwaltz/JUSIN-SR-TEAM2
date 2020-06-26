#pragma once


BEGIN(Engine)


typedef struct tagVertex_Texture
{
	// 3차원 스페이스 상의 위치를 정의. (로컬스페이스)
	D3DXVECTOR3			vPosition;
	D3DXVECTOR2			vTexUV;
}VTXTEX;

typedef struct tagVertex_Cube_Texture
{
	// 3차원 스페이스 상의 위치를 정의. (로컬스페이스)
	D3DXVECTOR3			vPosition;
	D3DXVECTOR3			vTexUV;
}VTXCUBETEX;

typedef struct tagVertex_Normal_Texture
{
	// 3차원 스페이스 상의 위치를 정의. (로컬스페이스)
	D3DXVECTOR3			vPosition;
	D3DXVECTOR3			vNormal;
	D3DXVECTOR2			vTexUV;
}VTXNORTEX;

typedef struct tagVertex_Texture_Viewport
{
	
	// 위치
	D3DXVECTOR4		vPosition;

	// 정점이 참조해야할 이미지의 좌표.
	D3DXVECTOR2		vTexUV;
	D3DXVECTOR4		vWinPos;

}VTXTEX_VIEWPORT;

END