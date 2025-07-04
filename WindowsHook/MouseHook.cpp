#include "pch.h"
#include <windows.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>


HHOOK g_hHook = NULL;
HINSTANCE g_hInstance = NULL;

HHOOK k_hHook = NULL;
HINSTANCE k_hInstance = NULL;

bool isActive = false;
std::atomic<int> check{1};
std::mutex mtx;

void autoClick() {
	INPUT ips[2] = {};
	ips[0].type = INPUT_MOUSE;
	ips[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	ips[1].type = INPUT_MOUSE;
	ips[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;


	while (true) {
		if (check % 2 == 0) {
			//Sleep(20);
			SendInput(2, ips, sizeof(INPUT));
		}
		else break;
	}
}

//Hook Procedure
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	//Only process if the wParam and lParam parameters contain information about a mouse message
	if (nCode == HC_ACTION) {
		MSLLHOOKSTRUCT* pMouse = (MSLLHOOKSTRUCT*)lParam;
		//Only display if the right mouse button is clicked
		if (wParam == WM_MBUTTONDOWN) {
			if (check % 2 == 1) {
				std::thread t1(autoClick);
				check++;
			}

			else if (check % 2 == 0) {
				check++;
			}
			std::cout << "Middle Click" << std::endl;
		}
	}
	//passes hook information to the next hook procedure
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
		if (wParam == WM_KEYDOWN) {
			std::cout << "Keyboard Click" << std::endl;

			if (pKeyboard->vkCode == VK_ESCAPE) {
				std::cout << "Button Escape Clicked" << std::endl;
				//MessageBox(NULL, L"Escape Clicked", L"Message!", MB_OK);
			}

			else if (pKeyboard->vkCode == VK_ADD) {
				MessageBox(NULL, L"Press Escape to Close the Program", L"Instruction", MB_OK);
			}
		}
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
