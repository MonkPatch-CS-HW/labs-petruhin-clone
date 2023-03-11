CC=g++
CFLAGS=-Iinclude -Wall -Wextra -Werror --pedantic-errors -g3
HEADERS=$(wildcard include/*)
SOURCE=$(filter-out src/main.cpp src/test.cpp, $(wildcard src/*))
OBJECT=$(patsubst src/%,obj/%,$(SOURCE:.cpp=.o))
EXECUTABLE=lab-07_matrix

all: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $(EXECUTABLE)

obj/%.o: src/%.cpp $(HEADERS)
	@mkdir -p obj
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECT) $(EXECUTABLE) $(TEST_EXECUTABLE)
