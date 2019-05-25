TARGET = bin/square.e

PROG_OBJ = obj/main.o obj/func.o obj/calc.o

C_FLAGS = -std=c99 -c -m32 -o
ASM_FLAGS = -f elf32 -DUNIX -o

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(PROG_OBJ)

$(TARGET): $(PROG_OBJ)
	gcc -o $(TARGET) -m32 $(PROG_OBJ)
obj/main.o: src/main.c src/lib.h
	gcc $(C_FLAGS) obj/main.o src/main.c
obj/%.o: src/%.c
	gcc $(C_FLAGS) $@ $<
obj/%.o: src/%.asm
	nasm $(ASM_FLAGS) $@ $<

