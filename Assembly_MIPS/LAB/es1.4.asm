.data

var: .word 0x3FFFFFF0

		.text
		.globl main
		.ent main
		
main:	lw $t1, var
		add $t1, $t1, $t1
		
		#la $a0, ($t1)
		addi $a0, $t1, 0
		li $v0, 1				#perché non va bene 4 al posto di 1?????
		syscall
		
		addiu $t3, $t1, 40
		la $a1, ($t3)
		li $v0, 1
		syscall
		
		#li $v0, 1				# E’ possibile stampare un risultato numerico?
		#syscall
		
		addi $t2, $0, 40
		addu $a2, $t1, $t2
		li $v0, 1
		syscall
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
		.end main