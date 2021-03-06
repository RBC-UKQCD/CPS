/* 
 * BAGEL machine generated output.  
 * Copyright UKQCD Collaboration  
 * This software is provided for NON-COMMERCIAL use only,  
 * and may not be redistributed without permission.  
 * It is provided as is, and is not guaranteed fit for any purpose.
 * Written by Peter Boyle
 */  
.text
.align 2
.globl m1dagm2dag
m1dagm2dag:

	or    %r9 , %r3 , %r3
	la   %r1,	-736(%r1)
	or    %r10 , %r4 , %r4
	or    %r11 , %r5 , %r5
	stw   %r14,	368(%r1)
	stw   %r15,	376(%r1)
	or    %r14 , %r6 , %r6
	stw   %r16,	384(%r1)
	stw   %r17,	392(%r1)
	stw   %r18,	400(%r1)
	stw   %r19,	408(%r1)
	stw   %r20,	416(%r1)
	stw   %r21,	424(%r1)
	stw   %r22,	432(%r1)
	stw   %r23,	440(%r1)
	stw   %r24,	448(%r1)
	stw   %r25,	456(%r1)
	stw   %r26,	464(%r1)
	stw   %r27,	472(%r1)
	stw   %r28,	480(%r1)
	stw   %r29,	488(%r1)
	stw   %r30,	496(%r1)
	stw   %r31,	504(%r1)
	stfd  14,	112(%r1)
	stfd  15,	120(%r1)
	stfd  16,	128(%r1)
	stfd  17,	136(%r1)
	stfd  18,	144(%r1)
	stfd  19,	152(%r1)
	stfd  20,	160(%r1)
	stfd  21,	168(%r1)
	stfd  22,	176(%r1)
	stfd  23,	184(%r1)
	stfd  24,	192(%r1)
	stfd  25,	200(%r1)
	stfd  26,	208(%r1)
	stfd  27,	216(%r1)
	stfd  28,	224(%r1)
	stfd  29,	232(%r1)
	stfd  30,	240(%r1)
	stfd  31,	248(%r1)
	lwz   %r13,	0(%r14)
	or.  %r13 , %r13 , %r13
	bf gt,  m1dagm2dag_lab0
	or    %r12 , %r9 , %r9
	li   %r15,128
	li   %r16,160
	li   %r17,192
	li   %r18,224
	li   %r19,256
	lfd   0,	0(%r10)
	lfd   2,	48(%r10)
	lfd   1,	8(%r10)
	lfd   3,	56(%r10)
	lfd   6,	0(%r11)
	lfd   7,	8(%r11)
	lfd   8,	48(%r11)
	lfd   9,	56(%r11)
	lfd   10,	96(%r11)
	lfd   11,	104(%r11)
	mtctr 	%r13
	b       m1dagm2dag_lab1
