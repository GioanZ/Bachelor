.data

DIM = 5
#m:		.word 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 5
m:		.word 1, 4, 5, 6, 7, 4, 2, 8, 6, 4, 5, 8, 3, 2, 9, 6, 6, 2, 4, 4, 7, 4, 9, 4, 5
#m:		.word 1, 4, 5, 6, 7, 4, 2, 8, 6, 4, 5, 8, 3, 2, 9, 6, 6, 2, 4, 4, 7, 4, 9, 40, 5

		.text
		.globl main
		.ent main
		
main:	la $s0, m
		li $t5, 2				#fino a prova contaria è diagonale
		li $t6, -1				#riga_colonna = -1
		li $s1, 4
		
		
comin:	addi $t6, $t6, 1		#riga_colonna++
		beq $t6, DIM, fMat
		add $t7, $t6, $0
		
ciclo:	addi $t7, $t7, 1		#colonna[t7] in riga[t6] e riga[t7] in colonna[t6]
		beq $t7, DIM, comin
		
		mul $t8, $t6, DIM		#t8 sa la riga corrente
		mul $t8, $t8, $s1		#t8 = num prima cella della riga 
		
R:		mul $t1, $t7, $s1		#t1 sa la colonna  
		add $t1, $t1, $t8		#colonna + riga
		add $t9, $t1, $s0
		lw $t3, ($t9)			#t3 = m[0][t1]
		
C:		mul $t2, $t7, DIM		#t2 sa la riga 
		mul $t2, $t2, $s1		#t2 sa la posizione della cella nella matrice R*4*5
		mul $t8, $t6, $s1 		#t8 sa la colonna
		add $t2, $t2, $t8		
		add $t9, $t2, $s0
		lw $t4, ($t9)			#t4 = m[][0]
		
		bne $t3, $t4, nulla
		beq $t3, $0, ciclo		#se è diagonale no problem, ricomincia il ciclo
		li $t5, 1				#matrice simmetrica
		j ciclo
		
		
nulla:	li $t5, 0				#matrice brutta
		
fMat:	move $a0, $t5
		li $v0, 1
		syscall
		j fine
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main
