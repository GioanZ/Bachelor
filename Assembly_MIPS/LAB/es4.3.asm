.data

DIMW = 4
R = 4 
C = 4 
vet1:	.word 1, 2, 3, 4
vet2:	.word 5, 6, 7, 8
mat:	.space R*C*DIMW			#4 colonne, 4 righe, con 4 spazi, dato che sono word
spaz:	.asciiz " "
aCapo:	.asciiz "\n"

		.text
		.globl main
		.ent main
		
main:	la $t5, vet1			#salva indirizzo x, i=0
		li $t4, 0				#i=0
		
		la $t0, mat				#salva indirizzo
		
for1:	la $t6, vet2			#salva indirizzo y, j=0
		li $t7, 0				#j=0
		
		lw $t1, ($t5)			#x_i = x[i]
		
for2:	lw $t2, ($t6)			#y_j = y[j]
		mul $t3, $t1, $t2		#x_i * y_j
		sw $t3, ($t0)			#scrivi risultato in mat[i][j]
		
		lw $a0, ($t0)			#scrive in $a0 quello che c'è scritto all'indirizzo di $t0
		li $v0, 1
		syscall
		la $a0, spaz			#stampa spazio
		li $v0, 4
		syscall
		
		add $t0, $t0, DIMW		#[i][j]++
		
		add $t6, $t6, DIMW		#j++
		addi $t7, $t7, 1 
		blt $t7, C, for2
		
		la $a0, aCapo			#stampa \n
		li $v0, 4
		syscall
		add $t5, $t5, DIMW		#i++
		addi $t4, $t4, 1 
		blt $t4, R, for1
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main