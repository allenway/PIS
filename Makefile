#############################################################################
# Makefile for building: PIS
# Generated by qmake (2.01a) (Qt 4.5.0) on: Wed Dec 23 15:05:03 2015
# Project:  PIS.pro
# Template: app
# Command: /opt/rha/qt-4.5/__install/arm/bin/qmake -spec ../../../rha/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++ -unix -o Makefile PIS.pro
#############################################################################

####### Compiler, tools and options

CC            = arm-linux-gcc
CXX           = arm-linux-g++
DEFINES       = -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../../../rha/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++ -I. -I../../../rha/qt-4.5/__install/arm/include/QtCore -I../../../rha/qt-4.5/__install/arm/include/QtNetwork -I../../../rha/qt-4.5/__install/arm/include/QtGui -I../../../rha/qt-4.5/__install/arm/include/QtXml -I../../../rha/qt-4.5/__install/arm/include/QtSql -I../../../rha/qt-4.5/__install/arm/include -I. -I.
LINK          = arm-linux-g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/opt/rha/qt-4.5/__install/arm/lib
LIBS          = $(SUBLIBS)  -L/opt/rha/qt-4.5/__install/arm//lib -lQtSql -L./tslib-1.4.1/__install/lib -L/opt/rha/qt-4.5/__install/arm//lib -lQtXml -lQtGui -lts -lQtNetwork -lQtCore -lm -lrt -ldl -lpthread
AR            = arm-linux-ar cqs
RANLIB        = 
QMAKE         = /opt/rha/qt-4.5/__install/arm/bin/qmake
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

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		formstationset.cpp \
		formsysstatus.cpp \
		formmenu.cpp \
		formaudio.cpp \
		message.cpp \
		dialogselectannunciator.cpp \
		mplayerprocess.cpp moc_mainwindow.cpp \
		moc_formstationset.cpp \
		moc_formsysstatus.cpp \
		moc_formmenu.cpp \
		moc_formaudio.cpp \
		moc_message.cpp \
		moc_dialogselectannunciator.cpp \
		moc_mplayerprocess.cpp
OBJECTS       = main.o \
		mainwindow.o \
		formstationset.o \
		formsysstatus.o \
		formmenu.o \
		formaudio.o \
		message.o \
		dialogselectannunciator.o \
		mplayerprocess.o \
		moc_mainwindow.o \
		moc_formstationset.o \
		moc_formsysstatus.o \
		moc_formmenu.o \
		moc_formaudio.o \
		moc_message.o \
		moc_dialogselectannunciator.o \
		moc_mplayerprocess.o
DIST          = ../../../rha/qt-4.5/__install/arm/mkspecs/common/g++.conf \
		../../../rha/qt-4.5/__install/arm/mkspecs/common/unix.conf \
		../../../rha/qt-4.5/__install/arm/mkspecs/common/linux.conf \
		../../../rha/qt-4.5/__install/arm/mkspecs/common/qws.conf \
		../../../rha/qt-4.5/__install/arm/mkspecs/qconfig.pri \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/qt_functions.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/qt_config.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/exclusive_builds.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/default_pre.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/release.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/default_post.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/warn_on.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/qt.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/unix/thread.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/moc.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/resources.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/uic.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/yacc.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/lex.prf \
		PIS.pro
QMAKE_TARGET  = PIS
DESTDIR       = 
TARGET        = PIS

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

