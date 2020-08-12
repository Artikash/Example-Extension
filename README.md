# Example Extension

Every time Textractor has a sentence of text ready, it will call `ProcessSentence` on all extensions it finds sequentially (via `OnNewSentence`)
After the sentence has been processed by all extensions, it will be displayed.

# SentenceInfo

## The following properties are in `SentenceInfo`
`"current select"`: always 0 unless the sentence is in the text thread selected by the user.<br>
`"process id"`: process id that the sentence is coming from. 0 for console and clipboard.<br>
`"text number"`: number of the current text thread. Counts up one by one as text threads are created. 0 for console, 1 for clipboard.<br>
`"text name"`: pointer to start of a wchar array of the name of the current text thread.<br>
`"void (*AddSentence)(int64_t number, const wchar_t* sentence)"`: pointer to function that adds a sentence to the text thread with the specified number.<br>
`"void (*AddText)(int64_t number, const wchar_t* text)"`: similar to AddSentence, but doesn't treat the text like it's a full sentence.<br>
`"DWORD (*GetSelectedProcessId)()"`: pointer to function that returns the process id currently selected in Textractor's top left dropdown.

# Notes

You just need Visual Studio with basic C++ support to compile this project.
