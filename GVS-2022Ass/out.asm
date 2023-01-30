.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../GVS-2022/Debug/GVS-2022Libs.lib
ExitProcess PROTO :DWORD

EXTRN module: proc
EXTRN raise: proc
EXTRN outputint: proc
EXTRN outputstr: proc
EXTRN outputsym: proc

.stack 4096

.const
	L1 SDWORD 0
	L2 SDWORD 1
	L3 SDWORD 2
	L4 BYTE "hello", 0
	L5 BYTE "f", 0
	L6 SDWORD 5
	L7 SDWORD 4
	L8 SDWORD 154

.data
	buffer BYTE 256 dup(0)
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

sum PROC 
	pop sumz
	push 0
	jmp local0
local0:
	pop eax
	ret
sum ENDP

main PROC
	pop Startd
	pop Startx
	pop Startio
	push Startx
	push Startd
	call sum
	mov eax, Startio
	cmp eax, L1
	je m1
m0:
	pop Startio
	jmp e0
m1:
	pop Startio
e0:

	call outputstr
	pop Startstr
	push Startstr
	call outputstr
	pop Startch
	push Startch
	call outputstr

	call outputstr
	pop Starty
	pop Startz
	push Starty
	call module
	push Startz
	call outputint

	call outputstr
	pop Startk
	push L7
	push L6
	call raise
	push Startk
	call outputint

	call outputstr
	pop Startv
	pop Startalt
	push Startalt
	call outputint

	call outputstr
	mov eax, Startz
	cmp eax, L2
	jmp cyclenext0
cycle0:
	pop Startk
	push Startk
	call outputint
	mov eax, Startz
	cmp eax, L2
cyclenext0:

	call outputstr
	push 0
		jmp theend
theend:
	call ExitProcess
main ENDP
end main