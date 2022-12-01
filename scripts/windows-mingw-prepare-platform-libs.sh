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
# libfreetype-6 dependenciens
cp /mingw64/bin/libbz2-1.dll platform/libs/
cp /mingw64/bin/libharfbuzz-0.dll platform/libs/
cp /mingw64/bin/libbrotlidec.dll platform/libs/
cp /mingw64/bin/libbrotlicommon.dll platform/libs/
cp /mingw64/bin/libpng16-16.dll platform/libs/
cp /mingw64/bin/libfreetype-6.dll platform/libs/
cp /mingw64/bin/libglib-2.0-0.dll platform/libs/
cp /mingw64/bin/libgraphite2.dll platform/libs/
cp /mingw64/bin/libiconv-2.dll platform/libs/
cp /mingw64/bin/libintl-8.dll platform/libs/
cp /mingw64/bin/zlib1.dll platform/libs/
cp /mingw64/bin/libpcre-1.dll platform/libs/
cp /mingw64/bin/libpcre2-8-0.dll platform/libs/
#
cp /mingw64/bin/addr2line.exe platform/libs/
