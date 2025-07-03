#include <Windows.h>
#include <iostream>

typedef void (*HookFunc)();

HMODULE g_hDll = NULL;

int main() {


	g_hDll = LoadLibrary(L"x64\\Debug\\WindowsHook.dll");
	if (!g_hDll) {
		std::cerr << "Failed to load library" << std::endl;
		return 1;
	}


	HookFunc SetMouseHook = (HookFunc)GetProcAddress(g_hDll, "SetMouseHook");
	HookFunc RemoveMouseHook = (HookFunc)GetProcAddress(g_hDll, "RemoveMouseHook");

	HookFunc SetKeyboardHook = (HookFunc)GetProcAddress(g_hDll, "SetKeyboardHook");
	HookFunc RemoveKeyboardHook = (HookFunc)GetProcAddress(g_hDll, "RemoveKeyboardHook");


	if (SetMouseHook && RemoveMouseHook && SetKeyboardHook && RemoveKeyboardHook) {

		SetMouseHook();
		std::cout << "Mouse Hook Set" << std::endl;

		SetKeyboardHook();
		std::cout << "Keyboard Hook Set" << std::endl;

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			std::cout << "message received" << std::endl;
			if (GetAsyncKeyState(VK_ESCAPE))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		RemoveMouseHook();
		std::cout << "Mouse Hook Removed" << std::endl;

		RemoveKeyboardHook();
		std::cout << "Keyboard Hook Removed" << std::endl;

		FreeLibrary(g_hDll);
		std::cout << "Library Freed" << std::endl;
	}

	else {
		std::cout << "failed to set hooks" << std::endl;
	}

	return 0;
}