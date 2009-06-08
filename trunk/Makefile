CC = gcc
CFLAGS = -g -Wall -Wextra -Wdeclaration-after-statement -Wbad-function-cast \
	-Wcast-qual -Wstrict-prototypes -Wmissing-declarations \
	-Wmissing-prototypes -Werror -std=iso9899:1999
# ¡¡¡¡¡¡¡¡¡¡ ELIMINAR EL -D__DEBUG !!!!!!!!!!!!!
# Analizar qué banderas dejar
TARGET = EK!
SOURCES = $(shell echo *.c)
OBJECTS = $(SOURCES:%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

-include .depend

.depend: $(SOURCES)
	$(CC) -MM $(SOURCES) > .depend

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJECTS) .depend *~
#	rm -f *.h *.c
