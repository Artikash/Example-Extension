# ExampleExtension

Every time Textractor has a sentence of text ready,
it will call ```OnNewSentence``` on all extensions it finds sequentially,
plugging the output of ```OnNewSentence``` from the previous extension into the next extension.<br>
After the sentence has been processed by all extensions, it will be displayed.

# SentenceInfo

## The following properties are in ```SentenceInfo```
```"current select"```: always 0 unless the sentence is in the text thread selected by the user.<br>
```"hook address"```: address the hook was inserted at. May need cast to unsigned. Console text thread is always -1.<br>
```"process id"```: process id that the sentence is coming from. 0 for console and clipboard text threads.<br>
```"text handle"```: number that uniquely identifies the current text thread.<br>
```"text name"```: pointer to start of a wchar array of the name of the current text thread.<br>

# Notes

You just need Visual Studio with basic C++ support to compile this project.<br>
Compile using Release configuration unless you built Textractor from source yourself using a Debug configuration. Compile targeting x86 for Textractor and x64 for Textractor64.
