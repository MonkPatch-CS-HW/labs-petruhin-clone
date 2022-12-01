.PHONY: all clean

CC = gcc

all: lab_05

obj:
	mkdir -p obj

lab_05: src/main.c obj/clist.o obj/pose_list.o include/*.h
	$(CC) -o $@ -Iinclude $< obj/*

obj/%.o: src/%.c include/*.h | obj
	$(CC) -Wall -Wextra -Werror -c -o $@ -Iinclude $<

clean:
	rm -rf obj lab_05
