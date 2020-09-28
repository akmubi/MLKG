CC := clang
CFLAGS := -c -Wall -Wno-deprecated-declarations

.PHONY: all run clean

FILENAME := main
BUILDPATH := build

ifeq ($(OS), Windows_NT)
FILENAME := $(BUILDPATH)\$(FILENAME).exe
RUNFILE := $(FILENAME)
else
FILENAME := $(BUILDPATH)/$(FILENAME)
RUNFILE := ./$(FILENAME)
CLIBS := -lm
endif

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)

all: $(OBJECTS)
	$(CC) $^ -o  $(FILENAME) $(CLIBS)

run:
	@$(RUNFILE)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

ifeq ($(OS), Windows_NT)
clean:
	del /q /s *.o
else
clean:
	rm -f *.o
endif