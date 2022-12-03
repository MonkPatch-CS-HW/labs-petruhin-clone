CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -Werror --pedantic-errors -g3
HEADERS=$(wildcard include/*)
SOURCE=$(filter-out src/main.c src/test.c, $(wildcard src/*))
OBJECT=$(patsubst src/%,obj/%,$(SOURCE:.c=.o))
EXECUTABLE=lab-04_intrusive-list

all: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $(EXECUTABLE)

obj/%.o: src/%.c $(HEADERS)
	@mkdir -p obj
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECT) $(EXECUTABLE) $(TEST_EXECUTABLE)
