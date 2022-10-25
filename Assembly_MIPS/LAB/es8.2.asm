.data

DIM = 6
anni:	.word 1945, 2008, 1800, 2006, 1748, 1600
result:	.space DIM

		.text
		.globl main
		.ent main
		
main:	li $a2, DIM				#lunghezza vettori
		la $a0, anni
		la $a1, result
		
		jal bisestile
		
		move $t0, $v0
		li $t1, 0
		li $t2, DIM
		
ciclStp:lb $a0, ($t0)
		addi $t0, $t0, 1
		li $v0, 1
		syscall
		li $a0, '\n'
		li $v0, 11
		syscall
		
		addi $t1, $t1, 1
		bne $t1, $t2, ciclStp
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

	.ent bisestile
bisestile:	
		
		li $t3, 0
		li $t1, 1
		li $t5, 100
		li $t6, 400
		li $t7, 4
		move $s0, $a1
		
cicl:	lw $t0, ($a0)		#legge l'anno
		addi $a0, $a0, 4
		addi $t3, $t3, 1
		
if:		div $t0, $t5
		mfhi $t2
		bne $t2, $0, else
		#{
if2:	div $t0, $t6
		mfhi $t2
		bne $t2, $0, nAnnBis
		j annBis
		#}
else:	div $t0, $t7
		mfhi $t2
		bne $t2, $0, nAnnBis
		j annBis
		
annBis:	sb $t1, ($a1)
		j cnt
		
nAnnBis:sb $0, ($a1)
		
cnt:	addi $a1, $a1, 1
		bne $t3, $a2, cicl
		
		move $v0, $s0
		jr $ra
		
.end bisestile