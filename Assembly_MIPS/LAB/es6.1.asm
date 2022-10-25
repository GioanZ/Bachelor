.data

DIM = 3

		.text
		.globl main
		.ent main
		
main:	li $a1, 0
		jal stampaTriangolo
		li $a1, 0
		jal stampaQuadrato
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall							#fine
.end main

		.ent stampaTriangolo
stampaTriangolo:

		addi $a1, $a1, 1
		bgt $a1, DIM, avanti 
		add $t5, $0, $0
		
qtaT:	addi $t5, $t5, 1
		bgt $t5, $a1, aCapoT
		li $a0, '*'
		li $v0, 11				#stampa carattere
		syscall
		j qtaT
		
aCapoT:	li $a0, '\n'
		li $v0, 11				#stampa carattere
		syscall
		j stampaTriangolo
		
avanti:	li $a0, '\n'
		li $v0, 11				#stampa carattere
		syscall
		jr $ra
.end stampaTriangolo

.ent stampaQuadrato
stampaQuadrato:
		
		addi $a1, $a1, 1
		bgt $a1, DIM, avanti 
		add $t5, $0, $0
		
qtaQ:	addi $t5, $t5, 1
		bgt $t5, DIM, aCapoQ
		li $a0, '*'
		li $v0, 11				#stampa carattere
		syscall
		j qtaQ
		
aCapoQ:	li $a0, '\n'
		li $v0, 11				#stampa carattere
		syscall
		j stampaQuadrato
.end stampaQuadrato