#############################################################################
# Makefile for building: unix/cuberok
# Generated by qmake (2.01a) (Qt 4.3.4) on: ?? ???? 1 09:25:15 2008
# Project:  Cuberok.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile Cuberok.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DAUDIERE -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -I/usr/include/taglib -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -O2 -I/usr/include/taglib -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/lib/qt4/mkspecs/linux-g++ -I. -I/usr/lib/qt4/include/QtCore -I/usr/lib/qt4/include/QtCore -I/usr/lib/qt4/include/QtGui -I/usr/lib/qt4/include/QtGui -I/usr/lib/qt4/include/QtSql -I/usr/lib/qt4/include/QtSql -I/usr/lib/qt4/include -I-I/usr/local/include -Iunix/obj -I.
LINK          = g++
LFLAGS        = -Wl,-rpath,/usr/lib/qt4/lib
LIBS          = $(SUBLIBS)  -L/usr/lib/qt4/lib -L/usr/local/lib -laudiere -ltag -lQtSql -L/usr/lib -L/usr/lib/qt4/lib -lQtGui -L/usr/X11R6/lib -lpng -lSM -lICE -lXi -lXrender -lXrandr -lXfixes -lXcursor -lXinerama -lfreetype -lfontconfig -lXext -lX11 -lQtCore -lz -lm -lrt -ldl -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = unix/obj/

####### Files

SOURCES       = aboutdialog.cpp \
		collectionview.cpp \
		cuberok.cpp \
		database.cpp \
		indicator.cpp \
		lookandfeel.cpp \
		main.cpp \
		player.cpp \
		playlistcontainer.cpp \
		playlistmodel.cpp \
		playlistsettings.cpp \
		playlistview.cpp \
		progressbar.cpp \
		stardelegate.cpp \
		stareditor.cpp \
		starrating.cpp \
		tageditor.cpp \
		tagger.cpp unix/obj/moc_aboutdialog.cpp \
		unix/obj/moc_collectionview.cpp \
		unix/obj/moc_cuberok.cpp \
		unix/obj/moc_indicator.cpp \
		unix/obj/moc_lookandfeel.cpp \
		unix/obj/moc_player.cpp \
		unix/obj/moc_playlistcontainer.cpp \
		unix/obj/moc_playlistmodel.cpp \
		unix/obj/moc_playlistsettings.cpp \
		unix/obj/moc_playlistview.cpp \
		unix/obj/moc_progressbar.cpp \
		unix/obj/moc_stardelegate.cpp \
		unix/obj/moc_stareditor.cpp \
		unix/obj/moc_tageditor.cpp \
		unix/obj/qrc_resource.cpp
OBJECTS       = unix/obj/aboutdialog.o \
		unix/obj/collectionview.o \
		unix/obj/cuberok.o \
		unix/obj/database.o \
		unix/obj/indicator.o \
		unix/obj/lookandfeel.o \
		unix/obj/main.o \
		unix/obj/player.o \
		unix/obj/playlistcontainer.o \
		unix/obj/playlistmodel.o \
		unix/obj/playlistsettings.o \
		unix/obj/playlistview.o \
		unix/obj/progressbar.o \
		unix/obj/stardelegate.o \
		unix/obj/stareditor.o \
		unix/obj/starrating.o \
		unix/obj/tageditor.o \
		unix/obj/tagger.o \
		unix/obj/moc_aboutdialog.o \
		unix/obj/moc_collectionview.o \
		unix/obj/moc_cuberok.o \
		unix/obj/moc_indicator.o \
		unix/obj/moc_lookandfeel.o \
		unix/obj/moc_player.o \
		unix/obj/moc_playlistcontainer.o \
		unix/obj/moc_playlistmodel.o \
		unix/obj/moc_playlistsettings.o \
		unix/obj/moc_playlistview.o \
		unix/obj/moc_progressbar.o \
		unix/obj/moc_stardelegate.o \
		unix/obj/moc_stareditor.o \
		unix/obj/moc_tageditor.o \
		unix/obj/qrc_resource.o
