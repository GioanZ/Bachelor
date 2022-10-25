.data

NUM = 5
DIM = NUM * 4
SCONTO = 30
ARROTONDA = 1
prezzi: .word 39, 1880, 2394, 1000, 1590
scont:	.space DIM

		.text
		.globl main
		.ent main
		
main:	
		la $a0, prezzi
		la $a1, scont
		li $a2, NUM
		li $a3, SCONTO
		li $t0, ARROTONDA
		subu $sp, 4 
		sw $t0, ($sp)
		jal calcola_sconto
		
		move $a0, $v0
		li $v0, 1
		syscall
		li $a0, '\n'
		li $v0, 11
		syscall
		
		la $t0, scont
		li $t1, 0				#i = 0
		li $t2, DIM
		
ciclStp:lw $a0, ($t0)
		addi $t0, $t0, 4
		li $v0, 1
		syscall
		li $a0, '\n'
		li $v0, 11
		syscall
		
		addi $t1, $t1, 4		#i++
		bne $t1, $t2, ciclStp
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

	.ent calcola_sconto
calcola_sconto:	

		addi $sp, $sp, -12
		lw $s0, 8($sp)
		lw $s1, 4($sp)
		lw $s2, ($sp)
		
		li $v0, 0
		li $t5, 0				#i = 0
		lw $s0, 12($sp)			#$s0 = ARROTONDA
		li $s1, 100
		sub $s3, $s1, $a3
		
cicl:	lw $t1, ($a0)
		addi $a0, $a0, 4
		addi $t5, $t5, 1		#i++
		mul $t3, $t1, $s3
		div $t3, $t3, $s1
		mfhi $t2				#$t2 = resto
		beq $s0, $0, cnt
		blt $t2, 50, cnt 		#se resto < 50 NON approssimare per eccesso
		
fArrot:	addi $t3, $t3, 1
		
cnt:	sw $t3, ($a1)
		addi $a1, $a1, 4
		sub $t3, $t1, $t3
		add $v0, $v0, $t3
		bne $t5, $a2, cicl
		
		sw $s0, 8($sp)
		sw $s1, 4($sp)
		sw $s2, ($sp)
		addi $sp, $sp, 12
		
		jr $ra
		
.end calcola_sconto