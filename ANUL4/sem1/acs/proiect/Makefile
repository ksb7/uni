CC = gcc
CXX = g++
CFLAGS = -Wall -pthread -fPIC

# ===== Qt 5 paths (default on Ubuntu/Debian) =====
QT_INCLUDE = /usr/include/x86_64-linux-gnu/qt5
QT_INCLUDE_WIDGETS = /usr/include/x86_64-linux-gnu/qt5/QtWidgets
QT_INCLUDE_GUI = /usr/include/x86_64-linux-gnu/qt5/QtGui
QT_INCLUDE_CORE = /usr/include/x86_64-linux-gnu/qt5/QtCore
QT_LIBS = -L/usr/lib/x86_64-linux-gnu -lQt5Widgets -lQt5Gui -lQt5Core

# ===== Targets =====
all: Server Client

Server: Server.c
	$(CC) $(CFLAGS) Server.c -o Server

Client: ClientNetwork.c ClientGUI.cpp
	$(CXX) $(CFLAGS) \
	-I$(QT_INCLUDE) -I$(QT_INCLUDE_WIDGETS) -I$(QT_INCLUDE_GUI) -I$(QT_INCLUDE_CORE) \
	ClientNetwork.c ClientGUI.cpp -o Client $(QT_LIBS)

clean:
	rm -f Server Client