DIST          = /usr/lib/qt4/mkspecs/common/g++.conf \
		/usr/lib/qt4/mkspecs/common/unix.conf \
		/usr/lib/qt4/mkspecs/common/linux.conf \
		/usr/lib/qt4/mkspecs/qconfig.pri \
		/usr/lib/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib/qt4/mkspecs/features/qt_config.prf \
		/usr/lib/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt4/mkspecs/features/default_pre.prf \
		/usr/lib/qt4/mkspecs/features/release.prf \
		/usr/lib/qt4/mkspecs/features/default_post.prf \
		/usr/lib/qt4/mkspecs/features/link_pkgconfig.prf \
		/usr/lib/qt4/mkspecs/features/qt.prf \
		/usr/lib/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib/qt4/mkspecs/features/moc.prf \
		/usr/lib/qt4/mkspecs/features/warn_on.prf \
		/usr/lib/qt4/mkspecs/features/resources.prf \
		/usr/lib/qt4/mkspecs/features/uic.prf \
		/usr/lib/qt4/mkspecs/features/yacc.prf \
		/usr/lib/qt4/mkspecs/features/lex.prf \
		Cuberok.pro
QMAKE_TARGET  = cuberok
DESTDIR       = unix/
TARGET        = unix/cuberok

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_aboutdialog.h ui_collectionview.h ui_cuberok.h ui_lookandfeel.h ui_tageditor.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) unix/ || $(MKDIR) unix/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Cuberok.pro  /usr/lib/qt4/mkspecs/linux-g++/qmake.conf /usr/lib/qt4/mkspecs/common/g++.conf \
		/usr/lib/qt4/mkspecs/common/unix.conf \
		/usr/lib/qt4/mkspecs/common/linux.conf \
		/usr/lib/qt4/mkspecs/qconfig.pri \
		/usr/lib/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib/qt4/mkspecs/features/qt_config.prf \
		/usr/lib/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt4/mkspecs/features/default_pre.prf \
		/usr/lib/qt4/mkspecs/features/release.prf \
		/usr/lib/qt4/mkspecs/features/default_post.prf \
		/usr/lib/qt4/mkspecs/features/link_pkgconfig.prf \
		/usr/lib/qt4/mkspecs/features/qt.prf \
		/usr/lib/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib/qt4/mkspecs/features/moc.prf \
		/usr/lib/qt4/mkspecs/features/warn_on.prf \
		/usr/lib/qt4/mkspecs/features/resources.prf \
		/usr/lib/qt4/mkspecs/features/uic.prf \
		/usr/lib/qt4/mkspecs/features/yacc.prf \
		/usr/lib/qt4/mkspecs/features/lex.prf \
		/usr/lib/qt4/lib/libQtSql.prl \
		/usr/lib/qt4/lib/libQtCore.prl \
		/usr/lib/qt4/lib/libQtGui.prl
	$(QMAKE) -unix -o Makefile Cuberok.pro
/usr/lib/qt4/mkspecs/common/g++.conf:
/usr/lib/qt4/mkspecs/common/unix.conf:
/usr/lib/qt4/mkspecs/common/linux.conf:
/usr/lib/qt4/mkspecs/qconfig.pri:
/usr/lib/qt4/mkspecs/features/qt_functions.prf:
/usr/lib/qt4/mkspecs/features/qt_config.prf:
/usr/lib/qt4/mkspecs/features/exclusive_builds.prf:
/usr/lib/qt4/mkspecs/features/default_pre.prf:
/usr/lib/qt4/mkspecs/features/release.prf:
/usr/lib/qt4/mkspecs/features/default_post.prf:
/usr/lib/qt4/mkspecs/features/link_pkgconfig.prf:
/usr/lib/qt4/mkspecs/features/qt.prf:
/usr/lib/qt4/mkspecs/features/unix/thread.prf:
/usr/lib/qt4/mkspecs/features/moc.prf:
/usr/lib/qt4/mkspecs/features/warn_on.prf:
/usr/lib/qt4/mkspecs/features/resources.prf:
/usr/lib/qt4/mkspecs/features/uic.prf:
/usr/lib/qt4/mkspecs/features/yacc.prf:
/usr/lib/qt4/mkspecs/features/lex.prf:
/usr/lib/qt4/lib/libQtSql.prl:
/usr/lib/qt4/lib/libQtCore.prl:
/usr/lib/qt4/lib/libQtGui.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile Cuberok.pro

