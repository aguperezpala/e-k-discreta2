TARGET=runner
CC=gcc
CFLAGS+= -I.. -ansi -Wall -Wextra -Wdeclaration-after-statement -Wbad-function-cast -Wcast-qual -Wstrict-prototypes -Wmissing-declarations -Wmissing-prototypes -Wno-unused-parameter -pedantic `pkg-config --cflags glib-2.0` -Werror -D_DEBUG
LDFLAGS=-lcheck `pkg-config --libs glib-2.0`-D_DEBUG
SOURCES=$(shell echo *.c)
OBJECTS=$(SOURCES:.c=.o)
# Aquí no usamos un wildcard para no traer el main
TESTED_OBJECTS= ../node_stack.o ../edge_list.o ../edge.o ../greedy.o  ../network.o  ../quad_list.o ../print_stack.o ../first_coloring.o

all: $(TARGET)

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS) $(TESTED_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) 

clean:
	rm -f $(TARGET) $(OBJECTS) test.log .depend *~

.depend: *.[ch]
	$(CC) $(CFLAGS) -MM $(SOURCES) >.depend

-include .depend

.PHONY: clean all
