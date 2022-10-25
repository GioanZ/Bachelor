.data

num1:	.word 200
num2:	.word 150
num3:	.word 210

		.text
		.globl main
		.ent main
		
main:	lw $t1, num1
		lw $t2, num2
		lw $t3, num3
		
L1:		blt $t1, $t2, L2
			swap1:	add $t0, $t1, $0
					add $t1, $t2, $0
					add $t2, $t0, $0
		
L2:		blt $t1, $t3, L3
			swap2:	add $t0, $t1, $0
					add $t1, $t3, $0
					add $t3, $t0, $0
		
L3:		blt $t2, $t3, stmp
			swap3:	add $t0, $t3, $0
					add $t3, $t2, $0
					add $t2, $t0, $0
		
stmp:	la $a0, ($t1)
		li $v0, 1
		syscall
		
		la $a0, ($t2)
		li $v0, 1
		syscall
		
		la $a0, ($t3)
		li $v0, 1
		syscall
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
		.end main