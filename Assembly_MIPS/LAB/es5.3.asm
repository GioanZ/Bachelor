.data

#var1:	.byte -2
var1:	.byte 2
var2:	.byte 3
var3:	.byte 4
sSolR:	.asciiz "Soluzione reale"
nSolR:	.asciiz "Soluzione NON reale"

		.text
		.globl main
		.ent main
		
main:	lb $t1, var1
		lb $t2, var2
		lb $t3, var3
		
		#NB solzuione reale <=> delta >= 0
		#b^2 - 4*a*c
		
		mul $t2, $t2, $t2		#b^2
		li $t4, 4
		mul $t4, $t1, $t4		#4*a
		mul $t4, $t3, $t4		#4*a*c
		sub $t4, $t2, $t4		#operazione finale
		
		slt $t5, $t4, $0		#se t4 < 0 allora t5 = 1, else = 0
		
		beq $t5, $0, siR
		
		la $a0, nSolR
		li $v0, 4
		syscall
		bne $t5, $0, fine

siR:	la $a0, sSolR
		li $v0, 4
		syscall
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main