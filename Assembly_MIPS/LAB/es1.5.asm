.data
var: 	.word 0x3FFFFFF0

		.text
		.globl main
		.ent main
		
main:	lw $t0, var
		add $t1, $t0, $t0 	# prima somma
		
		move $a0, $t1
		li $v0, 1
		syscall
		
		addiu $a0, $t1, 40 	# seconda somma (addi genera eccezione)
		li $v0, 1
		syscall 			# syscall assume che il valore in $a0 sia
							# in CA2; per stampare unsigned bisognerebbe
							# scrivere un’opportuna procedura
							
		li $t2, 40 			# terza somma
		addu $a0, $t1, $t2 	# (add genera eccezione)
		li $v0, 1
		syscall
		
		li $v0, 10
		syscall
		.end main