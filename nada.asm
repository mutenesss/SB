;Faz nada	nada.asm
;	Objectives: testar montador asm
;	Inputs: none
;	Outputs: Status code
;Variables:
;	eax recebe numero p system call
;	ebx recebe return status
section .data
section .text
global _start
_start:
mov eax, 1
mov ebx,0
int 0x80
