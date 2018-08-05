#!/bin/bash
git clone https://github.com/andreasdr/tdme2.git
cd tdme2
git checkout reactphysics3d-current
git pull
set -e
gmake -j4 mains
rm -rf package
mkdir package
mkdir package/tdme2
cp LICENSE package/tdme2
cp *.md package/tdme2
cp bin/tdme/tests/AngleTest package/tdme2
cp bin/tdme/tests/AudioTest package/tdme2
cp bin/tdme/tests/EngineTest package/tdme2
cp bin/tdme/tests/GUITest package/tdme2
cp bin/tdme/tests/LODTest package/tdme2
cp bin/tdme/tests/PathFindingTest package/tdme2
cp bin/tdme/tests/PhysicsTest1 package/tdme2
cp bin/tdme/tests/PhysicsTest2 package/tdme2
cp bin/tdme/tests/PhysicsTest3 package/tdme2
cp bin/tdme/tests/PhysicsTest4 package/tdme2
cp bin/tdme/tests/PivotTest package/tdme2
cp bin/tdme/tests/SkinningTest package/tdme2
cp bin/tdme/tests/ThreadingTest package/tdme2
cp bin/tdme/tests/UDPClientTest package/tdme2
cp bin/tdme/tests/UDPServerTest package/tdme2
cp bin/tdme/tools/cli/converttotm package/tdme2
cp bin/tdme/tools/cli/levelfixmodelszup2yup package/tdme2
cp bin/tdme/tools/leveleditor/TDMELevelEditor package/tdme2
cp bin/tdme/tools/modeleditor/TDMEModelEditor package/tdme2
cp bin/tdme/tools/particlesystem/TDMEParticleSystem package/tdme2
cp -R resources package/tdme2
cp -R shader package/tdme2
PACKAGE_FILE=tdme2-freebsd-x64_$(date +%F-%H-%M).tgz
cd package
tar -czf $PACKAGE_FILE .
echo $PACKAGE_FILE
ftp -p -v -n ftp.drewke.net <<END_SCRIPT
user drewke.net PASSWORD
binary
cd tdme2
put $PACKAGE_FILE
quit
END_SCRIPT
rm $PACKAGE_FILE
