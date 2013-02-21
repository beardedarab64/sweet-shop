CC = g++
RM = rm -rf
CFLAGS = -Wall -g -c $(shell pkg-config --cflags gtkmm-3.0)
LDFLAGS = $(shell pkg-config --libs gtkmm-3.0)

SOURCES = sweet-shop.cpp
OBJECTS = sweet-shop.o

EXECUTABLE = sweet-shop

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

sweet-shop.o: sweet-shop.cpp
	$(CC) $(CFLAGS) sweet-shop.cpp

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
