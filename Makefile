BDIR = ./build
BINARY = clicker

OBJS = $(patsubst src/%.c, $(BDIR)/%.o, $(wildcard src/*.c))

ifeq ($(OS), Windows_NT)
  OSFLAGS =
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
   	OSFLAGS =
  endif
  ifeq ($(UNAME_S), Darwin)
   	OSFLAGS = -framework ApplicationServices
  endif
endif

IDIR = ./include
LIBS = -lm
OPT = -O1
VER = c17
CFLAGS = -Wall -Wextra -std=$(VER) $(OPT) -I$(IDIR)

all: $(BDIR) $(BINARY)

$(BINARY): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(BINARY) $(LIBS) $(OSFLAGS)

$(BDIR)/%.o: src/%.c
	cc $(CFLAGS) -c $< -o $@

$(BDIR):
	mkdir -p $(BDIR)


.PHONY: clean

clean:
	rm -rf build/
	rm $(BINARY)
