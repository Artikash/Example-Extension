#include "extension.h"
#include <mutex>

HWND hWnd;
std::mutex m;
std::wstring currentSentence = L"Waiting...";

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		WNDCLASSEXW wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hInstance = hModule;
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszClassName = L"Extra Window";
		wcex.lpfnWndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT
		{
			switch (message)
			{
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				RECT wndRect;
				GetWindowRect(hWnd, &wndRect);
				RECT rect = { 0, 0, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top };
				FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
				std::lock_guard<std::mutex> lock(m);
				DrawTextW(hdc, currentSentence.c_str(), -1, &rect, DT_WORDBREAK);
				EndPaint(hWnd, &ps);
				return 0;
			}
			default:
			{
				return DefWindowProcW(hWnd, message, wParam, lParam);
			}
			}
		};
		RegisterClassExW(&wcex);

		hWnd = CreateWindowExW(
			WS_EX_TOPMOST,
			L"Extra Window",
			L"Example Visual Extension",
			WS_THICKFRAME,
			CW_USEDEFAULT,
			0,
			CW_USEDEFAULT,
			0,
			FindWindowW(NULL, L"Textractor") /*NULL*/,
			NULL,
			hModule,
			nullptr
		);
		if (!hWnd) throw;
		ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);
	}
	break;
	case DLL_PROCESS_DETACH:
	{
		DestroyWindow(hWnd);
	}
	break;
	}
	return TRUE;
}

bool ProcessSentence(std::wstring& sentence, SentenceInfo sentenceInfo)
{
	if (sentenceInfo["current select"])
	{
		std::lock_guard<std::mutex> lock(m);
		currentSentence = sentence;
		InvalidateRect(hWnd, nullptr, FALSE); // Force window repaint
	}
	return false;
}
