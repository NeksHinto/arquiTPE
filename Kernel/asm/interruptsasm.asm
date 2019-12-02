
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _exception0Handler
GLOBAL _exception6Handler
GLOBAL _irq00Handler
GLOBAL _irq01Handler

GLOBAL getStackPointer
GLOBAL _syscallHandler

GLOBAL instructionPointerBackup
GLOBAL stackPointerBackup

EXTERN exceptionDispatcher
EXTERN irqDispatcher
EXTERN syscallDispatcher
EXTERN main

SECTION .text

; Backup regs macro
; Stack all 64-bit regs
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

; Restore regs macro
; Unstack all 64-bit regs
%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

; IRQ Handle Master macro
; Receive IRQ-number as a parameter and call
; the dispatcher to handle the interruption acordingly,
; then send EOI signal.
%macro irqHandlerMaster 1
	pushState

	mov rdi, %1           ; passing parameter
	call irqDispatcher

	mov al, 20h            ; signal pic EOI (End of Interrupt)
	out 20h, al

	popState
	iretq
%endmacro

%macro exceptionHandler 1
	mov rsi,[rsp]       ; direction where the exception happened.
	pushState

	mov rdi, %1
	mov rdx, rsp        ; ptr to stack where regs were pushed.
	call exceptionDispatcher
	popState

	mov rdi, [instructionPointerBackup]
	mov qword [rsp], rdi ; dirección del sampleCodeModule para retornar de vuelta.
	mov rdi, [stackPointerBackup]
	mov qword[rsp + 3*8], rdi
	iretq

%endmacro

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = 16-bits mask
    out	    0A1h,al
    pop     rbp
    retn


;Division by zero
_exception0Handler:
	exceptionHandler 0

;Invalid opcode
_exception6Handler:
	exceptionHandler 6

;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;System calls handler
_syscallHandler:
	push rbp
	mov rbp, rsp

	push r8
	push rdx
	push rsi
	push rdi

	mov rdi, rax
	pop rsi
	pop rdx
	pop rcx
	mov r8, r10
	pop r9
	call syscallDispatcher
	leave
	iretq

haltcpu:
	cli
	hlt
	ret

getStackPointer:
	mov rax, rsp
	ret

SECTION .bss
	sampleCodeModule equ 0x400000
	stackPointerBackup resq 1
	instructionPointerBackup resq 1
