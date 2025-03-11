@REM GENERATE VS PROJECTS FOR WINDOWS
pushd ..\
call vendor\premake\premake5.exe vs2022
popd
PAUSE