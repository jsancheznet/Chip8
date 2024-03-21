@echo off

REM TODO(Jorge): Make sure we compile with all libraries in release mode

set SDL_INCLUDE="libraries\SDL2-2.30.1\include"
set SDL_LIB="libraries\SDL2-2.30.1\lib\x64"

set IncludeDirectories=-I%SDL_INCLUDE%
set LibDirectories=-LIBPATH:%SDL_LIB%

set CompilerFlags= -nologo -W4 -WX -Od -FS /Fm %IncludeDirectories% -Zi -EHsc -MD /D "_WINDOWS"
set LinkerFlags=-nologo -DEBUG %LibDirectories%

cl main.cpp %CompilerFlags% /link %LinkerFlags% -SUBSYSTEM:CONSOLE SDL2.lib SDL2main.lib shell32.lib
