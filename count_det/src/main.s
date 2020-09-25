.text

.global count_det

count_det:
	push {r4, r5, r6, r7, r8, r9, r10, r11}
	ldrb r1, [r0], #4
	ldrb r2, [r0], #4
	ldrb r3, [r0], #4
	ldrb r4, [r0], #4
	ldrb r5, [r0], #4	
	ldrb r6, [r0], #4
	ldrb r7, [r0], #4
	ldrb r8, [r0], #4
	ldrb r9, [r0], #4
	mul r0, r1, r5
	mul r0, r9
	mul r10, r3, r4
	mul r10, r8
	mul r11, r2, r6
	mul r11, r7
	mul r3, r5
	mul r3, r7
	mul r1, r6
	mul r1, r8
	mul r2, r4
	mul r2, r9
	add r0, r10
	add r0, r11
	sub r0, r1
	sub r0, r2
	sub r0, r3
	pop {r4, r5, r6, r7, r8, r9, r10, r11}
	bx lr 
	
	

