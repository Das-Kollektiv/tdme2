#!/bin/bash
rm -rf platform
mkdir platform
mkdir platform/libs
cp /mingw64/bin/glew32.dll platform/libs/
cp /mingw64/bin/glfw3.dll platform/libs/
cp /mingw64/bin/libgcc_s_seh-1.dll platform/libs/
cp /mingw64/bin/libopenal-1.dll platform/libs/
cp /mingw64/bin/libstdc++-6.dll platform/libs/
cp /mingw64/bin/libwinpthread-1.dll platform/libs/
cp /mingw64/bin/libfreetype-6.dll platform/libs/
cp /mingw64/bin/addr2line.exe platform/libs/