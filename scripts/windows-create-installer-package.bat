del /S /Q installer-package >nul 2>&1
if exist installer-package rmdir installer-package
mkdir installer-package
mkdir installer-package\installer
copy lib\* installer-package\
copy platform\libs\* installer-package\
copy bin\tdme\tools\installer\Installer.exe installer-package\
copy installer installer-package\installer\
