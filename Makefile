CC := clang
CFLAGS := -c -Wall -Wno-deprecated-declarations

.PHONY: all run clean

FILENAME := main

ifeq ($(OS), Windows_NT)
FILENAME := $(FILENAME).exe
RUNFILE := $(FILENAME)
else
RUNFILE := ./$(FILENAME)
endif

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)

all: $(OBJECTS)
	$(CC) $^ -o  $(FILENAME)

run:
	$(RUNFILE)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

ifeq ($(OS), Windows_NT)
clean:
	del /q /s *.o
else
clean:
	rm -f *.o
endif