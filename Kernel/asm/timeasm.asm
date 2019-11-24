GLOBAL _get_seconds
GLOBAL _get_minutes
GLOBAL _get_hours

%macro accessRTC 1
	push rbp
	mov rbp,rsp
	
	mov rax, 0h
	mov al, %1
	out 70h, al
	in al, 71h

	leave
	ret
%endmacro

_get_seconds:
	accessRTC 0

_get_minutes:
	accessRTC 2

_get_hours:
	accessRTC 4
