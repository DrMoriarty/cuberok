!define VERSION "0.0.11-rc"

Name "Cuberok ${VERSION}"

OutFile "win32-vs\cuberok_setup-${VERSION}.exe"

InstallDir $PROGRAMFILES\Cuberok

; Request application privileges for Windows Vista
RequestExecutionLevel user

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
  File "win32-vs\Cuberok.exe"
  File "win32-vs\Cuberok.exe.manifest"
  CreateDirectory $INSTDIR\translations
  File /oname=translations\cuberok_ru.qm "win32-vs\translations\cuberok_ru.qm"
  File "win32-vs\tag.dll"
  File "win32-vs\msvcp71.dll"
  File "win32-vs\msvcr71.dll"
  File "win32-vs\msvcp80.dll"
  File "win32-vs\msvcr80.dll"
  File "win32-vs\x86_Microsoft.VC80.CRT_1fc8b3b9a1e18e3b_8.0.50727.762_x-ww_6b128700.manifest"
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
  File "win32-vs\QtCore4.dll"
  File "win32-vs\QtGui4.dll"
  File "win32-vs\QtNetwork4.dll"
  File "win32-vs\QtSql4.dll"
  File "win32-vs\QtXml4.dll"
  File "win32-vs\phonon4.dll"
  CreateDirectory $INSTDIR\phonon_backend
  File /oname=phonon_backend\phonon_ds94.dll "win32-vs\phonon_backend\phonon_ds94.dll"
  CreateDirectory $INSTDIR\sqldrivers
  File /oname=sqldrivers\qsqlite4.dll "win32-vs\sqldrivers\qsqlite4.dll"
  CreateDirectory $INSTDIR\imageformats
  File /oname=imageformats\qgif4.dll "win32-vs\imageformats\qgif4.dll"
  File /oname=imageformats\qjpeg4.dll "win32-vs\imageformats\qjpeg4.dll"
  File /oname=imageformats\qmng4.dll "win32-vs\imageformats\qmng4.dll"
  File /oname=imageformats\qsvg4.dll "win32-vs\imageformats\qsvg4.dll"
  File /oname=imageformats\qtiff4.dll "win32-vs\imageformats\qtiff4.dll"
SectionEnd

Section "Audiere plugin"
  CreateDirectory $INSTDIR\plugins
  File "win32-vs\audiere.dll"
  File /oname=plugins\player_audiere.dll "win32-vs\plugins\player_audiere.dll"
SectionEnd

;Section "GStreamer plugin"
;  CreateDirectory $INSTDIR\plugins
;  File /oname=plugins\player_gst.dll "win32-vs\plugins\player_gst.dll"
;SectionEnd

Section "Phonon plugin"
  CreateDirectory $INSTDIR\plugins
  File /oname=plugins\player_phonon.dll "win32-vs\plugins\player_phonon.dll"
SectionEnd

Section "FFmpeg plugin"
  CreateDirectory $INSTDIR\plugins
  File /oname=plugins\player_ffmpeg.dll "win32\plugins\player_ffmpeg.dll"
  File "win32\avcodec-52.dll"
  File "win32\avformat-52.dll"
  File "win32\avutil-50.dll"
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
  Delete "$INSTDIR\phonon_backend\*.*"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Cuberok\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Cuberok"
  RMDir "$INSTDIR\translations"
  RMDir "$INSTDIR\plugins"
  RMDir "$INSTDIR\sqldrivers"
  RMDir "$INSTDIR\imageformats"
  RMDir "$INSTDIR\phonon_backend"
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
