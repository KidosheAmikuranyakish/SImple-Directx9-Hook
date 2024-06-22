#pragma once
class FastDraws
{
public:
	void DrawBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9);
};

enum COR
{
	VERMELHA = D3DCOLOR_RGBA(255, 0, 0, 255),
	VERDE = D3DCOLOR_RGBA(0, 255, 0, 255),
	AZUL = D3DCOLOR_RGBA(0, 0, 255, 255),
	BRANCO = D3DCOLOR_RGBA(255, 255, 255, 255),
};

extern FastDraws* NewDraw;
