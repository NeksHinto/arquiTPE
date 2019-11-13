GLOBAL _beep
GLOBAL _unbeep

section .text

_beep:
    push rbp
    mov rbp, rsp

    mov al, 180
    out 43h, al
    mov ax, 1193
    out 42h, al
    mov al, ah
    out 42h, al
    in al, 61h
    mov al, 03h
    out 61h, al

    mov rsp, rbp
    pop rbp
    
    ret

_unbeep:
    in al, 61h
    mov al, 00h
    out 61h,al
    ret

loop:
    nop
    jmp loop
    ret