dist: 
	@$(CHK_DIR_EXISTS) unix/obj/cuberok1.0.0 || $(MKDIR) unix/obj/cuberok1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) unix/obj/cuberok1.0.0/ && $(COPY_FILE) --parents aboutdialog.h collectionview.h cuberok.h database.h indicator.h lookandfeel.h main.h player.h playlistcontainer.h playlistmodel.h playlistsettings.h playlistview.h progressbar.h stardelegate.h stareditor.h starrating.h tageditor.h tagger.h unix/obj/cuberok1.0.0/ && $(COPY_FILE) --parents resource.qrc unix/obj/cuberok1.0.0/ && $(COPY_FILE) --parents aboutdialog.cpp collectionview.cpp cuberok.cpp database.cpp indicator.cpp lookandfeel.cpp main.cpp player.cpp playlistcontainer.cpp playlistmodel.cpp playlistsettings.cpp playlistview.cpp progressbar.cpp stardelegate.cpp stareditor.cpp starrating.cpp tageditor.cpp tagger.cpp unix/obj/cuberok1.0.0/ && $(COPY_FILE) --parents aboutdialog.ui collectionview.ui cuberok.ui lookandfeel.ui tageditor.ui unix/obj/cuberok1.0.0/ && (cd `dirname unix/obj/cuberok1.0.0` && $(TAR) cuberok1.0.0.tar cuberok1.0.0 && $(COMPRESS) cuberok1.0.0.tar) && $(MOVE) `dirname unix/obj/cuberok1.0.0`/cuberok1.0.0.tar.gz . && $(DEL_FILE) -r unix/obj/cuberok1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: unix/obj/moc_aboutdialog.cpp unix/obj/moc_collectionview.cpp unix/obj/moc_cuberok.cpp unix/obj/moc_indicator.cpp unix/obj/moc_lookandfeel.cpp unix/obj/moc_player.cpp unix/obj/moc_playlistcontainer.cpp unix/obj/moc_playlistmodel.cpp unix/obj/moc_playlistsettings.cpp unix/obj/moc_playlistview.cpp unix/obj/moc_progressbar.cpp unix/obj/moc_stardelegate.cpp unix/obj/moc_stareditor.cpp unix/obj/moc_tageditor.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) unix/obj/moc_aboutdialog.cpp unix/obj/moc_collectionview.cpp unix/obj/moc_cuberok.cpp unix/obj/moc_indicator.cpp unix/obj/moc_lookandfeel.cpp unix/obj/moc_player.cpp unix/obj/moc_playlistcontainer.cpp unix/obj/moc_playlistmodel.cpp unix/obj/moc_playlistsettings.cpp unix/obj/moc_playlistview.cpp unix/obj/moc_progressbar.cpp unix/obj/moc_stardelegate.cpp unix/obj/moc_stareditor.cpp unix/obj/moc_tageditor.cpp
unix/obj/moc_aboutdialog.cpp: ui_aboutdialog.h \
		aboutdialog.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) aboutdialog.h -o unix/obj/moc_aboutdialog.cpp

unix/obj/moc_collectionview.cpp: ui_collectionview.h \
		collectionview.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) collectionview.h -o unix/obj/moc_collectionview.cpp

unix/obj/moc_cuberok.cpp: ui_cuberok.h \
		progressbar.h \
		collectionview.h \
		ui_collectionview.h \
		playlistcontainer.h \
		playlistview.h \
		playlistmodel.h \
		player.h \
		main.h \
		cuberok.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) cuberok.h -o unix/obj/moc_cuberok.cpp

unix/obj/moc_indicator.cpp: indicator.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) indicator.h -o unix/obj/moc_indicator.cpp

unix/obj/moc_lookandfeel.cpp: ui_lookandfeel.h \
		lookandfeel.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) lookandfeel.h -o unix/obj/moc_lookandfeel.cpp

unix/obj/moc_player.cpp: main.h \
		player.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) player.h -o unix/obj/moc_player.cpp

unix/obj/moc_playlistcontainer.cpp: playlistview.h \
		playlistmodel.h \
		player.h \
		main.h \
		playlistcontainer.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) playlistcontainer.h -o unix/obj/moc_playlistcontainer.cpp

unix/obj/moc_playlistmodel.cpp: playlistmodel.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) playlistmodel.h -o unix/obj/moc_playlistmodel.cpp

