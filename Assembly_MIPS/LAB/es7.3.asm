.data

sequ:	.word 19

		.text
		.globl main
		.ent main
		
main:	lw $a0, sequ
		jal sequenzaDiCollatz
		
		move $a0, $v0
		li $v0, 1
		syscall
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main


	.ent sequenzaDiCollatz
sequenzaDiCollatz:
		
		li $s1, 1
		addi $sp, $sp, -4
		sw $ra, ($sp)
		
		add $v0, $s1, $0
		
ciclo:	beq $a0, $s1, ritorn
		addi $v0, $v0, 1		#i++
		addi $sp, $sp, -4		#alloca
		sw $v0, ($sp)			#salva in stack
		
		jal calcolaSuccessivo
		move $a0, $v0
		
		lw $v0, 0($sp)			
		addi $sp, $sp, 4

		j ciclo
		
ritorn:	lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
		
.end sequenzaDiCollatz


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