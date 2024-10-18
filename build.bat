if not exist build (
    mkdir build
)

set rootDir=%cd%
set includeDirs= -I%rootDir%/ext/include
set libDirs=/LIBPATH:%rootDir%/ext/lib
set links=SDL2.lib SDL2main.lib ImGui.lib

pushd build
if not exist ImGui.lib (
    cl %rootDir%/ext/src/compilation_unit.cpp -FoImGui.obj %includeDirs% /link /c %links% %libDirs%
    lib ImGui.obj
)
cl %rootDir%/src/*.cpp %includeDirs% -FeGame.exe /link %links% %libDirs%
popd build