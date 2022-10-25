.data

message: .asciiz "Inserisci un numero intero positivo, io ti diro' se il valore e' pari o dispari: "
msgPari: .asciiz "E' pari"
msgDisp: .asciiz "E' dispari"

		.text
		.globl main
		.ent main
		
main:	la $a0, message 		#salva messaggio
		li $v0, 4				#stampa messaggio
		syscall
		
		li $v0, 5				#leggi intero
		syscall
		move $t1, $v0			#prendi il intero letto e mettilo in $t1
		
		andi $t1, $t1, 1		#facendo AND mette in $t1 0 se e' pari, se no e' dispari
		
		beq $t1, 0, pari		#se $t1 == 0 allora è pari
		j dispari
		
pari:	
		la $a0, msgPari		 	#salva messaggio
		li $v0, 4				#stampa messaggio
		syscall
		j fine
		
dispari:
		la $a0, msgDisp			#salva messaggio
		li $v0, 4				#stampa messaggio
		syscall

fine:
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
		.end main