unix/obj/moc_playlistsettings.cpp: playlistmodel.h \
		playlistsettings.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) playlistsettings.h -o unix/obj/moc_playlistsettings.cpp

unix/obj/moc_playlistview.cpp: playlistmodel.h \
		player.h \
		main.h \
		playlistview.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) playlistview.h -o unix/obj/moc_playlistview.cpp

unix/obj/moc_progressbar.cpp: progressbar.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) progressbar.h -o unix/obj/moc_progressbar.cpp

unix/obj/moc_stardelegate.cpp: stardelegate.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) stardelegate.h -o unix/obj/moc_stardelegate.cpp

unix/obj/moc_stareditor.cpp: starrating.h \
		stareditor.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) stareditor.h -o unix/obj/moc_stareditor.cpp

unix/obj/moc_tageditor.cpp: ui_tageditor.h \
		tageditor.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) tageditor.h -o unix/obj/moc_tageditor.cpp

compiler_rcc_make_all: unix/obj/qrc_resource.cpp
compiler_rcc_clean:
	-$(DEL_FILE) unix/obj/qrc_resource.cpp
unix/obj/qrc_resource.cpp: resource.qrc \
		images/gnome-audio.png \
		images/star2s.png \
		images/rating2.png \
		images/rating5.png \
		images/gnome-fs-executable.png \
		images/rating3.png \
		images/rating1.png \
		images/emblem-distinguished.png \
		images/stock_person.png \
		images/gnome-dev-cdrom-audio.png \
		images/closetab.png \
		images/addtab.png \
		images/rating4.png \
		images/gnome-cdplayer-icon.png \
		images/emblem-noread.png \
		images/s_check_off.png \
		images/stock_notes.png
	/usr/lib/qt4/bin/rcc -name resource resource.qrc -o unix/obj/qrc_resource.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_aboutdialog.h ui_collectionview.h ui_cuberok.h ui_lookandfeel.h ui_tageditor.h
compiler_uic_clean:
	-$(DEL_FILE) ui_aboutdialog.h ui_collectionview.h ui_cuberok.h ui_lookandfeel.h ui_tageditor.h
ui_aboutdialog.h: aboutdialog.ui
	/usr/lib/qt4/bin/uic aboutdialog.ui -o ui_aboutdialog.h

ui_collectionview.h: collectionview.ui
	/usr/lib/qt4/bin/uic collectionview.ui -o ui_collectionview.h

ui_cuberok.h: cuberok.ui \
		playlistcontainer.h \
		collectionview.h \
		playlistview.h \
		playlistmodel.h \
		player.h \
		main.h \
		ui_collectionview.h
	/usr/lib/qt4/bin/uic cuberok.ui -o ui_cuberok.h

ui_lookandfeel.h: lookandfeel.ui
	/usr/lib/qt4/bin/uic lookandfeel.ui -o ui_lookandfeel.h

ui_tageditor.h: tageditor.ui
	/usr/lib/qt4/bin/uic tageditor.ui -o ui_tageditor.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

unix/obj/aboutdialog.o: aboutdialog.cpp aboutdialog.h \
		ui_aboutdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/aboutdialog.o aboutdialog.cpp

unix/obj/collectionview.o: collectionview.cpp collectionview.h \
		ui_collectionview.h \
		database.h \
		tagger.h \
		indicator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/collectionview.o collectionview.cpp

unix/obj/cuberok.o: cuberok.cpp cuberok.h \
		ui_cuberok.h \
		progressbar.h \
		collectionview.h \
		ui_collectionview.h \
		playlistcontainer.h \
		playlistview.h \
		playlistmodel.h \
		player.h \
		main.h \
		aboutdialog.h \
		ui_aboutdialog.h \
		lookandfeel.h \
		ui_lookandfeel.h \
		tagger.h \
		playlistsettings.h \
		indicator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/cuberok.o cuberok.cpp

unix/obj/database.o: database.cpp database.h \
		main.h \
		tagger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/database.o database.cpp

unix/obj/indicator.o: indicator.cpp indicator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/indicator.o indicator.cpp

unix/obj/lookandfeel.o: lookandfeel.cpp lookandfeel.h \
		ui_lookandfeel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/lookandfeel.o lookandfeel.cpp

