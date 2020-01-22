#!/bin/sh
cd installer
find . | tail -n +2 > ../filelist.txt
cd ..
sed -e 's/^.\//put /' filelist.txt > filelist-put.txt
cd installer
ftp -p -n -v ftp.drewke.net <<END_SCRIPT
user drewke.net PASSWORD
binary
cd tdme2
cd repository
`cat ../filelist-put.txt`
quit
END_SCRIPT
cd ..
rm filelist.txt
rm filelist-put.txt
