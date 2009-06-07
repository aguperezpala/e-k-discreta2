CC = gcc
CFLAGS = -g -Wall -Wextra -Wdeclaration-after-statement -Wbad-function-cast \
	-Wcast-qual -Wstrict-prototypes -Wmissing-declarations \
	-Wmissing-prototypes -Werror -D_DEBUG
TARGET = main_test
SOURCES = $(shell echo *.c)
OBJECTS = $(SOURCES:%.c=%.o) ../../node_stack.o ../../edge_list.o ../../edge.o ../../greedy.o ../../network.o ../../first_coloring.o ../../quad_list.o ../../print_stack.o
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

-include .depend

.depend: $(SOURCES)
	$(CC) -MM $(SOURCES) > .depend

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJECTS) .depend *~
