.586
.model flat, stdcall
includelib kernel32.lib
includelib libucrt.lib
includelib ..\Debug\GVS-2022Libs.lib
SetConsoleTitleA PROTO : DWORD
GetStdHandle PROTO:DWORD
WriteConsoleA PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD
printconsole PROTO : DWORD, : DWORD
SetConsoleOutputCP PROTO : DWORD

SetConsoleCP PROTO : DWORD

ExitProcess PROTO:DWORD


.stack 4096

EXTRN module: proc
EXTRN raiser: proc
.const
endl equ 0ah
str_endl byte endl,0
	L1 SDWORD 0
	L2 SDWORD 1
	L3 SDWORD 2
	L4 BYTE "hello", 0
HW0 = ($ - L4)

	L5 BYTE "f", 0
HW1 = ($ - L5)

	L6 SDWORD 5
	L7 SDWORD 4
	L8 SDWORD 154

.data
	buffer BYTE 256 dup(0)
	messageSize dword ?
	consoleTitle BYTE 'GVS-2022'
	result BYTE 40 dup(0)
	func_work BYTE 'Working functions='
	strsym_work BYTE 'Working symbol/string'
	int_work BYTE 'Working integer='
	consolehandle dword 0h
	sumz SDWORD 0
	Startd SDWORD 0
	Startx SDWORD 0
	Startio SDWORD 0
	Startstr DWORD ?
	Startch DWORD ?
	Starty SDWORD 0
	Startz SDWORD 0
	Startk SDWORD 0
	Startv SDWORD 0
	Startalt SDWORD 0

.code

sum PROC suma : SDWORD, sumb : SDWORD
	push suma
	push sumb
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop sumz
	push eax

	jmp local0
local0:
	pop eax
	ret
sum ENDP

main PROC
	push L2
	pop Startd
	push L3
	pop Startx
	push Startd
	push Startx
	pop edx
	pop edx
	push Startx
	push Startd
	call sum
	push eax
	pop Startio
	mov eax, Startio
	cmp eax, L1
	jg m0
	jl m1
	je m1
m0:
	push Startio
	push L2
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop Startio
	jmp e0
m1:
	push L1
	pop Startio
e0:
	mov eax, offset L4
	pop Startstr
push offset consoleTitle
call SetConsoleTitleA
mov messageSize, HW0
push -11
call GetStdHandle
mov consolehandle,eax
push 0
push 0
push messageSize
push offset Startstr
push consolehandle
call WriteConsoleA
	mov eax, offset L5
	pop Startch
push offset consoleTitle
call SetConsoleTitleA
mov messageSize, HW1
push -11
call GetStdHandle
mov consolehandle,eax
push 0
push 0
push messageSize
push offset Startch
push consolehandle
call WriteConsoleA
invoke printconsole, offset str_endl, offset consoleTitle 
	push L3
	pop Starty
	push Starty
	pop edx
	push Starty
	call module
	push eax
	pop Startz
	push Startz
	push offset result
	call int_to_char
	invoke printconsole,offset int_work,offset consoleTitle
invoke printconsole, offset str_endl, offset consoleTitle 
	push L6
	push L7
	pop edx
	pop edx
	push L7
	push L6
	call raiser
	push eax
	pop Startk
	push Startk
	push offset result
	call int_to_char
	invoke printconsole,offset int_work,offset consoleTitle
invoke printconsole, offset str_endl, offset consoleTitle 
	push L8
	pop Startv
	push Startz
	push Startk
	pop ebx
	pop eax
	and eax, ebx
	push edx
	pop Startalt
	push Startalt
	push offset result
	call int_to_char
	invoke printconsole,offset int_work,offset consoleTitle
invoke printconsole, offset str_endl, offset consoleTitle 
	mov eax, Startz
	cmp eax, L2
	jg cycle0
	jmp cyclenext0
cycle0:
	push Startz
	push L2
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop Startz
	push Startz
	push offset result
	call int_to_char
	invoke printconsole,offset int_work,offset consoleTitle
	mov eax, Startz
	cmp eax, L2
	jg cycle0
cyclenext0:
invoke printconsole, offset str_endl, offset consoleTitle 
	push eax

		jmp theend
theend:
	call ExitProcess
main ENDP

printconsole proc uses eax ebx ecx edi esi,pstr :dword,ptitle :dword
push ptitle
call SetConsoleTitleA ;
mov esi,pstr
push -11 ; -11 - handle для стандартного вывода
call GetStdHandle ; получить handle -> в eax
mov esi, pstr ; подсчет количества символов
mov edi, -1 ; до 0-символа
count:
inc edi ;
cmp byte ptr [esi + edi], 0 ; 
jne count ;
push 0 ; можно 0 (резерв)
push 0 ; можно 0
push edi ; количество байт
push pstr ; адрес выводимой строки
push eax ; handle для вывода (eax)
call WriteConsoleA ; вывести в консоль
ret ; вывести в консоль
printconsole ENDP; ----------------преобразование числа в строку--------------------------
int_to_char PROC uses eax ebx ecx edi esi,pstr : dword,intfield : sdword
mov edi, pstr
mov esi, 0
mov eax, intfield
cdq
mov ebx,10
idiv ebx
test eax, 80000000h
jz plus
neg eax
neg edx
mov cl,'-'
mov[edi],cl
inc edi
plus:
push dx
inc esi
test eax,eax;
jz fin
cdq
idiv ebx
jmp plus
fin:
mov ecx,esi
write:
pop bx
add bl, '0'
mov[edi], bl
inc edi
loop write
ret
int_to_char ENDP
end main
