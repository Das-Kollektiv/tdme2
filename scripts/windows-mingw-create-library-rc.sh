#!/bin/bash
echo $1
cp resources/platforms/win32/lib.rc $2
LIBRARY=`echo $1 | grep -o '[a-zA-Z0-9\_\-]*\\.dll' | sed -e 's/\\.dll//'`
LIBRARY_LOWERCASE=`echo $LIBRARY | tr '[:upper:]' '[:lower:]'`
sed -i "s/{__LIBRARY__}/$LIBRARY/g" $2

