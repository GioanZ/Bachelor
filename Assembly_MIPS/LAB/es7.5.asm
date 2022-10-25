.data

mat:	.word  	2, 3, 4, 4, 1, 6, 9, 7, 4

		.text
		.globl main
		.ent main
		
main:	addi $sp, $sp, -4
		sw $ra, ($sp)
		
		la $t1, mat
		lw $a0, 0($t1)
		lw $a1, 4($t1)
		lw $a2, 8($t1)
		lw $a3, 12($t1)
		addi $sp, $sp, -20
		lw $t0, 16($t1)
		sw $t0, 16($sp)
		lw $t0, 20($t1)
		sw $t0, 12($sp)
		lw $t0, 24($t1)
		sw $t0, 8($sp)
		lw $t0, 28($t1)
		sw $t0, 4($sp)
		lw $t0, 32($t1)
		sw $t0, 0($sp)
		jal determinante3x3
		
		addi $sp, $sp, 20
		
		move $a0, $v0
		li $v0, 1
		syscall
		
		lw $ra, ($sp)
		addi $sp, $sp, 4
		
fine:	jr $ra					#fine
.end main


	.ent determinante3x3
determinante3x3:	
		
		move $s3, $ra
		
		move $t0, $a0
		move $t1, $a1
		move $t2, $a2
		move $t3, $a3
		lw $t4, 16($sp)
		lw $t5, 12($sp)
		lw $t6, 8($sp)
		lw $t7, 4($sp)
		lw $t8, 0($sp)
		
		move $a0, $t4
		move $a1, $t5
		move $a2, $t7
		move $a3, $t8
		
		jal determinante2x2
		mul $t9, $v0, $t0
		add $s0, $t9, $0
		
		move $a0, $t3
		move $a1, $t5
		move $a2, $t6
		move $a3, $t8
		
		jal determinante2x2
		mul $t9, $v0, $t1
		sub $s0, $s0, $t9
		
		move $a0, $t3
		move $a1, $t4
		move $a2, $t6
		move $a3, $t7
		
		jal determinante2x2
		mul $t9, $v0, $t2
		add $s0, $s0, $t9
		
		move $ra, $s3
		
		move $v0, $s0
		
		jr $ra
		
.end determinante3x3


	.ent determinante2x2
determinante2x2:	
		
		mul $s1, $a0, $a3
		mul $s2, $a1, $a2
		sub $v0, $s1, $s2
		jr $ra
		
.end determinante2x2