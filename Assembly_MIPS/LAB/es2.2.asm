.data

message: .asciiz "Inserisci un numero intero positivo: "
errB1: .asciiz "Errore primo numero"
errB2: .asciiz "Errore secondo numero"
var:	.word 0xFFFFFF00

		.text
		.globl main
		.ent main
		
main:	la $a0, message 		#stampa messaggio
		li $v0, 4				#stampa messaggio
		syscall
		
		li $v0, 5				#leggi primo intero
		syscall
		move $t1, $v0			#prendi il numero letto e mettilo in $t1
		
		la $a0, message 		
		li $v0, 4				#stampa messaggio
		syscall
		
		li $v0, 5				#leggi secondo intero
		syscall
		move $t2, $v0			#prendi il numero letto e mettilo in $t2
		
		lw $t0, var				#metti in $t0 1111 1111 1111 1111 1111 1111 0000 0000
		
controllaByte1:					#controlla se è un byte, se è 1 byte allora è 0000 0000 0000 0000 0000 0000 XXXX XXXX
		and $t6, $t1, $t0		#quindi facendo AND 0*X = 0; 1*0 = 0; => mi darà 0
		bne $t6, $0, errBy1		#se t6 != 0 non è 1 byte => errore
		
controllaByte2:					#come sopra
		and $t6, $t2, 0xFFFFFF00
		bne $t6, $0, errBy2		#se t6 != 0 non è 1 byte => errore
		
								#OSS andi $t6, $t2, 0xFFFFFF00 non posso farlo perché è I-Type, quindi 0xFFFFFF00 ha 32 bit e max ne supporta 16
								#quindi usi AND normale
		
opera:							#C = NOT(A AND (NOT(B))) OR (A XOR B)
		xor $t3, $t1, $t2 		#A XOR B
		nor $t4, $t2, $0		#NOT(B)
		and $t5, $t1, $t4		#A AND (NOT(B))
		nor $t5, $t5, $0		#NOT(A AND (NOT(B)))
		or $t5, $t5, $t3		#NOT(A AND (NOT(B))) OR (A XOR B)
		
		add $a0, $t5, $0		#stampa a video numero ottenuto
		li $v0, 1				#stampa messaggio
		syscall
		j fine
		
errBy1:	la $a0, errB1	 		#stampa errore
		li $v0, 4				#stampa messaggio
		syscall
		j fine
		
errBy2:	la $a0, errB2	 		#stampa errore
		li $v0, 4				#stampa messaggio
		syscall
		
fine:
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
		.end main