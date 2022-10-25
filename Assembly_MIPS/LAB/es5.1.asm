.data

var:	.word 3141592653

		.text
		.globl main
		.ent main
		
main:	lw $t0, var
		
		li $t1, 10
		addi $t5, $0, '0'		#per ascii
		li $t6, 0				#contatore i = 0
		
while:	divu $t0, $t0, $t1
		mfhi $t2
		
		add $t2, $t2, $t5		#per rendere il numero in codice ascii
		
		subu $sp, $sp, 4
		sw $t2, ($sp)
		addi $t6, $t6, 1		#i++
		bne $t0, $0, while
		
while2:	lw $a0, ($sp)
		addu $sp, $sp, 4
		
		li $v0, 11
		syscall
		
		addi $t6, $t6, -1		#i--
		bne $t6, $0, while2
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main