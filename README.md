# ExampleExtension

Every time NextHooker has a sentence of text ready,
it will call ```OnNewSentence``` on all extensions it finds sequentially,
plugging the output of ```OnNewSentence``` from the previous extension into the next extension.<br>
After the sentence has been processed by all extensions, it will be displayed.

# MiscInfo

## The following keys are in ```MiscInfo```
```"current select"```: always 0 unless the sentence is in the text channel currently selected by the user.<br>
```"text number"```: number uniquely identifying the text channel the sentence is in. Console text channel is always 0.<br>
```"process id"```: process id that the sentence is coming from.<br>

# Notes

You just need Visual Studio with basic C++ support to compile this project.<br>
Compile using Release configuration unless you built NextHooker from source yourself using a Debug configuration. Compile targeting x86 for NextHooker and x64 for NextHooker64.
