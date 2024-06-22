#include "pch.h"
#include "Hack.h"


FastDraws* NewDraw = new FastDraws();

typedef HRESULT(WINAPI* _Present)(LPDIRECT3DDEVICE9 pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
_Present OriginalPresent;


void KM::Hack::CreateDevice(DWORD* pVtable)
{
	LPDIRECT3D9 mD3D = NULL;
	mD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (mD3D == NULL)
		MessageBox(NULL, "Falha no Direct3DCreate9", "...", MB_OK | MB_ICONINFORMATION);

	D3DPRESENT_PARAMETERS pParams;
	ZeroMemory(&pParams, sizeof(pParams));
	pParams.Windowed = true;
	pParams.BackBufferFormat = D3DFMT_UNKNOWN;
	pParams.SwapEffect = D3DSWAPEFFECT_DISCARD;

	LPDIRECT3DDEVICE9 pDevice;
	if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING
		, &pParams, &pDevice)))
		MessageBox(NULL, "Falha no LPDIRECT3DDEVICE9", "...", MB_OK | MB_ICONINFORMATION);

	DWORD* vTable = (DWORD*)pDevice;
	vTable = (DWORD*)vTable[0];
	pVtable[0] = vTable[16];
	pVtable[1] = vTable[17];
	pVtable[2] = vTable[42];
}

void KM::Hack::InitHook(void)
{
	DWORD vtabble[3] = { 0 };
	this->CreateDevice(vtabble);
	OriginalPresent = (_Present)vtabble[1];
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)OriginalPresent,(PVOID)My_Present);
	DetourTransactionCommit();
	printf("hook iniciado\n");
}

void KM::Hack::RemoveHook(void)
{
	//nothing here
}




HRESULT WINAPI KM::My_Present(LPDIRECT3DDEVICE9 pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, HRESULT ret)
{
	static bool Inited = false;
	static bool aimbot = false;
	if (Inited == false)
	{
		Inited = true;

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplWin32_Init(GetDesktopWindow());
		ImGui_ImplDX9_Init(pDevice);
	}
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Menu Opened");
	ImGui::Checkbox("Aimbot", &aimbot);
	ImGui::End();

	ShowCursor(true);

	ImGui::EndFrame();
	ImGui::Render();



	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	//NewDraw->DrawBox(255, 555, 254, 244, COR::VERDE, pDevice);
	ret = OriginalPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	return ret;
}
