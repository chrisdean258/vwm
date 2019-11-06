CC = gcc

LIBS = -lX11
FLAGS = -Wall 

TARGETS = vwm

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)


all: $(TARGETS)

vwm: $(OBJECTS)
	$(CC) -o $@ $^ $(FLAGS) $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $^ $(FLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o
	
