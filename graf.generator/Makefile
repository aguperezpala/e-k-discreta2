CC = gcc
CFLAGS = -g -Wall -Wextra -Wdeclaration-after-statement -Wbad-function-cast \
	-Wcast-qual -Wstrict-prototypes -Wmissing-declarations \
	-Wmissing-prototypes -Werror -D__DEBUG -I/usr/include/glib-2.0 \
	-I/usr/lib/glib-2.0/include/ 
# ¡¡¡¡¡¡¡¡¡¡ ELIMINAR EL -D__DEBUG !!!!!!!!!!!!!
# Analizar qué banderas dejar


LIBS = -lglib-2.0 -lm
TARGET = grafgen
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
