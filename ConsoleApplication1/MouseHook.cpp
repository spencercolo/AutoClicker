#include <Windows.h>

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

