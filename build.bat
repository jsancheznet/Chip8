@echo off

REM TODO(Jorge): Make sure we compile with all libraries in release mode

set SDL_INCLUDE=""
set SDL_LIB=""

set IncludeDirectories=-I%SDL_INCLUDE%
set LibDirectories=

set CompilerFlags= -nologo -W4 -WX -Od -FS /Fm %IncludeDirectories% -Zi -EHsc -MD /D "_WINDOWS"
set LinkerFlags=-nologo -DEBUG %LibDirectories%

cl disasm.cpp %CompilerFlags% /link %LinkerFlags% -SUBSYSTEM:CONSOLE
