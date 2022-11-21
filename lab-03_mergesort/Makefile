CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -Werror
HEADERS=$(wildcard include/*)
SOURCE=$(filter-out src/main.c src/test.c, $(wildcard src/*))
OBJECT=$(patsubst src/%,obj/%,$(SOURCE:.c=.o))
EXECUTABLE=lab-03_mergesort
TEST_EXECUTABLE=test

all: $(EXECUTABLE) $(TEST_EXECUTABLE)

$(EXECUTABLE): obj/main.o $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $(EXECUTABLE)

$(TEST_EXECUTABLE): obj/test.o $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $(TEST_EXECUTABLE)

obj/%.o: src/%.c $(HEADERS)
	@mkdir -p obj
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECT) $(EXECUTABLE) $(TEST_EXECUTABLE)
