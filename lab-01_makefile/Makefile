CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -Werror
HEADERS=$(wildcard include/*)
SOURCE=$(wildcard src/*)
OBJECT=$(patsubst src/%,obj/%,$(SOURCE:.c=.o))
EXECUTABLE=lab-01_makefile

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(EXECUTABLE)

obj/%.o: src/%.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJECT) $(EXECUTABLE)
