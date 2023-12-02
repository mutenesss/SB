section .text

%define VAL1 dword[ebp + 8]
%define VAL2 dword[ebp + 12]

; global string_to_int
; global int_to_string
global add_int
global sub_int
;global mul_int
;global div_int
;global exp_int
;global mod_int
;
; string_to_int:
;     enter 4,0
;     ; EBP + 8   = Ponteiro para String
;     ; EBP + 12  = Tamanho da String
;     ; EBP + 16 = Ponteiro para salvar o numero obtido
;     ; EBP - 4 = Variavel que salva o sinal do numero
;     leave
;     ret

; int_to_string:
;     enter 0,0
;
;     leave
;     ret

add_int:
    ; EBP + 8   = Primeiro valor a ser somado
    ; EBP + 12  = Segundo valor a ser somado
    ; Resultado eh retornado em EAX
    enter 0,0
    mov eax, VAL1
    add eax, VAL2
    leave
    ret

sub_int:
    ; EBP + 8   = Primeiro valor a ser subtraido
    ; EBP + 12  = Segundo valor a ser subtraido
    ; Resultado eh retornado em EAX
    enter 0,0
    mov eax, VAL1
    sub eax, VAL2
    leave
    ret

; mul_int:
; div_int:
; exp_int:
; mod_int:
