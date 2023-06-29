#pragma once
#include <Windows.h>

namespace Hooks
{
	bool Initialize();

	LONG hkWinVerifyTrust(HWND hwnd, GUID* pgActionID, LPVOID pWVTData);
}
