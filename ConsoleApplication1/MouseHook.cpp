#define WINVER 0x0500
#include <windows.h>

HHOOK g_hHook = NULL;
HINSTANCE g_hInstance = NULL;


//Hook Procedure
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	//Only process if the wParam and lParam parameters contain information about a mouse message
	if (nCode == HC_ACTION) {
		MSLLHOOKSTRUCT* pMouse = (MSLLHOOKSTRUCT*)lParam;

		//Only display if the right mouse button is clicked
		if (wParam == WM_RBUTTONDOWN) {
			MessageBox(NULL, L"Right Mouse CLick", L"Mouse Hook", MB_OK);
		}
	}
	//passes hook information to the next hook procedure
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}


//Hook Installation Function
extern "C" __declspec(dllexport) void SetHook() {
	//check if null
	if(!g_hHook)
		g_hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, g_hInstance, 0);
}

//Hook Removal Function
extern "C" __declspec(dllexport) void RemoveHook() {
	//check if not null
	if (g_hHook) {
		UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
	}
}

//DLL Entry Point
BOOL APIENTRY DLLMAIN(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		g_hInstance = hModule;

	return TRUE;
}
