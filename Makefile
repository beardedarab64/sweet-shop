CC = g++
CFLAGS = -Wall -g -c $(shell pkg-config --cflags gtkmm-3.0)
LDFLAGS = $(shell pkg-config --libs gtkmm-3.0) -lsqlite3 

RM = rm -rf

SOURCES = sweet-shop.cpp WindowMain.cpp TreeViewGoods.cpp GoodsColumns.cpp \
          database.cpp TreeViewPurchases.cpp PurchasesColumns.cpp \
          WindowInform.cpp

OBJECTS = sweet-shop.o WindowMain.o TreeViewGoods.o GoodsColumns.o \
          database.o TreeViewPurchases.o PurchasesColumns.o \
          WindowInform.o

EXECUTABLE = sweet-shop

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

sweet-shop.o: sweet-shop.cpp sweet-shop.h WindowMain.h
	$(CC) $(CFLAGS) sweet-shop.cpp

WindowMain.o: WindowMain.cpp WindowMain.h TreeViewGoods.h TreeViewPurchases.h \
              sweet-shop.h
	$(CC) $(CFLAGS) WindowMain.cpp

TreeViewGoods.o: TreeViewGoods.cpp TreeViewGoods.h GoodsColumns.h database.h \
                 sweet-shop.h
	$(CC) $(CFLAGS) TreeViewGoods.cpp

GoodsColumns.o: GoodsColumns.cpp GoodsColumns.h
	$(CC) $(CFLAGS) GoodsColumns.cpp

database.o: database.cpp database.h sweet-shop.h
	$(CC) $(CFLAGS) database.cpp

TreeViewPurchases.o: TreeViewPurchases.cpp TreeViewPurchases.h \
                     PurchasesColumns.h WindowInform.h
	$(CC) $(CFLAGS) TreeViewPurchases.cpp

PurchasesColumns.o: PurchasesColumns.cpp PurchasesColumns.h
	$(CC) $(CFLAGS) PurchasesColumns.cpp

WindowInform.o: WindowInform.cpp WindowInform.h database.h sweet-shop.h
	$(CC) $(CFLAGS) WindowInform.cpp

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
