CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -Werror
HEADERS=$(wildcard include/*)
SOURCE=$(wildcard src/*)
OBJECT=$(patsubst src/%,obj/%,$(SOURCE:.c=.o))
EXECUTABLE=lab-02_cstrings

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(EXECUTABLE)

obj/%.o: src/%.c $(HEADERS)
	@mkdir -p obj
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJECT) $(EXECUTABLE)
