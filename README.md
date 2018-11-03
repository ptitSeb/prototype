# prototype
===========

![prototype build status](https://api.travis-ci.org/ptitSeb/prototype.png "prototype build status")

This is ProtoType, an RType remake from Dark Castle Software.
This version compile on OpenPandora, Linux, ODROID and AmigaOS4, has the FMOD dependancy removed (using SDL_mixer instead, but can be re-activated), and has a few fixes in the code.
This game now use stb_image for Image Loading.

![sreenshot on Pandora](screenshot.png "screenshot on Pandora")

On Pandora and ODROID, it use [gl4es](http://github.com/ptitSeb/gl4es).

To compile on Pandora, type
`make`

To compile on ODROID, type
`make ODROID=1`

To compile on Linux x86, type
`make LINUX=1`

To compile on AmigaOS4, type
`make AMIGAOS4=1`

SDL2 is also supported, just add `SDL2=1` to the make command (better `make clean` before if needed).

To use legacy FMOD, add `FMOD=1` to the make command.

For more info, the website of the original game is here: http://xout.blackened-interactive.com/ProtoType/Prototype.html

For info on the Pandora version, go there: https://pyra-handheld.com/boards/threads/prototype.71887/

