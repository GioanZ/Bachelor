.data

DIM = 5
vet1:	.word 56, 12, 98, 129, 58
vet2:	.word 1, 0, 245, 129, 12
result:	.space DIM

		.text
		.globl main
		.ent main
		
main:	la $a0, vet1
		la $a1, vet2
		la $a2, result
		li $a3, DIM
		jal CalcolaDistanzaH
		
		la $t0, result
		li $t2, DIM
		li $t1, 0
ciclStp:lb $a0, ($t0)
		addi $t0, $t0, 1
		li $v0, 1
		syscall
		li $a0, '\n'
		li $v0, 11
		syscall
		
		addi $t1, $t1, 1		#i++
		bne $t1, $t2, ciclStp
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

	.ent CalcolaDistanzaH
CalcolaDistanzaH:	
		
		li $t5, 0
		move $s0, $a0
		move $s1, $a1
		move $s2, $a2
		move $s3, $a3
		addi $sp, $sp, -4
		sw $ra, ($sp)			#salva ritorno a main
		
cicl:	lw $t0, ($s0)
		lw $t1, ($s1)
		addi $s0, $s0, 4
		addi $s1, $s1, 4
		addi $t5, $t5, 1
		xor	$a0, $t0, $t1		#se bit uguali da 0, se sono diversi da 1
		
		jal CountUno
		
		sb $v0, ($s2)			#scrivi risultato in vettore
		addi $s2, $s2, 1
		
		bne $t5, $a3, cicl
		
		lw $ra, ($sp)
		add $sp, $sp, 4
		jr $ra
		
.end CalcolaDistanzaH


	.ent CountUno
CountUno:
		
		move $t0, $a0
		li $t2, 2
		li $v0, 0
		
cicl2:	div $t0, $t2
		mflo $t0
		mfhi $t1
		
		add $v0, $v0, $t1
		bne $t0, $0, cicl2
		
		jr $ra
		
.end CountUno