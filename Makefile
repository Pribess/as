CC = cc
AR = ar

CFLAGS = -Wall
LDFLAGS =
ARFLAGS = rcus

TARGET = iasm
LIB = libiasm.a

INCLUDEDIR = -I./include -I./
INCLUDEDIR += -I./deps/ics/include
SOURCES = $(shell find ./src -name "*.c")
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all
all : $(TARGET) $(LIB)


$(TARGET) : $(OBJECTS)
	$(CC) $(notdir $^) $(LDFLAGS) -o $@

$(LIB) : $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(notdir $^)


%.o : %.c
	$(CC) $(INCLUDEDIR) -c $(CFLAGS) $< -o $(notdir $@)


.PHONY: clean

clean:
	rm -f $(TARGET) $(LIB) *.o