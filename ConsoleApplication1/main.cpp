#define WINVER 0x0500
#include <Windows.h>
#include <iostream>

typedef void (*HookFunc)();

HMODULE g_hDll = NULL;

int main() {
	g_hDll = LoadLibrary(L"MouseHook.dll");
	if (!g_hDll) {
		std::cerr << "Failed to load library" << std::endl;
		return 1;
	}


	HookFunc SetHook = (HookFunc)GetProcAddress(g_hDll, "SetHook");
	HookFunc RemoveHook = (HookFunc)GetProcAddress(g_hDll, "RemoveHook");

	if (SetHook && RemoveHook) {

		SetHook();
		std::cout << "Hook Set" << std::endl;

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			if (GetAsyncKeyState(VK_ESCAPE))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		RemoveHook();
		FreeLibrary(g_hDll);
	}
}