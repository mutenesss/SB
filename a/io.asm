section .text
global get_string
global print_string
global end

get_string:
    enter 0,0

    push ebx
    push ecx
    push edx

    mov eax, 3
    mov ebx, 0
    mov ecx, [ebp + 8] ; Ponteiro p buffer de entrada
    mov edx, [ebp + 12] ; Tamanho do buffer a ser escrito
    int 0x80

    pop ebx
    pop ecx
    pop edx
    leave
    ret

print_string:
    enter 0,0

    push ebx
    push ecx
    push edx

    mov eax, 4
    mov ebx, 1
    mov ecx, [ebp + 8] ; Ponteiro p buffer de saida
    mov edx, [ebp + 12] ; Tamanho buffer de saida
    int 0x80

    pop ebx
    pop ecx
    pop edx
    leave
    ret

end:
    enter 0,0
    mov eax, 1
	mov ebx,0
	int 0x80
	leave
	ret
