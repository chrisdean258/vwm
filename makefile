CC = gcc

LIBS = -lX11
FLAGS = -Wall -Wextra

TARGETS = vwm

SOURCES = vwm.c xevents.c
OBJECTS = $(SOURCES:.c=.o)


all: $(TARGETS)

vwm: $(OBJECTS)
	$(CC) -o $@ $^ $(FLAGS) $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $^ $(FLAGS) $(LIBS)


	
