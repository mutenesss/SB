secao text
input n
load n
fat: sub one
jmpz fim
store aux
mul n
store n
load aux
jmp fat
fim: output n
STOP
aux:space
n: space
one: const 1