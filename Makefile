CC = gcc
CFLAGS = -Wall -Wextra

SRC = $(wildcard src/*.c) $(wildcard src/modules/*/*.c)

main.exe: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o main.exe

clean:
	del main.exe