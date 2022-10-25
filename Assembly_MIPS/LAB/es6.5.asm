.data

n = 6
k = 3

		.text
		.globl main
		.ent main
		
main:	li $a0, n
		li $a1, k
		jal combina
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

.ent combina
combina:	

		move $t0, $a0			#t0 = n
		move $t1, $a1			#t1 = k
		li $t5, 1				#n - t5
		move $t2, $a0			#NUM: t2
num:	addi $t0, $t0, -1
		bge $t5, $t1, den		#se t5 >= t1 salta
		
		mul $t2, $t2, $t0		#n*(n-1)*(n-2)*...
		addi $t5, $t5, 1
		j num
		
den:	move $t3, $t1			#DEN: t3
		
fatt:	addi $t1, $t1, -1
		ble $t1, 1, clc
		
		mul $t3, $t3, $t1
		j fatt
		
clc:	div $v0, $t2, $t3		
		jr $ra
		
.end combina