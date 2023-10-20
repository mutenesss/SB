secao text
copy zero,older
copy one,old
INPUT limit
OUTPUT old
front: load older
add old
store new
sub limit
jmpp final
output new
copy old,older
copy new,old
jmp front
final: output limit
STOP
zero: const 0
one: const 1
older: SPACE
old:space
new: 	space
limit: space