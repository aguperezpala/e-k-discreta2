CC = gcc
CFLAGS = -g -Wall -Wextra -Wdeclaration-after-statement -Wbad-function-cast \
	-Wcast-qual -Wstrict-prototypes -Wmissing-declarations \
	-Wmissing-prototypes -Werror -D_DDEBUG \
	-I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include/
LIBS = -lglib-2.0
TARGET = host
SOURCES = $(shell echo *.c)
OBJECTS = $(SOURCES:%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

utest: $(OBJECTS) data_tests.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) -lcheck

-include .depend

.depend: $(SOURCES)
	$(CC) -MM $(SOURCES) > .depend

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJECTS) .depend *~
