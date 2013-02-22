CC = g++
RM = rm -rf
CFLAGS = -Wall -g -c $(shell pkg-config --cflags gtkmm-3.0)
LDFLAGS = $(shell pkg-config --libs gtkmm-3.0)

SOURCES = sweet-shop.cpp WindowMain.cpp TreeViewGoods.cpp
OBJECTS = sweet-shop.o WindowMain.o TreeViewGoods.o

EXECUTABLE = sweet-shop

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

sweet-shop.o: sweet-shop.cpp WindowMain.h
	$(CC) $(CFLAGS) sweet-shop.cpp

WindowMain.o: WindowMain.cpp WindowMain.h TreeViewGoods.h
	$(CC) $(CFLAGS) WindowMain.cpp

TreeViewGoods.o: TreeViewGoods.cpp TreeViewGoods.h
	$(CC) $(CFLAGS) TreeViewGoods.cpp

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
