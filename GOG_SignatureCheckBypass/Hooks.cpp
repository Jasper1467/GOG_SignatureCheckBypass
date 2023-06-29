#include "Hooks.h"

#include <stdexcept>

#include "MinHook/MinHook.h"

using WinVerifyTrustFn = LONG(__stdcall*)(HWND, GUID*, LPVOID);
WinVerifyTrustFn g_oWinVerifyTrustFn;

bool Hooks::Initialize()
{
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("MH_Initialize() failed!");

	if (MH_CreateHookApi(L"Wintrust.dll", "WinVerifyTrust", hkWinVerifyTrust, (void**)g_oWinVerifyTrustFn))
		throw std::runtime_error("MH_CreateHookApi failed!");

	return true;
}

LONG Hooks::hkWinVerifyTrust(HWND hwnd, GUID* pgActionID, LPVOID pWVTData)
{
	// Just in case they at one point start checking if WinVerifyTrust gets called
	g_oWinVerifyTrustFn(hwnd, pgActionID, pWVTData);

	return 0;
}