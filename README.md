# ExampleExtension

Every time NextHooker has a sentence of text ready,
it will call ```NewSentence``` on all extensions it finds sequentially,
plugging the output of ```NewSentence``` from the previous extension into the next extension.<br>
After the sentence has been processed by all extensions, it will be displayed.

# Notes

Please compile extensions for Release targeting x86 architecture!
