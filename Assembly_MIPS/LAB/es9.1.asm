.data

DIM = 3
mat1:	.word 39, 1880, 2394, 1000, 1590, 39, -548, 2124, 31000
mat2:	.word 39, 1880, -547, 1000, 1590, 1456, 1880, 2394, 31999
result:	.space DIM * 4
I = 2

		.text
		.globl main
		.ent main
		
main:	la $a0, mat1
		la $a1, mat2
		la $a2, result
		li $a3, DIM
		li $t0, I
		addi $sp, $sp, -4
		sw $t0, ($sp)
		jal Variazione
		addi $sp, $sp, 4
		
STMP:	la $t0, result
		li $t1, 0				#i = 0
		li $t2, DIM
ciclStp:lw $a0, ($t0)
		addi $t0, $t0, 4
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

	.ent Variazione
Variazione:	
		
		lw $t5, ($sp)			#I
		mul $a3, $a3, 4
		mul $t6, $t5, $a3		#indice mat1
		mul $t7, $t5, 4		#indice mat2
		li $t0, 0				#indice quanti ne ho fatti
		
ciclo:	add $t1, $a0, $t6
		add $t2, $a1, $t7
		lw $t1, ($t1)
		lw $t2, ($t2)
		
var:	sub $t2, $t2, $t1
		mul $t2, $t2, 100
		div $t2, $t2, $t1
		
		sw $t2, ($a2)
		addi $a2, $a2, 4
		
		addi $t6, $t6, 4		#incrementa indice mat1
		add $t7, $t7, $a3		#incrementa indice mat2
		
		addi $t0, $t0, 4
		blt $t0, $a3, ciclo 
		
		jr $ra
		
.end Variazione