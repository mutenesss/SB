;Calculadora IA-32	calculator.asm
;	Objectives: Calcular o resultado da operacao de dois valores 
;	Inputs: dois inteiros e uma operacao
;	Outputs: resultado da operacao
;Variables:
;	arg1 -> primeiro argumento
;	arg2 -> segundo argumento
;	op -> operacao

section .bss
	arg1 		resb 11
	arg2 		resb 11
	op 		resb 11
	result 		resb 11
section .data
	msg1 		db 'Digite o primeiro numero', 0dH, 0aH
	msg2 		db 'Digite o segundo numero', 0dH, 0aH
	size_msg1 	EQU $-msg1
	size_msg2 	EQU $-msg2
	msg_op 		db 'Digite o numero da operacao desejada', 0dH, 0aH
	size_msg_op 	EQU $-msg_op
	msg_result	db 'Resultado da operacao', 0dH, 0aH
	size_msg_res 	EQU $-msg_result
section .text
global _start
_start:
	;Entrada do valor arg1
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, size_msg1
	int 0x80
	
	mov eax, 3
	mov ebx, 0
	mov ecx, arg1
	mov edx, 2
	int 0x80
	
	;Entrada do valor arg2
	mov eax, 4
	mov ebx, 1
	mov ecx, msg2
	mov edx, size_msg2
	int 0x80
	
	mov eax, 3
	mov ebx, 0
	mov ecx, arg2
	mov edx, 2
	int 0x80
	
	;Entrada da operacao
	mov eax, 4
	mov ebx, 1
	mov ecx, msg_op
	mov edx, size_msg_op
	int 0x80
	
	mov eax, 3
	mov ebx, 0
	mov ecx, op
	mov edx, 2
	int 0x80
	
	jmp find_op

find_op:
	mov dword eax, op
	cmp eax, 1
	je op_add
	cmp eax, 2
	je op_sub
	
	jmp fim

fim:	
	mov eax, 1
	mov ebx, 0
	int 0x80

op_add:
	mov dword eax, [arg1]
	add eax, [arg2]
	mov dword [result], eax
	jmp show_result
	
op_sub:
	mov dword eax, [arg1]
	sub eax, [arg2]
	mov dword [result], eax
	jmp show_result
	
show_result: 
	;Entrada da operacao
	mov eax, 4
	mov ebx, 1
	mov ecx, msg_result
	mov edx, size_msg_res
	int 0x80
	
	mov eax, 4
	mov ebx, 1
	mov ecx, result
	mov edx, 10
	int 0x80
	jmp fim
