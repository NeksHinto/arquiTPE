GLOBAL _beep
GLOBAL _unbeep
section .text

_beep:
    push rbp
    mov rbp, rsp

    mov rax,0
    mov al, 182
    out 0x43, al
    mov ax, 9121
    out 0x42, al
    mov al, ah
    out 0x42, al
    in al, 0x61
    or al, 0x03
    out 61h, al

    mov rsp, rbp
    pop rbp
    ret

_unbeep:
    in al, 0x61
    and al, 0xFC
    out 0x61, al
    ret
