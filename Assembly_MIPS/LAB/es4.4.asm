.data

DIMW = 4
R = 10
C = 10 

mat:	.space R*C*DIMW			#C colonne, R righe, con 4 spazi, dato che sono word
spaz:	.asciiz " "
aCapo:	.asciiz "\n"

		.text
		.globl main
		.ent main
		
main:	la $t0, mat

		li $t1, 0
		li $t5, 0
		
for1:	li $t6, 2				#j=2
		addi $t1, $t1, 1
		sw $t1, ($t0)
		
		lw $a0, ($t0)			#scrive in $a0 quello che c'è scritto all'indirizzo di $t0
		li $v0, 1
		syscall
		la $a0, spaz			#stampa spazio
		li $v0, 4
		syscall
		
		add $t0, $t0, DIMW
		
		add $t3, $t1, $t1
		sw $t3, ($t0)
		
		lw $a0, ($t0)			#scrive in $a0 quello che c'è scritto all'indirizzo di $t0
		li $v0, 1
		syscall
		la $a0, spaz			#stampa spazio
		li $v0, 4
		syscall
		
		add $t0, $t0, DIMW
		
for2:	add $t3, $t3, $t1
		sw $t3, ($t0)
		
		lw $a0, ($t0)			#scrive in $a0 quello che c'è scritto all'indirizzo di $t0
		li $v0, 1
		syscall
		la $a0, spaz			#stampa spazio
		li $v0, 4
		syscall
		
		add $t0, $t0, DIMW
		
		addi $t6, $t6, 1		#j++ 
		blt $t6, C, for2
		
		la $a0, aCapo			#stampa \n
		li $v0, 4
		syscall
		addi $t5, $t5, 1		#i++
		blt $t5, R, for1
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main