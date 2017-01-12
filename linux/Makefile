CC=g++
CFLAGS= -c -g -std=c++11 -MMD -MP

INCLUDEDIR = ../include
SRC=AsyncSystem.cpp Behavior.cpp BehaviorManager.cpp Component.cpp ComponentType.cpp Context.cpp Entity.cpp EntityManager.cpp State.cpp SyncSystem.cpp System.cpp SystemManager.cpp SystemType.cpp Thread.cpp Transition.cpp World.cpp
OBJ=$(SOURCES:.cpp=.o)
LIBFILE=entitysystem
LIBDIR = ./lib
SRCDIR = ../src
lib: createdir $(LIBFILE)

createdir:
	mkdir -p $(LIBDIR)

$(LIBFILE): $(SRC)
	libtool -static -o $(LIBDIR)/lib$(LIBFILE).a $(LIBDIR)/*.o

AsyncSystem.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/AsyncSystem.o.d" -o $(LIBDIR)/AsyncSystem.o $(SRCDIR)/AsyncSystem.cpp
Behavior.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Behavior.o.d" -o $(LIBDIR)/Behavior.o $(SRCDIR)/Behavior.cpp
BehaviorManager.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/BehaviorManager.o.d" -o $(LIBDIR)/BehaviorManager.o $(SRCDIR)/BehaviorManager.cpp
Component.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Component.o.d" -o $(LIBDIR)/Component.o $(SRCDIR)/Component.cpp
ComponentType.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/ComponentType.o.d" -o $(LIBDIR)/ComponentType.o $(SRCDIR)/ComponentType.cpp
Context.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Context.o.d" -o $(LIBDIR)/Context.o $(SRCDIR)/Context.cpp
Entity.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Entity.o.d" -o $(LIBDIR)/Entity.o $(SRCDIR)/Entity.cpp
EntityManager.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/EntityManager.o.d" -o $(LIBDIR)/EntityManager.o $(SRCDIR)/EntityManager.cpp
State.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/State.o.d" -o $(LIBDIR)/EntityManager.o $(SRCDIR)/EntityManager.cpp
SyncSystem.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/SyncSystem.o.d" -o $(LIBDIR)/SyncSystem.o $(SRCDIR)/SyncSystem.cpp
System.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/System.o.d" -o $(LIBDIR)/System.o $(SRCDIR)/System.cpp
SystemManager.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/SystemManager.o.d" -o $(LIBDIR)/SystemManager.o $(SRCDIR)/SystemManager.cpp
SystemType.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/SystemType.o.d" -o $(LIBDIR)/SystemType.o $(SRCDIR)/SystemType.cpp
Thread.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Thread.o.d" -o $(LIBDIR)/Thread.o $(SRCDIR)/Thread.cpp
Transition.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/Transition.o.d" -o $(LIBDIR)/Transition.o $(SRCDIR)/Transition.cpp
World.cpp:
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -MF "$(LIBDIR)/World.o.d" -o $(LIBDIR)/World.o $(SRCDIR)/World.cpp

clean:
	rm -fr $(LIBDIR)