$(TARGET): ui_mainwindow.h ui_formstationset.h ui_formsysstatus.h ui_formmenu.h ui_formaudio.h ui_dialogselectannunciator.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: PIS.pro  ../../../rha/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++/qmake.conf ../../../rha/qt-4.5/__install/arm/mkspecs/common/g++.conf \
		../../../rha/qt-4.5/__install/arm/mkspecs/common/unix.conf \
		../../../rha/qt-4.5/__install/arm/mkspecs/common/linux.conf \
		../../../rha/qt-4.5/__install/arm/mkspecs/common/qws.conf \
		../../../rha/qt-4.5/__install/arm/mkspecs/qconfig.pri \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/qt_functions.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/qt_config.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/exclusive_builds.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/default_pre.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/release.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/default_post.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/warn_on.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/qt.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/unix/thread.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/moc.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/resources.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/uic.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/yacc.prf \
		../../../rha/qt-4.5/__install/arm/mkspecs/features/lex.prf \
		/opt/rha/qt-4.5/__install/arm/lib/libQtSql.prl \
		/opt/rha/qt-4.5/__install/arm/lib/libQtCore.prl \
		/opt/rha/qt-4.5/__install/arm/lib/libQtXml.prl \
		/opt/rha/qt-4.5/__install/arm/lib/libQtGui.prl \
		/opt/rha/qt-4.5/__install/arm/lib/libQtNetwork.prl
	$(QMAKE) -spec ../../../rha/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++ -unix -o Makefile PIS.pro
../../../rha/qt-4.5/__install/arm/mkspecs/common/g++.conf:
../../../rha/qt-4.5/__install/arm/mkspecs/common/unix.conf:
../../../rha/qt-4.5/__install/arm/mkspecs/common/linux.conf:
../../../rha/qt-4.5/__install/arm/mkspecs/common/qws.conf:
../../../rha/qt-4.5/__install/arm/mkspecs/qconfig.pri:
../../../rha/qt-4.5/__install/arm/mkspecs/features/qt_functions.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/qt_config.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/exclusive_builds.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/default_pre.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/release.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/default_post.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/warn_on.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/qt.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/unix/thread.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/moc.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/resources.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/uic.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/yacc.prf:
../../../rha/qt-4.5/__install/arm/mkspecs/features/lex.prf:
/opt/rha/qt-4.5/__install/arm/lib/libQtSql.prl:
/opt/rha/qt-4.5/__install/arm/lib/libQtCore.prl:
/opt/rha/qt-4.5/__install/arm/lib/libQtXml.prl:
/opt/rha/qt-4.5/__install/arm/lib/libQtGui.prl:
/opt/rha/qt-4.5/__install/arm/lib/libQtNetwork.prl:
qmake:  FORCE
	@$(QMAKE) -spec ../../../rha/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++ -unix -o Makefile PIS.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/PIS1.0.0 || $(MKDIR) .tmp/PIS1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/PIS1.0.0/ && $(COPY_FILE) --parents mainwindow.h formstationset.h formsysstatus.h formmenu.h formaudio.h message.h rha.h dialogselectannunciator.h mplayerprocess.h .tmp/PIS1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp formstationset.cpp formsysstatus.cpp formmenu.cpp formaudio.cpp message.cpp dialogselectannunciator.cpp mplayerprocess.cpp .tmp/PIS1.0.0/ && $(COPY_FILE) --parents mainwindow.ui formstationset.ui formsysstatus.ui formmenu.ui formaudio.ui dialogselectannunciator.ui .tmp/PIS1.0.0/ && (cd `dirname .tmp/PIS1.0.0` && $(TAR) PIS1.0.0.tar PIS1.0.0 && $(COMPRESS) PIS1.0.0.tar) && $(MOVE) `dirname .tmp/PIS1.0.0`/PIS1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/PIS1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_formstationset.cpp moc_formsysstatus.cpp moc_formmenu.cpp moc_formaudio.cpp moc_message.cpp moc_dialogselectannunciator.cpp moc_mplayerprocess.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_formstationset.cpp moc_formsysstatus.cpp moc_formmenu.cpp moc_formaudio.cpp moc_message.cpp moc_dialogselectannunciator.cpp moc_mplayerprocess.cpp
moc_mainwindow.cpp: formmenu.h \
		formstationset.h \
		formsysstatus.h \
		formaudio.h \
		message.h \
		rha.h \
		mainwindow.h
	/opt/rha/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_formstationset.cpp: formstationset.h
	/opt/rha/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) formstationset.h -o moc_formstationset.cpp

moc_formsysstatus.cpp: formsysstatus.h
	/opt/rha/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) formsysstatus.h -o moc_formsysstatus.cpp

