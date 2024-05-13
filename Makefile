default:
	nasm -f elf32 impl/ioport.asm -o out/asmioport.o
	nasm -f elf32 impl/idt.asm -o out/asmidt.o
	nasm -f elf32 impl/kb.asm -o out/asmkb.o
	gcc -m32 -Wall -c impl/*.c -Iinclude
	nasm -f elf32 kernel.asm -o out/asmkern.o
	gcc -m32 -Wall -c kernel.c -Iinclude
	mv *.o out/
	ld -m elf_i386 -T link.ld -o bin/kernel out/*