.data

msg:	.asciiz "Inserisci dimensione: "

		.text
		.globl main
		.ent main
		
main:	la $a0, msg
		li $v0, 4
		syscall	
		
		li $v0, 5
		syscall	
		move $s1, $v0			#scanf int in tmp
		
		move $a0, $s1
		li $a1, 0
		jal stampaTriangolo
		
		move $a0, $s1
		li $a1, 0
		jal stampaQuadrato
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall							#fine
.end main

.ent stampaTriangolo
stampaTriangolo:

		move $s0, $a0
		
ciclo1:	addi $a1, $a1, 1
		bgt $a1, $s0, avanti 
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
		j ciclo1
		
avanti:	li $a0, '\n'
		li $v0, 11				#stampa carattere
		syscall
		jr $ra
.end stampaTriangolo

.ent stampaQuadrato
stampaQuadrato:
		
		move $s0, $a0
		
ciclo2:	addi $a1, $a1, 1
		bgt $a1, $s0, avanti 
		add $t5, $0, $0
		
qtaQ:	addi $t5, $t5, 1
		bgt $t5, $s0, aCapoQ
		li $a0, '*'
		li $v0, 11				#stampa carattere
		syscall
		j qtaQ
		
aCapoQ:	li $a0, '\n'
		li $v0, 11				#stampa carattere
		syscall
		j ciclo2
.end stampaQuadrato