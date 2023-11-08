;Somador	sum.asm
;	Objectives: calcular a soma de dois valores 
;	Inputs: dois valores inteiros
;	Outputs: soma dos valores
;Variables:
;	arg1 -> primeiro valor
;	arg2 -> segundo valor
;	res -> resultado da soma

section .bss
	arg1	resb 11
	arg2 	resb 11
	res	resb 11
	 
section .data
	msg1 db 'Digite o primeiro numero', 0dH, 0ah
	msg2 db 'Digite o segundo numero', 0dH, 0ah
	msg1_size EQU $-msg1
	msg2_size EQU $-msg2 
	
section .text
global _start
_start:
	; Pedido primeiro numero
	mov eax, 4		; sys_write
	mov ebx, 1		; write on monitor
	mov ecx, msg1		; pointer to msg
	mov edx, msg1_size	; length of msg
	int 0x80
	
	mov eax, 3		; sys_read
	mov ebx, 0		; read from keyboard
	mov ecx, arg1		; pointer to store arg1
	mov edx, 11		; size of arg1
	int 0x80
	
	push arg1 		; coloca arg1 na pilha
	
	; Pedido segundo numero
	mov eax, 4		; sys_write
	mov ebx, 1		; write on monitor
	mov ecx, msg2		; pointer to msg
	mov edx, msg2_size	; length of msg
	int 0x80
	
	mov eax, 3		; sys_read
	mov ebx, 0		; read from keyboard
	mov ecx, arg2		; pointer to store arg1
	mov edx, 11		; size of arg1
	int 0x80
	
	push arg2 		; coloca arg2 na pilha
	
	call sum
	add esp, 8
	
	mov eax, 1
	mov ebx,0
	int 0x80

sum:	
	push ebp
	mov ebp, esp
	
	mov eax, [ebp + 8]
	mov ebx, [ebp + 12]
	add eax, ebx
	
	mov dword [res], eax
	mov eax, 4
	mov ebx, 1
	mov ecx, res
	mov edx, 11
	int 0x80
	
	mov esp, ebp
	pop ebp
	ret
