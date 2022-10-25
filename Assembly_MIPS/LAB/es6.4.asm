.data

DIM = 6
vet:	.word 1, 4, 7, 40, 40, 6

		.text
		.globl main
		.ent main
		
main:	la $a0, vet
		li $a1, DIM
		jal massimo
		move $a0, $v0
		li $v0, 1
		syscall
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

.ent massimo
massimo:
		
		move $t0, $a0
		add $t5, $0, $0
		lw $t2, ($t0)
		addi $t0, $t0, 4
ciclo:	addi $t5, $t5, 2
		bgt $t5, $a1, torna
		lw $t1, ($t0)
		addi $t0, $t0, 4
		blt $t1, $t2, cnt
		move $t2, $t1
cnt:	j ciclo
torna:	move $v0, $t2
		jr $ra
.end massimo