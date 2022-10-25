.data

op1:	.byte 150
op2:	.byte 100


		.text
		.globl main
		.ent main
		
main:	lbu $t0, op1			#per salvare senza segno uso lbu
		lb $t1, op2
		
		add $a0, $t0, $t1
		
		li $v0 1
		syscall
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
		.end main