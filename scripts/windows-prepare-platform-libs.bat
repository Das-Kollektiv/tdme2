if exist platform\libs bin del /S /Q platform\libs >nul 2>&1
if exist platform\libs rmdir platform\libs
if exist platform bin del /S /Q platform >nul 2>&1
if exist platform rmdir platform
mkdir platform
mkdir platform\libs
copy ext\fbx\win64\lib\libfbxsdk.dll platform\libs\.
copy ext\glfw3\lib\win64\glfw3.dll platform\libs\.
copy ext\windows-msc\glew\libs\glew32.dll platform\libs\.
copy ext\windows-msc\openal-soft\libs\OpenAl32.dll platform\libs\.
copy ext\windows-msc\pthread\libs\pthreadVC2.dll platform\libs\.
copy ext\freetype\lib\win64\freetype.dll platform\libs\.
