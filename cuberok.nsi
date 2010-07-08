!define VERSION "0.1.0-rc0"

Name "Cuberok ${VERSION}"

OutFile "win32\cuberok_setup-${VERSION}.exe"

InstallDir $PROGRAMFILES\Cuberok

; Request application privileges for Windows Vista
RequestExecutionLevel admin

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\Cuberok" "Install_Dir"

; First is default
LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Russian.nlf"

LicenseData license.txt

SetCompressor /SOLID lzma

; Pages

Page license
Page components
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles


Section "Cuberok"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "win32\Cuberok.exe"
  CreateDirectory $INSTDIR\translations
  File /oname=translations\cuberok_ru.qm "win32\translations\cuberok_ru.qm"
  File "win32\mingwm10.dll"
  File "win32\libtag.dll"
  File "license.txt"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\Cuberok "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Cuberok" "DisplayName" "Cuberok"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Cuberok" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Cuberok" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Cuberok" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

  CreateDirectory "$SMPROGRAMS\Cuberok"
  CreateShortCut "$SMPROGRAMS\Cuberok\Cuberok.lnk" "$INSTDIR\Cuberok.exe" "" "$INSTDIR\Cuberok.exe" 0
  CreateShortCut "$SMPROGRAMS\Cuberok\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Qt4 library"
  File "win32\QtCore4.dll"
  File "win32\QtGui4.dll"
  File "win32\QtNetwork4.dll"
  File "win32\QtSql4.dll"
  File "win32\QtXml4.dll"
  File "win32\QtWebKit4.dll"
  CreateDirectory $INSTDIR\sqldrivers
  File /oname=sqldrivers\qsqlite4.dll "win32\sqldrivers\qsqlite4.dll"
  CreateDirectory $INSTDIR\imageformats
  File /oname=imageformats\qgif4.dll "win32\imageformats\qgif4.dll"
  File /oname=imageformats\qjpeg4.dll "win32\imageformats\qjpeg4.dll"
  File /oname=imageformats\qmng4.dll "win32\imageformats\qmng4.dll"
  File /oname=imageformats\qsvg4.dll "win32\imageformats\qsvg4.dll"
  File /oname=imageformats\qtiff4.dll "win32\imageformats\qtiff4.dll"
SectionEnd

Section "Audiere plugin"
  CreateDirectory $INSTDIR\plugins
  File "win32\audiere.dll"
  File /oname=plugins\player_audiere.dll "win32\plugins\player_audiere.dll"
SectionEnd

Section "GStreamer plugin"
  CreateDirectory $INSTDIR\plugins
  File /oname=plugins\player_gst.dll "win32\plugins\player_gst.dll"
SectionEnd

Section "Phonon plugin"
  CreateDirectory $INSTDIR\plugins
  File /oname=plugins\player_phonon.dll "win32\plugins\player_phonon.dll"
SectionEnd

Section "FFmpeg plugin"
  CreateDirectory $INSTDIR\plugins
  File /oname=plugins\player_ffmpeg.dll "win32\plugins\player_ffmpeg.dll"
  File "win32\avcodec-52.dll"
  File "win32\avformat-52.dll"
  File "win32\avutil-50.dll"
  File "win32\SDL.dll"
SectionEnd

Section "Desktop Shortcut"
  CreateShortCut "$DESKTOP\Cuberok.lnk" "$INSTDIR\Cuberok.exe" "" "$INSTDIR\Cuberok.exe" 0
SectionEnd

Section /o "Sources"
  File /nonfatal "..\cuberok-${VERSION}.tar.gz"
SectionEnd

Section "Uninstall"
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Cuberok"
  DeleteRegKey HKLM SOFTWARE\Cuberok

  ; Remove files and uninstaller
  Delete $INSTDIR\uninstall.exe
  Delete "$INSTDIR\*.*"
  Delete "$INSTDIR\plugins\*.*"
  Delete "$INSTDIR\sqldrivers\*.*"
  Delete "$INSTDIR\imageformats\*.*"
  Delete "$INSTDIR\translations\*.*"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Cuberok\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Cuberok"
  RMDir "$INSTDIR\translations"
  RMDir "$INSTDIR\plugins"
  RMDir "$INSTDIR\sqldrivers"
  RMDir "$INSTDIR\imageformats"
  RMDir "$INSTDIR"
SectionEnd

;--------------------------------

Function .onInit

	;Language selection dialog

	Push ""
	Push ${LANG_ENGLISH}
	Push English
	Push ${LANG_RUSSIAN}
	Push Russian
	Push A ; A means auto count languages
	       ; for the auto count to work the first empty push (Push "") must remain
	LangDLL::LangDialog "Installer Language" "Please select the language of the installer"

	Pop $LANGUAGE
	StrCmp $LANGUAGE "cancel" 0 +2
		Abort
FunctionEnd
