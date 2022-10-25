.data

or_in:	.byte 12, 47
or_out:	.byte 18, 14
X: 		.byte 1
Y: 		.byte 40

		.text
		.globl main
		.ent main
		
main:	la $a0, or_in # indirizzo di ora_in
		la $a1, or_out # indirizzo di ora_out
		lbu $a2, X
		lbu $a3, Y
		jal costoParcheggio
		
		move $a0, $v0
		li $v0, 1
		syscall

fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

	.ent costoParcheggio
costoParcheggio:	
		
		lb $t0, ($a0)
		lb $t1, 1($a0)
		lb $t2, ($a1)
		lb $t3, 1($a1)
		
		li $t6, 60
		
		mul $t0, $t0, $t6
		mul $t2, $t2, $t6
		
		add $t0, $t0, $t1
		add $t2, $t2, $t3
		
		sub $t0, $t2, $t0
		beq $t0, $0, aggEcc
		
		div $t0, $a3
		mflo $t0
		mfhi $t1
		
		beq $t1, $0, calcCost

aggEcc:	addi $t0, $t0, 1

calcCost:
		mul $v0, $t0, $a2
		
		jr $ra
		
.end costoParcheggio