moc_formmenu.cpp: formstationset.h \
		formsysstatus.h \
		formaudio.h \
		formmenu.h
	/opt/rha/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) formmenu.h -o moc_formmenu.cpp

moc_formaudio.cpp: formaudio.h
	/opt/rha/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) formaudio.h -o moc_formaudio.cpp

moc_message.cpp: rha.h \
		message.h
	/opt/rha/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) message.h -o moc_message.cpp

moc_dialogselectannunciator.cpp: dialogselectannunciator.h
	/opt/rha/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) dialogselectannunciator.h -o moc_dialogselectannunciator.cpp

moc_mplayerprocess.cpp: message.h \
		rha.h \
		mplayerprocess.h
	/opt/rha/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) mplayerprocess.h -o moc_mplayerprocess.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_formstationset.h ui_formsysstatus.h ui_formmenu.h ui_formaudio.h ui_dialogselectannunciator.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_formstationset.h ui_formsysstatus.h ui_formmenu.h ui_formaudio.h ui_dialogselectannunciator.h
ui_mainwindow.h: mainwindow.ui
	/opt/rha/qt-4.5/__install/arm/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_formstationset.h: formstationset.ui
	/opt/rha/qt-4.5/__install/arm/bin/uic formstationset.ui -o ui_formstationset.h

ui_formsysstatus.h: formsysstatus.ui
	/opt/rha/qt-4.5/__install/arm/bin/uic formsysstatus.ui -o ui_formsysstatus.h

ui_formmenu.h: formmenu.ui
	/opt/rha/qt-4.5/__install/arm/bin/uic formmenu.ui -o ui_formmenu.h

ui_formaudio.h: formaudio.ui
	/opt/rha/qt-4.5/__install/arm/bin/uic formaudio.ui -o ui_formaudio.h

ui_dialogselectannunciator.h: dialogselectannunciator.ui
	/opt/rha/qt-4.5/__install/arm/bin/uic dialogselectannunciator.ui -o ui_dialogselectannunciator.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		formmenu.h \
		formstationset.h \
		formsysstatus.h \
		formaudio.h \
		message.h \
		rha.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		formmenu.h \
		formstationset.h \
		formsysstatus.h \
		formaudio.h \
		message.h \
		rha.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

formstationset.o: formstationset.cpp formstationset.h \
		ui_formstationset.h \
		rha.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formstationset.o formstationset.cpp

formsysstatus.o: formsysstatus.cpp formsysstatus.h \
		ui_formsysstatus.h \
		rha.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formsysstatus.o formsysstatus.cpp

formmenu.o: formmenu.cpp formmenu.h \
		formstationset.h \
		formsysstatus.h \
		formaudio.h \
		ui_formmenu.h \
		rha.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formmenu.o formmenu.cpp

formaudio.o: formaudio.cpp formaudio.h \
		ui_formaudio.h \
		rha.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formaudio.o formaudio.cpp

message.o: message.cpp message.h \
		rha.h \
		dialogselectannunciator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o message.o message.cpp

dialogselectannunciator.o: dialogselectannunciator.cpp dialogselectannunciator.h \
		ui_dialogselectannunciator.h \
		rha.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogselectannunciator.o dialogselectannunciator.cpp

mplayerprocess.o: mplayerprocess.cpp mplayerprocess.h \
		message.h \
		rha.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mplayerprocess.o mplayerprocess.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_formstationset.o: moc_formstationset.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formstationset.o moc_formstationset.cpp

moc_formsysstatus.o: moc_formsysstatus.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formsysstatus.o moc_formsysstatus.cpp

moc_formmenu.o: moc_formmenu.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formmenu.o moc_formmenu.cpp

moc_formaudio.o: moc_formaudio.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formaudio.o moc_formaudio.cpp

moc_message.o: moc_message.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_message.o moc_message.cpp

moc_dialogselectannunciator.o: moc_dialogselectannunciator.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogselectannunciator.o moc_dialogselectannunciator.cpp

moc_mplayerprocess.o: moc_mplayerprocess.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mplayerprocess.o moc_mplayerprocess.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

