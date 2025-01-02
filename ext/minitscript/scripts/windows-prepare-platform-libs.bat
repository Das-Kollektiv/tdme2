@echo off
if exist platform\libs del /S /Q platform\libs >nul 2>&1
if exist platform\libs rmdir platform\libs
if exist platform del /S /Q platform >nul 2>&1
if exist platform rmdir platform
mkdir platform
mkdir platform\libs
copy ext\windows-msc\openssl\lib\libcrypto-3-x64.dll platform\libs\.
copy ext\windows-msc\openssl\lib\libssl-3-x64.dll platform\libs\.
