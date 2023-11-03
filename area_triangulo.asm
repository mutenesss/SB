;Calculo da area de um triangulo	area.asm
;	Objectives: calcular a area de um triangulo 
;	Inputs: dois inteiros representando os catetos
;	Outputs: resultado da area do triangulo
;Variables:
;	eax -> recebe numero p system call
;	ebx -> recebe return status
;	a, b -> catetos
;	quo -> quociente da divisao
;	rest -> resto da divisao

section .bss
	a resb 1
	b resb 1
	quo resb 4
	resto resb 4
	 
section .data
	msg1 db 'Digite o primeiro numero', 0dH, 0ah
	msg2 db 'Digite o segundo numero', 0dH, 0ah
	msg_quo db 'Quociente:', 0dH, 0ah
	msg_rest db 'Resto:', 0dH, 0ah
	msg1_size EQU $-msg1
	msg2_size EQU $-msg2 
	msg_quo_size EQU $-msg_quo
	msg_rest_size EQU $-msg_rest
	
section .text
global _start
_start:
	; Pedido primeiro numero
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, msg1_size
	int 0x80
	
	mov eax, 3
	mov ebx, 0
	mov ecx, a
	mov edx, 2
	int 0x80
	
	; Pedido segundo numero
	mov eax, 4 
	mov ebx, 1
	mov ecx, msg2
	mov edx, msg2_size
	int 0x80 
	
	mov eax, 3 
	mov ebx, 0
	mov ecx, b
	mov ecx, 2
	int 0x80

_calc:
	mov eax, a
	add eax, [b]
	cdq
	mov bx, 2
	idiv bx
	; div 32/16 -> quociente = eax, resto = edx 
	; os dois mov seguintes estao com erro
	; objetivo: retirar valores de eax e edx para memoria
	; possivel problema -> o programa acaba antes da divisao ser completa, por isso saida vazia
	mov [quo], eax
	mov [resto], edx

_result:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg_quo
	mov edx, msg_quo_size
	int 0x80
	
	mov eax, 4 
	mov ebx, 1
	mov ecx, quo
	mov ecx, 2
	int 0x80
	
	mov eax, 4
	mov ebx, 1
	mov ecx, msg_rest
	mov edx, msg_rest_size
	int 0x80
	
	mov eax, 4 
	mov ebx, 1
	mov ecx, resto
	mov ecx, 2
	int 0x80
	
	mov eax, 1
	mov ebx,0
	int 0x80
