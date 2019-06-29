#include "Extension.h"

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MessageBoxW(NULL, L"Extension Loaded", L"Example", MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		MessageBoxW(NULL, L"Extension Removed", L"Example", MB_OK);
		break;
	}
	return TRUE;
}

//#define COPY_CLIPBOARD
//#define EXTRA_NEWLINES

/*
	Param sentence: sentence received by Textractor (UTF-16). Can be modified, Textractor will receive this modification only if true is returned.
	Param sentenceInfo: contains miscellaneous info about the sentence (see README).
	Return value: whether the sentence was modified.
	Textractor will display the sentence after all extensions have had a chance to process and/or modify it.
	The sentence will be destroyed if it is empty or if you call Skip().
	This function may be run concurrently with itself: please make sure it's thread safe.
	It will not be run concurrently with DllMain.
*/
bool ProcessSentence(std::wstring& sentence, SentenceInfo sentenceInfo)
{
	// Your code here...
#ifdef COPY_CLIPBOARD
	// This example extension automatically copies sentences from the hook currently selected by the user into the clipboard.
	if (sentenceInfo["current select"])
	{
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (sentence.size() + 2) * sizeof(wchar_t));
		memcpy(GlobalLock(hMem), sentence.c_str(), (sentence.size() + 2) * sizeof(wchar_t));
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_UNICODETEXT, hMem);
		CloseClipboard();
	}
	return false;
#endif // COPY_CLIPBOARD

#ifdef EXTRA_NEWLINES
	// This example extension adds extra newlines to all sentences.
	sentence += L"\r\n";
	return true;
#endif // EXTRA_NEWLINES
}
