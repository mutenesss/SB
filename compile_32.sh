cd NASM_32/
./nasm -f elf -o io.o io.asm && ./nasm -f elf -o main.o main.asm && ./nasm -f elf -o op.o op.asm &&  ld -m elf_i386 -o calc_32 main.o io.o op.o
mv ./calc_32 ..
