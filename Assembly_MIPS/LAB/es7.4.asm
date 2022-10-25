.data



		.text
		.globl main
		.ent main
		
main:	addi $sp, $sp, -4
		sw $ra, ($sp)
		
		li $a0, 3
		li $a1, 8
		li $a2, 5
		li $a3, 4
		jal determinante2x2
		
		move $a0, $v0
		li $v0, 1
		syscall
		
		lw $ra, ($sp)
		addi $sp, $sp, 4
		
fine:	jr $ra					#fine
.end main

	.ent determinante2x2
determinante2x2:	
		
		mul $t0, $a0, $a3
		mul $t1, $a1, $a2
		sub $v0, $t0, $t1
		jr $ra
		
.end determinante2x2