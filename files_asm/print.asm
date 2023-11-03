;Print de um valor obtido na entrada	print.asm
;	Objectives: printar valor recebido na entrada
;	Inputs: int
;	Outputs: int recebido na entrada, status code
;Variables:
;	eax recebe numero p system call
;	ebx recebe return status
section .data
	number dw 1
section .text
global _start
_start:
	mov eax, 3
	mov ebx, 0
	mov ecx, number
	mov edx, 32
	int 0x80
	 
	mov eax, 4 ; sys write
	mov ebx, 1 ; stdout
	mov ecx, number
	mov edx, 32
	int 0x80 ; executa syscall
	
	mov eax, 1
	mov ebx,0
	int 0x80
