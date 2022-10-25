.data

wMat:	.word   154, 123, 109, 86, 4, 0, 412, -23, -231, 9, 50, 0, 123, -24, 12, 55, -45, 0, 0, 0, 0, 0, 0, 0

		.text
		.globl main
		.ent main
		
main:	la $t0, wMat
		li $t3, 0
		li $t5, 0

iniz1:	li $t6, 0
		li $t3, 0
		
cicl1:	lw $t1, ($t0)
		add $t3, $t3, $t1
		addi $t0, $t0, 4
		addi $t6, 1
		blt $t6, 5, cicl1
		
		sw $t3, ($t0)
		addi $t0, $t0, 4
		
		addi $t5, 1
		blt $t5, 3, iniz1
		
		
		
		la $t0, wMat
		li $t6, 0

iniz2:	li $t5, 0
		li $t3, 0
		
cicl2:	lw $t1, ($t0)
		add $t3, $t3, $t1
		addi $t0, $t0, 24		#4*6
		addi $t5, 1
		blt $t5, 3, cicl2
		
		sw $t3, ($t0)
		
		la $t0, wMat			#torna a m[0][0] per poi prendere la colonna dopo
		addi $t6, $t6, 1
		mul $t7, $t6, 4
		add $t0, $t0, $t7
		
		blt $t6, 6, iniz2
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main