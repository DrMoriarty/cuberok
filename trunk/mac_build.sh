#!/bin/sh
#
# This script requires the use of the macdeployqt tool that is found in Qt 4.5
#
 
APP="cuberok"
VERSION="0.0.11"
QTDIR="/Developer/Tools/Qt"
 
DIR="bundle"
if [ -d $DIR.app ] ; then
echo "$DIR.app already exists"
    exit 1;
fi
 
# build app with Qt libraries
make distclean --quiet
qmake -r -config release -spec macx-g++
make --quiet
cp -rf unix/$APP.app mac/
$QTDIR/macdeployqt mac/$APP.app/

# other staff
mkdir mac/$APP.app/Contents/Resources/locale
cp translations/*.qm mac/$APP.app/Contents/Resources/locale/
 
# Create Bundle
mkdir $DIR
cp -rf mac/$APP.app $DIR/
hdiutil create -ov -srcfolder $DIR -format UDBZ -volname "$APP $VERSION" "$APP.dmg"
hdiutil internet-enable -yes "$APP.dmg"
rm -rf $DIR
 
DATE=`date +"%m-%d-%Y"`
mv $APP.dmg "$APP Snapshot ($DATE) Intel-qt4.5.dmg"
