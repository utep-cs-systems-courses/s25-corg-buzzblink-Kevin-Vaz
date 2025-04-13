	.arch msp430g2553
	.text
	.global transition1
	.global transition2
	.global transition3
	.global transition4

transition1:
	cmp.b   #4, &sw1	; Compare sw1 with 4
	jge     reset1	; If sw1 >= 4, jump to reset
	add.b   #1, &sw1	; Else, increment sw1
	pop     r0		; Return
reset1:
	mov.b   #1, &sw1	; Reset sw1 to 1
	pop     r0		; Return

transition2:
	cmp.b   #5, &sw2	; Compare sw2 with 5
	jge     reset2
	add.b   #1, &sw2
	pop     r0
reset2:
	mov.b   #1, &sw2
	pop     r0

transition3:
	cmp.b   #6, &sw3	; Compare sw3 with 6
	jge     reset3
	add.b   #1, &sw3
	pop     r0
reset3:
	mov.b   #1, &sw3
	pop     r0

transition4:

	cmp.b   #8, &sw4	; Compare sw4 with 8

	jge     reset4

	add.b   #1, &sw4

	pop     r0

reset4:
	mov.b   #1, &sw4
	    pop     r0
