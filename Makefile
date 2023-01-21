CC = cc

CFLAGS = -Wall
LDFLAGS =

TARGET = as

SOURCES = $(shell find ./src -name "*.c")
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all
all : $(TARGET) $(LIB)


$(TARGET) : $(OBJECTS)
	$(CC) $(notdir $^) $(LDFLAGS) -o $@

%.o : %.c
	$(CC) $(INCLUDEDIR) -c $(CFLAGS) $< -o $(notdir $@)


.PHONY: clean

clean:
	rm -f $(TARGET) *.o

# compilation database generator for Jetbrains Fleet

.PHONY: db

db:
	compiledb -n make

cleandb:
	rm -f compile_commands.json
