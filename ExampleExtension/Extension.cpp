#include "stdafx.h"

struct InfoForExtension
{
	const char* propertyName;
	int propertyValue;
	InfoForExtension* nextProperty;
};

int GetProperty(const char* propertyName, InfoForExtension* miscInfo)
{
	InfoForExtension* miscInfoTraverser = miscInfo;
	while (miscInfoTraverser != nullptr)
		if (strcmp(propertyName, miscInfoTraverser->propertyName) == 0) return miscInfoTraverser->propertyValue;
		else miscInfoTraverser = miscInfoTraverser->nextProperty;

	return 0;
}

extern "C"
{
	/**
	* Param sentence: pointer to sentence received by NextHooker (UTF-16).
	* The sentence is held in a buffer only just large enough for it.
	* If you need to add more text, please copy into a new buffer, delete the old one, and return the new buffer.
	* Param miscInfo: pointer to start of singly linked list containing misc info about the sentence.
	* You can modify the linked list, and future extensions will be able to read that.
	* Return value: pointer to sentence NextHooker takes for future processing and display.
	* Return 'sentence' unless you created a new buffer as mentioned above.
	* NextHooker will display the sentence after all extensions have had a chance to process and/or modify it.
	* THIS FUNCTION MAY BE RUN SEVERAL TIMES CONCURRENTLY: PLEASE ENSURE THAT IT IS THREAD SAFE!
	*/
	__declspec(dllexport) wchar_t* OnNewSentence(wchar_t* sentence, InfoForExtension* miscInfo)
	{
#if 1
		// This example extension places sentences from the hook currently selected by the user into the clipboard
		if (GetProperty("current select", miscInfo))
		{
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (wcslen(sentence) + 1) * sizeof(wchar_t));
			memcpy(GlobalLock(hMem), sentence, (wcslen(sentence) + 1) * sizeof(wchar_t));
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hMem);
			CloseClipboard();
		}
		return sentence;
#else
		// This example extension adds extra newlines to all sentences
		wchar_t* newSentence = new wchar_t[wcslen(sentence) + 6];
		swprintf(newSentence, wcslen(sentence) + 6, L"%s\r\n", sentence);
		delete[] sentence;
		return newSentence;
#endif
	}
}
