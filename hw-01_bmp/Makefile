CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -Werror --pedantic-errors -O0 -g3
HEADERS=$(wildcard include/*)
SOURCE=$(filter-out src/main.c src/test.c, $(wildcard src/*))
OBJECT=$(patsubst src/%,obj/%,$(SOURCE:.c=.o))
EXECUTABLE=hw-01_bmp

all: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $(EXECUTABLE)

obj/%.o: src/%.c $(HEADERS)
	@mkdir -p obj
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECT) $(EXECUTABLE) $(TEST_EXECUTABLE)
