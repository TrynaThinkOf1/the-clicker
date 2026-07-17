BDIR = ./build
BINARY = clicker

OBJS = $(patsubst src/%.c, $(BDIR)/%.o, $(wildcard src/*.c))

ifeq ($(OS), Windows_NT)
  OSFLAGS =
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
   	OSFLAGS = -lm
  endif
  ifeq ($(UNAME_S), Darwin)
   	OSFLAGS = -framework ApplicationServices
  endif
endif


GTKFLAGS = $(shell pkg-config --cflags gtk4) -Wno-incompatible-pointer-types
GTKLIBS = $(shell pkg-config --libs gtk4)

IDIR = ./include
LIBS = -lpthread
OPT = -O1
VER = c17
CFLAGS = -Wall -Wextra -std=$(VER) $(OPT) -I$(IDIR) -MMD

all: $(BDIR) $(BINARY)

$(BINARY): $(OBJS)
	@cc $(CFLAGS) $(GTKFLAGS) $(OBJS) -o $(BINARY) $(LIBS) $(GTKLIBS) $(OSFLAGS)

$(BDIR)/%.o: src/%.c
	@cc $(CFLAGS) $(GTKFLAGS) -c $< -o $@

$(BDIR):
	mkdir -p $(BDIR)


.PHONY: clean

clean:
	rm -rf build/
	rm $(BINARY)

-include $(patsubst $(BDIR)/%.o, $(BDIR)/%.d, $(OBJS))