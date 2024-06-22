#pragma once
#include "framework.h"
#include "pch.h"
#include "FastDraws.h"

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"





namespace KM{
	class Hack : public FastDraws
	{
		friend HRESULT WINAPI My_Present(LPDIRECT3DDEVICE9 pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, HRESULT ret);
	public:
		void CreateDevice(DWORD *pVtable);
		void InitHook(void);
		void RemoveHook(void);
	};
	HRESULT WINAPI My_Present(LPDIRECT3DDEVICE9 pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, HRESULT ret);
};


extern KM::Hack *game;