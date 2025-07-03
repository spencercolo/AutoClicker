#include "pch.h"
#include <windows.h>
#include <iostream>


HHOOK g_hHook = NULL;
HINSTANCE g_hInstance = NULL;

HHOOK k_hHook = NULL;
HINSTANCE k_hInstance = NULL;



//Hook Procedure
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	//Only process if the wParam and lParam parameters contain information about a mouse message
	if (nCode == HC_ACTION) {
		MSLLHOOKSTRUCT* pMouse = (MSLLHOOKSTRUCT*)lParam;
		//Only display if the right mouse button is clicked
		if (wParam == WM_RBUTTONDOWN) {
			//MessageBox(NULL, L"Right Mouse CLick", L"Mouse Hook", MB_OK);
			std::cout << "Right Click" << std::endl;
			//PostMessage(HWND_BROADCAST, nCode, wParam, lParam);
		}

		else if (wParam == WM_KEYDOWN) {
			std::cout << "Key Down" << std::endl;
			PostMessage(HWND_BROADCAST, WM_KEYDOWN, wParam, lParam);
		}
	}
	//passes hook information to the next hook procedure
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		std::cout << "Keyboard Click" << std::endl;
		std::cout << wParam << std::endl;
		if (wParam == 'j')
			std::cout << "Button F Clicked" << std::endl;
	}

	return CallNextHookEx(k_hHook, nCode, wParam, lParam);
}

extern "C" __declspec(dllexport) void SetKeyboardHook() {
	if (!k_hHook)
		k_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, k_hInstance, 0);
}

extern "C" __declspec(dllexport) void RemoveKeyboardHook() {
	if (k_hHook) {
		UnhookWindowsHookEx(k_hHook);
		k_hHook = NULL;
	}
}


//Mouse Hook Installation Function
extern "C" __declspec(dllexport) void SetMouseHook() {
	//check if null
	if (!g_hHook)
		g_hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, g_hInstance, 0);
}

//Mouse Hook Removal Function
extern "C" __declspec(dllexport) void RemoveMouseHook() {
	//check if not null
	if (g_hHook) {
		UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
	}
}

//DLL Entry Point
BOOL APIENTRY DLLMAIN(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		g_hInstance = hModule;
		k_hInstance = hModule;
	}

	return TRUE;
}
