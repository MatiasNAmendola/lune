CC=gcc
CFLAGS=-ansi -Wall -g
OUT=lune
SRCDIR=src
OBJDIR=obj
OBJ=$(wildcard $(SRCDIR)/*.c)
OBJ:=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(OBJ))

all: mkdir $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUT)

mkdir:
	mkdir -p $(OBJDIR)

$(OBJDIR)/$(OUT).o: $(SRCDIR)/$(OUT).c
	$(CC) $(CFLAGS) $< -o $@ -c

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	rm -rf $(OUT) $(OBJDIR)

