GLOBAL _invalid_op_code
GLOBAL _division_by_zero

_division_by_zero:
	mov rdx, 5
	mov al,1
	mov bl,0
	div bl
	ret

_invalid_op_code:
	ud2
	ret