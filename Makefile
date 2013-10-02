

CC ?= gcc

ifdef WITHOUT_READLINE
	READLINE_CFLAGS =
	READLINE_LIBS =
else
	READLINE_CFLAGS = -DUSE_READLINE
	READLINE_LIBS = -lreadline
endif

CFLAGS = -O2 -Wall -Wno-char-subscripts $(READLINE_CFLAGS) 
LDFLAGS = -s

INCLUDES = -I. -Iui 
LIBS = $(READLINE_LIBS) $(OS_LIBS)

BINARY = input-module
all: $(BINARY)

.SUFFIXES: .c .o

OBJ=\
    ui/reader.o \
    ui/input.o \
    ui/input_console.o \
    ui/main.o

$(BINARY): $(OBJ)
	@$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

.c.o:
	@$(CC) $(CFLAGS) -o $@ -c $*.c


clean:
	@rm -f $(OBJ)
	@rm -f $(BINARY)
