.data

var1:	.byte 2
VAR1:	.word 3
VAR2:	.word 6
VAR3:	.space 4

		.text
		.globl main
		.ent main
		
main:	#CAMBIA SEGNO DI VAR1 e scrivilo in VAR2
		lw $t0, VAR1
		li $t1, 0x80000
		xor $t0, $t0, $t1
		sw $t0, VAR2


lw $t1, VAR2

fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main
