CC = g++
RM = rm -rf
CFLAGS = -Wall -g -c $(shell pkg-config --cflags gtkmm-3.0)
LDFLAGS = $(shell pkg-config --libs gtkmm-3.0)

SOURCES = sweet-shop.cpp WindowMain.cpp TreeViewGoods.cpp GoodsColumns.cpp \
          database.cpp
OBJECTS = sweet-shop.o WindowMain.o TreeViewGoods.o GoodsColumns.o \
          database.o

EXECUTABLE = sweet-shop

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

sweet-shop.o: sweet-shop.cpp WindowMain.h
	$(CC) $(CFLAGS) sweet-shop.cpp

WindowMain.o: WindowMain.cpp WindowMain.h TreeViewGoods.h
	$(CC) $(CFLAGS) WindowMain.cpp

TreeViewGoods.o: TreeViewGoods.cpp TreeViewGoods.h GoodsColumns.h database.h
	$(CC) $(CFLAGS) TreeViewGoods.cpp

GoodsColumns.o: GoodsColumns.cpp GoodsColumns.h
	$(CC) $(CFLAGS) GoodsColumns.cpp

database.o: database.cpp database.h
	$(CC) $(CFLAGS) database.cpp

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
