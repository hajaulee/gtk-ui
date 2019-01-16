default: main

main:
	clear 
	gcc -w -g -o main main.c -lgthread-2.0 `pkg-config gtk+-3.0 --cflags --libs`

w:
	clear 
	gcc -Wall -g -o main main.c -lgthread-2.0 `pkg-config gtk+-3.0 --cflags --libs`

run: main
	./main
debug: main
	gdb ./main	
clean:
	rm -f main