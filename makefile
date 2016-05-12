CC = gcc

SOURCEDIR = /src
BUILDDIR = build
FLAGS = -pthread -c -Wall -Wstrict-prototypes 

all: dir $(BUILDER)/$(EXECUTABLE)

dir:
	mkdir -p &(BUILDDIR)

pessoa:
	gcc pessoa.c