# ExampleExtension

Every time NextHooker has a sentence of text ready,
it will call ```OnNewSentence``` on all extensions it finds sequentially,
plugging the output of ```OnNewSentence``` from the previous extension into the next extension.<br>
After the sentence has been processed by all extensions, it will be displayed.

# Notes

Please compile extensions for Release targeting x86 architecture!
