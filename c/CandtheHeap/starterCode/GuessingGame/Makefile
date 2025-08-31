CC = GCC
CFLAGS = -Wall
CFILES = GuessingGamePart3.c

all: myprogram

myprogram:
	$(CC) $(CFLAGS) $(CFILES) GuessingGameDriver.c -o game.out

test:
	$(CC) $(CFLAGS) $(CFILES) TestDriver.c -o game.out

clean:
	rm *.out