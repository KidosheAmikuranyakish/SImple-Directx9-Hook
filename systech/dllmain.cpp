// dllmain.cpp : Define o ponto de entrada para o aplicativo DLL.
#include "pch.h"
#include "Hack.h"



bool Console()
{
    FILE* FStream;
    AllocConsole();
    freopen_s(&FStream, "CONOUT$", "w", stdout);

    return true;
}

typedef struct MyStruct
{
    bool CanInit;
}MYTYPES;


void InitThread() 
{
    KM::Hack* game = new KM::Hack();
    Console();
    static MYTYPES types;
    while (!GetModuleHandle("d3d9.dll") && !GetModuleHandle("samp.dll")) {
        Sleep(1000);
    }
    game->InitHook();
    while (true)
    {
        if (!types.CanInit)
            printf("hook inicado\n\n");

        types.CanInit = true;

        Sleep(1); // evitar sobrecarregar sistema :)
    }
}



BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitThread, NULL, NULL, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

