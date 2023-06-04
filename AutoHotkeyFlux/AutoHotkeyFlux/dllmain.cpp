// ╔═══════════════════════════════════════════════════╗
// ║ AutoHotkey Flux Apex Library                      ║
// ║ © 2023 Ian Pride - New Pride Software / Services  ║
// ║ Flux Apex's C/C++ functions for use in AutoHotkey ║
// ╚═══════════════════════════════════════════════════╝
#include "pch.h"
#include "Header.h"
BOOL APIENTRY DllMain(HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved
)
{
  (void)hModule;
  (void)lpReserved;
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}

