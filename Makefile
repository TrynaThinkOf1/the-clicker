BDIR = ./build
BINARY = clicker

OBJS = $(patsubst src/%.c, $(BDIR)/%.o, $(wildcard src/*.c))
OBJS += $(BDIR)/resources.o

UIDIR = include/graphics/ui
UIFILES = $(wildcard $(UIDIR)/*.ui)
STYDIR = include/graphics/styles
CSSFILES = $(wildcard $(STYDIR)/*.css)

ifeq ($(OS), Windows_NT)
  OSFLAGS =
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
   	OSFLAGS = -lm
  endif
  ifeq ($(UNAME_S), Darwin)
   	OSFLAGS = -framework ApplicationServices -framework Foundation -framework UserNotifications
  endif
endif


GTKFLAGS = $(shell pkg-config --cflags gtk4) -Wno-incompatible-pointer-types
GTKLIBS = $(shell pkg-config --libs gtk4)

IDIR = ./include
LIBS = -lpthread
VER = c17
CFLAGS = -Wall -Wextra -std=$(VER) -I$(IDIR) -MMD

ifeq ($(debug),1)
  CFLAGS += -g -O0 -DDEBUG_TESTS
else
	CFLAGS += -O1
endif


all: $(BDIR) $(BINARY)

compile_commands.json:
	compiledb make -n

$(BINARY): $(OBJS)
	@cc $(CFLAGS) $(GTKFLAGS) $(OBJS) -o $(BINARY) $(LIBS) $(GTKLIBS) $(OSFLAGS)

$(BDIR)/%.o: src/%.c
	@cc $(CFLAGS) $(GTKFLAGS) -c $< -o $@
	
$(BDIR)/resources.c: gresource.xml $(UIFILES) $(CSSFILES) | $(BDIR)
	glib-compile-resources gresource.xml --target=$@ --generate-source --sourcedir=include

$(BDIR)/resources.o: $(BDIR)/resources.c
	@cc $(CFLAGS) $(GTKFLAGS) -c $< -o $@

$(BDIR):
	mkdir -p $(BDIR)


.PHONY: clean

clean:
	rm -rf build/
	rm $(BINARY)

-include $(patsubst $(BDIR)/%.o, $(BDIR)/%.d, $(OBJS))