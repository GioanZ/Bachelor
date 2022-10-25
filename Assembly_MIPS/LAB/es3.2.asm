.data

msg:	.asciiz "Metti il numero:"
err:	.asciiz "Errore, non numero"
num:	.asciiz "Numero: "
ovflw:	.asciiz "Overflow"
sBy:	.asciiz "\nSta su 4 byte"
nBy:	.asciiz "\nNon sta su 4 byte"

		.text
		.globl main
		.ent main
		
main:	la $a0, msg
		li $v0, 4
		syscall
		
		add $t0, $0, $0
		add $s0, $0, 10
		addu $s1, $0, 0xFFFFFFFF
		
while:	li $v0, 12
		syscall
		move $t1, $v0
		beq $t1, '\n', stmp
		blt $t1, '0', error1
		bgt $t1, '9', error1
		
		#operazioni per trovare il numero
		sub $t1, $t1, '0'
		mult $s0, $t0
		mflo $t2
		mfhi $t3
		bne $t3, $0, error2
		addu $t0, $t2, $t1		#numero corrente
		bltu $t0, $t1, error2	#controllo che non ci sia stato overflow 
								#=> controllo che sia maggiore di entrambi i numeri
								
		j while
		
error1: la $a0, err
		li $v0, 4
		syscall
		j fine
		
error2: la $a0, ovflw
		li $v0, 4
		syscall
		j fine
		
stmp:	la $a0, num				#stampa testo inutile
		li $v0, 4
		syscall
		
		move $a0, $t0			#stampa numero acquisito
		li $v0, 1
		syscall
		
		bgtu $t0, $s1, noByte
		la $a0, sBy				#stampa che sta su 1 byte
		li $v0, 4
		syscall
		j fine
		
noByte:	la $a0, nBy				#stampa che non sta su 1 byte
		li $v0, 4
		syscall
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main