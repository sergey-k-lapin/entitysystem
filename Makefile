CC=g++
CFLAGS= -c -g -std=c++11 -MMD -MP

INCLUDEDIR = ./include
SRC=Component.cpp ComponentType.cpp Entity.cpp EntityManager.cpp Manager.cpp System.cpp SystemManager.cpp SystemType.cpp Thread.cpp World.cpp
OBJ=$(SOURCES:.cpp=.o)
LIBFILE=entitysystem
LIBDIR = ./lib
SRCDIR = ./src
lib: createdir $(LIBFILE)

createdir:
	mkdir -p $(LIBDIR)

$(LIBFILE): $(SRC)
	libtool -static -o $(LIBDIR)/lib$(LIBFILE).a $(LIBDIR)/*.o
	g++ -c -std=c++11 -I $(INCLUDEDIR) -o ./test/main.o ./test/main.cpp
	g++ -o ./test/main  ./test/main.o -L$(LIBDIR) -l$(LIBFILE)

Component.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Component.o.d" -o $(LIBDIR)/Component.o $(SRCDIR)/Component.cpp
ComponentType.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/ComponentType.o.d" -o $(LIBDIR)/ComponentType.o $(SRCDIR)/ComponentType.cpp
Entity.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Entity.o.d" -o $(LIBDIR)/Entity.o $(SRCDIR)/Entity.cpp
EntityManager.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/EntityManager.o.d" -o $(LIBDIR)/EntityManager.o $(SRCDIR)/EntityManager.cpp
Manager.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Manager.o.d" -o $(LIBDIR)/Manager.o $(SRCDIR)/Manager.cpp
System.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/System.o.d" -o $(LIBDIR)/System.o $(SRCDIR)/System.cpp
SystemManager.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/SystemManager.o.d" -o $(LIBDIR)/SystemManager.o $(SRCDIR)/SystemManager.cpp
SystemType.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/SystemType.o.d" -o $(LIBDIR)/SystemType.o $(SRCDIR)/SystemType.cpp
Thread.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Thread.o.d" -o $(LIBDIR)/Thread.o $(SRCDIR)/Thread.cpp
World.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/World.o.d" -o $(LIBDIR)/World.o $(SRCDIR)/World.cpp

clean:
	rm -fr $(LIBDIR)
	rm -f ./test/*.o
	rm -f ./test/main
