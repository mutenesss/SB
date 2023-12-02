; Main Calculadora SB
;   Objetivos:
;   Inputs:
;   Outputs:


section .bss
    name resb 20
    arg1 resb 11    ; Maior inteiro 32 bits possivel + sinal
    arg2 resb 11    ; Maior inteiro 32 bits possivel + sinal
    resp resb 10    ; Resposta pos processamento
    opti resb 1     ; Opcao da calculadora

section .data
    msg1 db 'Bem-vindo. Digite seu nome:', 0dh, 0ah
    msg1_size EQU $-msg1

    msg2 db 'Hola, '
    msg2_size EQU $-msg2

    msg3 db ', bem-vindo ao programa de CALC IA-32', 0dh, 0ah
    msg3_size EQU $-msg3

section .text
global _start
extern get_string
extern print_string
extern end

; extern string_to_int
; extern int_to_string
extern add_int
extern sub_int
; extern mul_int
; extern div_int
; extern exp_int
; extern mod_int
_start:
    push msg1_size
    push msg1
    call print_string
    add esp, 8 ; Limpa a pilha dos dois enderecos inseridos

    push 20
    push name
    call get_string
    add esp, 8

    push 15
    push 15
    call sub_int
    mov dword [resp], eax
    add esp, 8

    call end
