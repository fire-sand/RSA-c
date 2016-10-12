TARGET = bignum
LIBS = -lm
CC = clang
CFLAGS = -g -Weverything

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)



# CC=clang
# CFLAGS=-g -Weverything
# TARGET=bignum

# all: $(TARGET)

# $(TARGET): $(TARGET).c
# 	  $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# clean:
# 	  $(RM) $(TARGET)
