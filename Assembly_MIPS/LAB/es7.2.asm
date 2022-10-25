.data

sequ:	.word 10

		.text
		.globl main
		.ent main
		
main:	lw $a0, sequ
ciclo:	jal calcolaSuccessivo
		
		move $a0, $v0
		j ciclo
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

	.ent calcolaSuccessivo
calcolaSuccessivo:	
		
		li $t0, 2
		div $a0, $t0
		mfhi $t1
		beq $t1, $0, pari
disp:	
		li $t3, 3
		mul $t0, $a0, $t3
		addi $v0, $t0, 1
		j fnCS
pari:	
		div $v0, $a0, $t0
		
fnCS:	move $a0, $v0
		move $t0, $v0
		li $v0, 1
		syscall
		
		li $a0, '\n'
		li $v0, 11
		syscall
		
		move $v0, $t0
		
		jr $ra
		
.end calcolaSuccessivo