unix/obj/main.o: main.cpp cuberok.h \
		ui_cuberok.h \
		progressbar.h \
		collectionview.h \
		ui_collectionview.h \
		playlistcontainer.h \
		playlistview.h \
		playlistmodel.h \
		player.h \
		main.h \
		database.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/main.o main.cpp

unix/obj/player.o: player.cpp player.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/player.o player.cpp

unix/obj/playlistcontainer.o: playlistcontainer.cpp playlistcontainer.h \
		playlistview.h \
		playlistmodel.h \
		player.h \
		main.h \
		playlistsettings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/playlistcontainer.o playlistcontainer.cpp

unix/obj/playlistmodel.o: playlistmodel.cpp playlistmodel.h \
		main.h \
		database.h \
		tagger.h \
		starrating.h \
		indicator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/playlistmodel.o playlistmodel.cpp

unix/obj/playlistsettings.o: playlistsettings.cpp playlistsettings.h \
		playlistmodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/playlistsettings.o playlistsettings.cpp

unix/obj/playlistview.o: playlistview.cpp playlistview.h \
		playlistmodel.h \
		player.h \
		main.h \
		tageditor.h \
		ui_tageditor.h \
		tagger.h \
		database.h \
		stardelegate.h \
		starrating.h \
		playlistsettings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/playlistview.o playlistview.cpp

unix/obj/progressbar.o: progressbar.cpp progressbar.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/progressbar.o progressbar.cpp

unix/obj/stardelegate.o: stardelegate.cpp stardelegate.h \
		stareditor.h \
		starrating.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/stardelegate.o stardelegate.cpp

unix/obj/stareditor.o: stareditor.cpp stareditor.h \
		starrating.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/stareditor.o stareditor.cpp

unix/obj/starrating.o: starrating.cpp starrating.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/starrating.o starrating.cpp

unix/obj/tageditor.o: tageditor.cpp tageditor.h \
		ui_tageditor.h \
		main.h \
		tagger.h \
		database.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/tageditor.o tageditor.cpp

unix/obj/tagger.o: tagger.cpp tagger.h \
		main.h \
		database.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/tagger.o tagger.cpp

unix/obj/moc_aboutdialog.o: unix/obj/moc_aboutdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_aboutdialog.o unix/obj/moc_aboutdialog.cpp

unix/obj/moc_collectionview.o: unix/obj/moc_collectionview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_collectionview.o unix/obj/moc_collectionview.cpp

unix/obj/moc_cuberok.o: unix/obj/moc_cuberok.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_cuberok.o unix/obj/moc_cuberok.cpp

unix/obj/moc_indicator.o: unix/obj/moc_indicator.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_indicator.o unix/obj/moc_indicator.cpp

unix/obj/moc_lookandfeel.o: unix/obj/moc_lookandfeel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_lookandfeel.o unix/obj/moc_lookandfeel.cpp

unix/obj/moc_player.o: unix/obj/moc_player.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_player.o unix/obj/moc_player.cpp

unix/obj/moc_playlistcontainer.o: unix/obj/moc_playlistcontainer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_playlistcontainer.o unix/obj/moc_playlistcontainer.cpp

unix/obj/moc_playlistmodel.o: unix/obj/moc_playlistmodel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_playlistmodel.o unix/obj/moc_playlistmodel.cpp

unix/obj/moc_playlistsettings.o: unix/obj/moc_playlistsettings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_playlistsettings.o unix/obj/moc_playlistsettings.cpp

unix/obj/moc_playlistview.o: unix/obj/moc_playlistview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_playlistview.o unix/obj/moc_playlistview.cpp

unix/obj/moc_progressbar.o: unix/obj/moc_progressbar.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_progressbar.o unix/obj/moc_progressbar.cpp

unix/obj/moc_stardelegate.o: unix/obj/moc_stardelegate.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_stardelegate.o unix/obj/moc_stardelegate.cpp

unix/obj/moc_stareditor.o: unix/obj/moc_stareditor.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_stareditor.o unix/obj/moc_stareditor.cpp

unix/obj/moc_tageditor.o: unix/obj/moc_tageditor.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/moc_tageditor.o unix/obj/moc_tageditor.cpp

unix/obj/qrc_resource.o: unix/obj/qrc_resource.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o unix/obj/qrc_resource.o unix/obj/qrc_resource.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
