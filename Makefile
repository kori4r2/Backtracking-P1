# Italo Tobler Silva		 nUSP - 8551910
CFLAGS = -g -Wall
PROJECT = Backtracking
CC = g++
BINDIR = bin
SRCDIR = src
LIBDIR = lib
LIBS := $(wildcard $(LIBDIR)/*hpp)
SRCS := $(wildcard $(SRCDIR)/*cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%.o, $(SRCS))

all : $(BINDIR) build

build : $(OBJS)
	$(CC) -o $(PROJECT) $(OBJS)

$(BINDIR) :
	mkdir -p bin

$(BINDIR)/%.o : $(SRCDIR)/%.cpp $(LIBS)
	$(CC) -c $< -I $(LIBDIR) $(CFLAGS) -o $@

clean :
	rm -f $(BINDIR)/*.o
#	rm -f *.dif
#	rm -f test*.out
	rm -f $(PROJECT).zip
	rm -f $(PROJECT)
	clear

run : build
	./$(PROJECT)

.zip :
	zip $(PROJECT).zip $(SRCS) $(LIBS) Makefile

#debug : build
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < 1.in > test1.out
#	diff 1.out test1.out > 1.dif
#
#fixdiff :
#	sed -i -e '$a\' *.out
#