#!/bin/bash
rm -rf installer-package
mkdir installer-package
mkdir installer-package/installer
cp lib/* installer-package
cp platform/libs/* installer-package/
cp bin/tdme/tools/installer/Installer.exe installer-package/
cp -r installer installer-package/
