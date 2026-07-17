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
CFLAGS = -Wall -Wextra -std=$(VER) $(OPT) -I$(IDIR) -I$(BDIR) -MMD

# GResource setup
GLIB_COMPILE_RESOURCES = glib-compile-resources
RESOURCE_XML = resources.gresource.xml
RESOURCE_C = $(BDIR)/resources.c
RESOURCE_H = $(BDIR)/resources.h
RESOURCE_O = $(BDIR)/resources.o

# files referenced inside the .gresource.xml (e.g. the png), so
# rebuild resources.c/.h whenever the actual asset changes too.
RESOURCE_DEPS = $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=. --generate-dependencies $(RESOURCE_XML))

all: $(BDIR) $(BINARY)

$(BINARY): $(OBJS) $(RESOURCE_O)
	@cc $(CFLAGS) $(GTKFLAGS) $(OBJS) $(RESOURCE_O) -o $(BINARY) $(LIBS) $(GTKLIBS) $(OSFLAGS)

# every normal object depends on resources.h existing first,
# since source includes "resources.h".
$(OBJS): $(RESOURCE_H)

$(BDIR)/%.o: src/%.c
	@cc $(CFLAGS) $(GTKFLAGS) -c $< -o $@

$(RESOURCE_C): $(RESOURCE_XML) $(RESOURCE_DEPS) | $(BDIR)
	$(GLIB_COMPILE_RESOURCES) --sourcedir=. --generate-source --target=$@ $(RESOURCE_XML)

$(RESOURCE_H): $(RESOURCE_XML) $(RESOURCE_DEPS) | $(BDIR)
	$(GLIB_COMPILE_RESOURCES) --sourcedir=. --generate-header --target=$@ $(RESOURCE_XML)

$(RESOURCE_O): $(RESOURCE_C) $(RESOURCE_H)
	@cc $(CFLAGS) $(GTKFLAGS) -c $(RESOURCE_C) -o $@

$(BDIR):
	mkdir -p $(BDIR)


.PHONY: clean all

clean:
	rm -rf build/
	rm -f $(BINARY)

-include $(patsubst $(BDIR)/%.o, $(BDIR)/%.d, $(OBJS))