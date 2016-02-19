TARGET = tetris
DEPENDENCIES = placing movement graphics auxiliaries rotation gfx5
SUFFIX = c
CC = gcc
CFLAGS =
LINKING= -lX11

all: $(TARGET)

$(TARGET): $(TARGET:=.o) $(DEPENDENCIES:=.o)
	$(CC) $(CFLAGS) $^ -o $@ $(LINKING)

%.o: %.$(SUFFIX)
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f *.o $(TARGET)
