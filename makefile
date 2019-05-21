all: square.e
square.e: main.o func.o calc.o
	gcc -o square.e main.o calc.o func.o
main.o: main.c lib.h
	gcc -std=c99 -c -o main.o main.c
calc.o: calc.c
	gcc -std=c99 -c -o calc.o calc.c
func.o: func.asm
	nasm -f win32 -o func.o func.asm -DCYGWIN
clean:
	rm -f main.o func.o calc.o
