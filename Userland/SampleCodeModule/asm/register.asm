GLOBAL infoReg
EXTERN write_registers

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

infoReg:
    push rbp
    mov rbp, rsp

    pushState
    mov rdi, rsp

    call write_registers

    mov rax, 0

    leave
    ret
