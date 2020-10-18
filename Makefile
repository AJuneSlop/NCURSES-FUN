CFLAGS= -g -Wall
LDLIBS= -lncurses

.PHONY: clean

all: demo

clean:
	rm -rf demo
