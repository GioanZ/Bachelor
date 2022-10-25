.data



		.text
		.globl main
		.ent main
		
main:	
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

	.ent somma
somma:	
		
.end somma
###############################################################################

		li $t1, 0				#scrivere un immediato in $t1, load immediate (tipo usare add, move ecc)
		
		
msg:	.asciiz "Metti numero: "
		la $a0, msg				#stampa msg
		li $v0, 4
		syscall
		
		
		li $v0, 5
		syscall
		move $t2, $v0			#scanf int in tmp
		
		
		li $v0, 5
		syscall
		blt $v0, 0, errore		#così controlli subito cosa hai acquisito
		
		
		lw $a0, ($t0)			#scrive in $a0 quello che c'è scritto all'indirizzo di $t0
		li $v0, 1				#stampa numero acquisito
		syscall
		
		
		div $t0, $t3
		mflo $a0				#prendi quoziente
		
		
opa:	.word 2043
		la $t2, opa				#salva indirizzo di opa in $t2
		lw $t2, 0($t2)			#salva il contenuto dell'indirizzo $t2 + 0 in $t2
		
		
result:	.space 4		
		la $t5, result			#salva indirizzo di result in $t5
		sw $t4, ($t5)			#scrive $t4 dentro l'indirizzo $t5 
		
		
tab:	.word somma, sottrazione, moltiplic, divisione
switch:	lw $t0, tab($t0)		#scrivi in t0 quel che è scritto all'indirizzo: tab + t0
		jr $t0					#j è quando hai un immediato, tipo j resul
		
		
STMP:	la $t0, scont
		li $t1, 0				#i = 0
		li $t2, DIM
ciclStp:lw $a0, ($t0)
		addi $t0, $t0, 4
		li $v0, 1
		syscall
		li $a0, '\n'
		li $v0, 11
		syscall
		addi $t1, $t1, 1		#i++
		bne $t1, $t2, ciclStp

per la matrice es4.3.asm
			

#Stack		
	#Per inserire un dato si effettua una push:		
		subu $sp, $sp, 4
		sw $t0, ($sp)
		addi $t6, $t6, 1		#i++
	#Per prelevare un dato si effettua una pop:
		lw $t0, ($sp)
		addu $sp, $sp, 4
		addi $t6, $t6, -1		#i--
	

		move $t0, $sp			#così mi salvo indirizzo stack[-1]

		
		addi $t5, $0, '0'
		
		
diffofsums:
		addi $sp, $sp, -12 		# make space on stack
								# to store 3 registers
		sw $s0, 8($sp) 			# save $s0 on stack
		sw $t0, 4($sp) 			# save $t0 on stack
		sw $t1, 0($sp) 			# save $t1 on stack
		add $t0, $a0, $a1 		# $t0 = f + g
		add $t1, $a2, $a3 		# $t1 = h + i
		sub $s0, $t0, $t1 		# result = (f + g) - (h + i)
		add $v0, $s0, $0 		# put return value in $v0
		lw $t1, 0($sp) 			# restore $t1 from stack
		lw $t0, 4($sp) 			# restore $t0 from stack
		lw $s0, 8($sp) 			# restore $s0 from stack
		addi $sp, $sp, 12 		# deallocate stack space
		jr $ra 					# return to caller
		
		
		
		
####################################################################
#come leggere carattere per carattere 
stringa1: .asciiz "Calcolatori Elettronici 2019/2020" 

	la $a0, stringa1 			#salva in $a0 l'indirizzo di stringa1

	lb $t1, ($a0)				#leggi lettera a quell'indirizzo
	beq $t1, 0x00, fineExam		#se è finita la stringa finisci
		
####################################################################
#come leggere/scrivere un VAR
VAR1:	.word 5	
VAR3:	.space 4	
		
	lw $t1, VAR1				#$t1 = leggi cosa c'è all'indirizzo VAR1
	sw $t0, VAR3				#scrive all'indirizzo VAR3 $t0


####################################################################
#come salvare nello stack
.ent PROCE
PROCE:
	addi $sp, $sp, -24
	sw $ra, ($sp) 
	sw $s0, 4($sp) 
	sw $s1, 8($sp) 
	sw $s2, 12($sp) 
	sw $s3, 16($sp) 
	sw $s4, 20($sp) 
...
	lw $ra, ($sp) 
	lw $s0, 4($sp) 
	lw $s1, 8($sp) 
	lw $s2, 12($sp) 
	lw $s3, 16($sp) 
	lw $s4, 20($sp) 
	addi $sp, $sp, 24 
	jr $ra
	.end PROCE
	
#oppure registri $t
...
	addi $sp, $sp, -4
	sw $t0, 0($sp)
	jal PROCEDURA
	lw $t0, 0($sp)
	addi $sp, $sp, 4
...	
	
####################################################################
#come salvare nello stack
	