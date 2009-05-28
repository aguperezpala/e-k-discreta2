CC = gcc
CFLAGS = -g -Wall -Wextra -Wdeclaration-after-statement -Wbad-function-cast \
	-Wcast-qual -Wstrict-prototypes -Wmissing-declarations \
	-Wmissing-prototypes -Werror -D__DEBUG
# ¡¡¡¡¡¡¡¡¡¡ ELIMINAR EL -D__DEBUG !!!!!!!!!!!!!
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