.align 4
m1dagm2dag_lab1:
	fmul   24 , 0 , 6
	stfd  26,	112(%r12)
	fmul   25 , 0 , 7
	lfd   12,	16(%r11)
	fmul   26 , 0 , 8
	stfd  27,	120(%r12)
	lfd   13,	24(%r11)
	fmul   27 , 0 , 9
	lfd   14,	64(%r11)
	fnmsub 24 , 1 , 7 , 24
	lfd   15,	72(%r11)
	fnmadd 25 , 1 , 6 , 25
	lfd   16,	112(%r11)
	fnmsub 26 , 1 , 9 , 26
	lfd   17,	120(%r11)
	lfd   18,	32(%r11)
	fnmadd 27 , 1 , 8 , 27
	lfd   19,	40(%r11)
	fmadd  24 , 2 , 12 , 24
	lfd   20,	80(%r11)
	fnmsub 25 , 2 , 13 , 25
	lfd   21,	88(%r11)
	fmadd  26 , 2 , 14 , 26
	lfd   22,	128(%r11)
	lfd   23,	136(%r11)
	fnmsub 27 , 2 , 15 , 27
	lfd   4,	96(%r10)
	fnmsub 24 , 3 , 13 , 24
	lfd   5,	104(%r10)
	fnmsub 25 , 3 , 12 , 25
	stfd  28,	128(%r12)
	fnmsub 26 , 3 , 15 , 26
	la   %r13,	-1(%r13)
	fmul   28 , 0 , 10
	stfd  29,	136(%r12)
	fnmsub 27 , 3 , 14 , 27
	dcbt 	%r15,%r10
	fmul   29 , 0 , 11
	or    %r12 , %r9 , %r9
	fmadd  24 , 4 , 18 , 24
	fnmsub 25 , 4 , 19 , 25
	lfd   0,	16(%r10)
	fnmsub 28 , 1 , 11 , 28
	dcbt 	%r16,%r10
	fmadd  26 , 4 , 20 , 26
	fnmadd 29 , 1 , 10 , 29
	fnmsub 27 , 4 , 21 , 27
	fnmsub 24 , 5 , 19 , 24
	lfd   1,	24(%r10)
	fmadd  28 , 2 , 16 , 28
	dcbt 	%r17,%r10
	fnmsub 25 , 5 , 18 , 25
	fnmsub 29 , 2 , 17 , 29
	fnmsub 26 , 5 , 21 , 26
	fnmsub 27 , 5 , 20 , 27
	stfd  24,	0(%r9)
	fnmsub 28 , 3 , 17 , 28
	lfd   2,	64(%r10)
	fmul   24 , 0 , 6
	stfd  25,	8(%r9)
	fnmsub 29 , 3 , 16 , 29
	fmul   25 , 0 , 7
	stfd  26,	16(%r9)
	stfd  27,	24(%r9)
	fmadd  28 , 4 , 22 , 28
	fmul   26 , 0 , 8
	lfd   3,	72(%r10)
	fnmsub 29 , 4 , 23 , 29
	fmul   27 , 0 , 9
	fnmsub 24 , 1 , 7 , 24
	lfd   4,	112(%r10)
	fnmsub 28 , 5 , 23 , 28
	dcbt 	%r18,%r10
	fnmadd 25 , 1 , 6 , 25
	fnmsub 29 , 5 , 22 , 29
	fnmsub 26 , 1 , 9 , 26
	fnmadd 27 , 1 , 8 , 27
	lfd   5,	120(%r10)
	fmadd  24 , 2 , 12 , 24
	stfd  28,	32(%r9)
	fnmsub 25 , 2 , 13 , 25
	fmul   28 , 0 , 10
	stfd  29,	40(%r9)
	fmadd  26 , 2 , 14 , 26
	dcbt 	%r19,%r10
	fmul   29 , 0 , 11
	fnmsub 27 , 2 , 15 , 27
	fnmsub 24 , 3 , 13 , 24
	lfd   0,	32(%r10)
	fnmsub 28 , 1 , 11 , 28
	dcbt 	%r15,%r11
	fnmsub 25 , 3 , 12 , 25
	fnmadd 29 , 1 , 10 , 29
	fnmsub 26 , 3 , 15 , 26
	fnmsub 27 , 3 , 14 , 27
	dcbt 	%r16,%r11
	fmadd  28 , 2 , 16 , 28
	fmadd  24 , 4 , 18 , 24
	fnmsub 29 , 2 , 17 , 29
	lfd   1,	40(%r10)
	fnmsub 25 , 4 , 19 , 25
	dcbt 	%r17,%r11
	fmadd  26 , 4 , 20 , 26
	fnmsub 28 , 3 , 17 , 28
	fnmsub 27 , 4 , 21 , 27
	lfd   2,	80(%r10)
	fnmsub 29 , 3 , 16 , 29
	dcbt 	%r18,%r11
	fnmsub 24 , 5 , 19 , 24
	fnmsub 25 , 5 , 18 , 25
	fmadd  28 , 4 , 22 , 28
	lfd   3,	88(%r10)
	fnmsub 26 , 5 , 21 , 26
	dcbt 	%r19,%r11
	fnmsub 29 , 4 , 23 , 29
	fnmsub 27 , 5 , 20 , 27
	stfd  24,	48(%r9)
	fnmsub 28 , 5 , 23 , 28
	stfd  25,	56(%r9)
	fmul   24 , 0 , 6
	la   %r11,	144(%r11)
	fnmsub 29 , 5 , 22 , 29
	stfd  26,	64(%r9)
	fmul   25 , 0 , 7
	stfd  27,	72(%r9)
	fmul   26 , 0 , 8
	fmul   27 , 0 , 9
	lfd   4,	128(%r10)
	fnmsub 24 , 1 , 7 , 24
	lfd   5,	136(%r10)
	fnmadd 25 , 1 , 6 , 25
	stfd  28,	80(%r9)
	fnmsub 26 , 1 , 9 , 26
	stfd  29,	88(%r9)
	fmul   28 , 0 , 10
	la   %r10,	144(%r10)
	fmul   29 , 0 , 11
	la   %r9,	144(%r9)
	fnmadd 27 , 1 , 8 , 27
	lfd   6,	0(%r11)
	fmadd  24 , 2 , 12 , 24
	lfd   0,	0(%r10)
	fnmsub 25 , 2 , 13 , 25
	fnmsub 28 , 1 , 11 , 28
	lfd   7,	8(%r11)
	fnmadd 29 , 1 , 10 , 29
	lfd   8,	48(%r11)
	fmadd  26 , 2 , 14 , 26
	fnmsub 27 , 2 , 15 , 27
	lfd   1,	8(%r10)
	fnmsub 24 , 3 , 13 , 24
	lfd   9,	56(%r11)
	fmadd  28 , 2 , 16 , 28
	fnmsub 29 , 2 , 17 , 29
	lfd   10,	96(%r11)
	fnmsub 25 , 3 , 12 , 25
	lfd   11,	104(%r11)
	fnmsub 26 , 3 , 15 , 26
	lfd   2,	48(%r10)
	fnmsub 27 , 3 , 14 , 27
	fnmsub 28 , 3 , 17 , 28
	fnmsub 29 , 3 , 16 , 29
	fmadd  24 , 4 , 18 , 24
	fnmsub 25 , 4 , 19 , 25
	lfd   3,	56(%r10)
	fmadd  26 , 4 , 20 , 26
	fnmsub 27 , 4 , 21 , 27
	fmadd  28 , 4 , 22 , 28
	fnmsub 29 , 4 , 23 , 29
	fnmsub 24 , 5 , 19 , 24
	fnmsub 25 , 5 , 18 , 25
	fnmsub 26 , 5 , 21 , 26
	fnmsub 27 , 5 , 20 , 27
	fnmsub 28 , 5 , 23 , 28
	fnmsub 29 , 5 , 22 , 29
	stfd  24,	96(%r12)
	stfd  25,	104(%r12)
	bdnz    m1dagm2dag_lab1
	stfd  26,	112(%r12)
	stfd  27,	120(%r12)
	stfd  28,	128(%r12)
	stfd  29,	136(%r12)
