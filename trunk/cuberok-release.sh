#!/bin/sh

USER=DrMoriarty
MAIL=drmoriarty.0@gmail.com

VER=$1
DIR=cuberok-${VER}
BUILD=0lenny

rm -rf ${DIR}
echo exporting source tree...
svn export http://cuberok.googlecode.com/svn/trunk ${DIR} 1> /dev/null
mv  ${DIR}/debian ./
tar -czf cuberok_${VER}_orig.tar.gz ${DIR}
mv ./debian ./${DIR}/
cd ${DIR}
export DEBEMAIL="${USER} <${MAIL}>"
dch -v ${VER}-${BUILD} New upstream release 
cat debian/changelog
echo building...
chmod +x debian/rules
dpkg-buildpackage -rfakeroot 1> /dev/null
cd ..
