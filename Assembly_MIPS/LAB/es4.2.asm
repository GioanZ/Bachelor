.data

opa:	.word 2043
opb:	.word 5
res:	.space 4

tab:	.word somma, sottrazione, moltiplic, divisione
msg:	.asciiz "Metti numero: "
msg2:	.asciiz "Devi mettere un numero tra 0 e 3\n"

		.text
		.globl main
		.ent main
		
main:	la $t2, opa				#salva indirizzo di opa in $t2
		lw $t2, 0($t2)			#salva il contenuto dell'indirizzo $t2 + 0 in $t2
		
		la $t3, opb
		lw $t3, 0($t3)
		
acq:	la $a0, msg				#stampa msg
		li $v0, 4
		syscall
		
		li $v0, 5
		syscall
		move $t0, $v0			#scanf int in tmp
		
		add $t1, $0, 0
		bgt $t1, $t0, err 
		add $t1, $0, 3
		blt $t1, $t0, err
		
		mul $t0, $t0, 4
		
switch:	lw $t0, tab($t0)		#scrivi in t0 quel che è scritto all'indirizzo: tab + t0
		jr $t0
		
err:	la $a0, msg2			#stampa msg2
		li $v0, 4
		syscall
		
		j acq
		
somma:	
		add $t4, $t2, $t3
		j resul
sottrazione:
		sub $t4, $t2, $t3
		j resul
moltiplic:		
		mul $t4, $t2, $t3
		j resul
divisione:	
		div $t4, $t2, $t3
		#div $t2, $t3
		#mflo $t4				#prendi quoziente
		
resul:	la $t5, res				#salva indirizzo di res in $t5
		sw $t4, ($t5)			#scrive $t4 dentro l'indirizzo $t5 
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main