m1dagm2dag_lab0:
	lwz   %r14,	368(%r1)
	lwz   %r15,	376(%r1)
	lwz   %r16,	384(%r1)
	lwz   %r17,	392(%r1)
	lwz   %r18,	400(%r1)
	lwz   %r19,	408(%r1)
	lwz   %r20,	416(%r1)
	lwz   %r21,	424(%r1)
	lwz   %r22,	432(%r1)
	lwz   %r23,	440(%r1)
	lwz   %r24,	448(%r1)
	lwz   %r25,	456(%r1)
	lwz   %r26,	464(%r1)
	lwz   %r27,	472(%r1)
	lwz   %r28,	480(%r1)
	lwz   %r29,	488(%r1)
	lwz   %r30,	496(%r1)
	lwz   %r31,	504(%r1)
	lfd   14,	112(%r1)
	lfd   15,	120(%r1)
	lfd   16,	128(%r1)
	lfd   17,	136(%r1)
	lfd   18,	144(%r1)
	lfd   19,	152(%r1)
	lfd   20,	160(%r1)
	lfd   21,	168(%r1)
	lfd   22,	176(%r1)
	lfd   23,	184(%r1)
	lfd   24,	192(%r1)
	lfd   25,	200(%r1)
	lfd   26,	208(%r1)
	lfd   27,	216(%r1)
	lfd   28,	224(%r1)
	lfd   29,	232(%r1)
	lfd   30,	240(%r1)
	lfd   31,	248(%r1)
	la   %r1,	736(%r1)
	blr
