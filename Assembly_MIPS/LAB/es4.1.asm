.data

DIM = 20
vet:	.space DIM*4				#perché 20 numeri di tipo word
aCapo:	.asciiz "\n"

		.text
		.globl main
		.ent main
		
main:	addi $t1, $0, 1			#v[i-1]			
		addi $t2, $0, 0			#v[i-2]
		addi $t3, $0, 0			#variabile di appoggio
		addi $t4, $0, 1			#contatore
		
		la $t0, vet				#indirizzo del vettore in $t0
		sw $t1 ($t0)			#scrivo in vet[0] = 1, SERVE $T1 PERCHé SW PRENDE SOLO DAI REGISTRI
		
		lw $a0, ($t0)			#scrive in $a0 quello che c'è scritto all'indirizzo di $t0
		li $v0, 1				#stampa numero acquisito
		syscall
		la $a0, aCapo			#stampa \n
		li $v0, 4
		syscall
		
fibon:	add $t0, $t0, 4			#ora $t0, punta vett[quello di prima + 1]
		add $t3, $t1, $t2		#vet[i] = vet[i-1] + vet[i-2]
		sw $t3 ($t0)			#scrivo in vet[i] = t3	
		
		add $t2, $t1, $0		#t2 = v[i-1] + 0
		add $t1, $t3, $0		#t1 = v[i] + 0
		add $t4, $t4, 1			#incremento variabile
		
		lw $a0, ($t0)			#scrive in $a0 quello che c'è scritto all'indirizzo di $t0
		li $v0, 1				#stampa numero acquisito
		syscall
		
		la $a0, aCapo			#stampa \n
		li $v0, 4
		syscall
		
		bne $t4, DIM, fibon		#if(i != 20) ricomincia ciclo
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main 