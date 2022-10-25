.data

msg:	.asciiz "Metti il numero: "
noPal:	.asciiz "Il numero NON è palindormo"
siPal:	.asciiz "Il numero è palindormo"

		.text
		.globl main
		.ent main
		
main:	la $a0, msg
		li $v0, 4
		syscall
		
		li $t5, 0				#i=0
		move $t0, $sp			#così mi salvo indirizzo stack[-1]
		li $t4, 2
		
acq:	li $v0, 12
		syscall
		
		beq $v0, '\n', fNumer
		
		subu $sp, $sp, 4
		sw $v0, ($sp)
		addi $t5, $t5, 1		#i++
		
		j acq
		
fNumer:	div $t5, $t5, $t4		#i/2

oss:	ble $t5, $zero, siP		#se i <= 0 è palindormo
		
		addi $t0, $t0, -4
		lw $t1, ($t0)			#scrive in $t1 quello che c'è scritto all'indirizzo di $t0
		
		lw $t2, ($sp)
		addu $sp, $sp, 4
		addi $t5, $t5, -1		#i--
		
		bne $t1, $t2, noP
		j oss
		
noP:	la $a0, noPal
		li $v0, 4
		syscall
		j fine

siP:	la $a0, siPal
		li $v0, 4
		syscall
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main