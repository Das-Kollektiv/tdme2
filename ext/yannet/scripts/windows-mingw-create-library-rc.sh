#!/bin/bash
cp resources/platforms/win32/lib.rc $2
LIBRARY=`echo $1 | grep -o '[a-zA-Z0-9\_\-]*\\.dll' | sed -e 's/\\.dll//'`
sed -i "s/{__LIBRARY__}/$LIBRARY/g" $2

