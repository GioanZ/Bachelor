.data

msg:	.asciiz "Metti il numero:"
err:	.asciiz "Errore, non numero"
		.text
		.globl main
		.ent main
		
main:	la $a0, msg
		li $v0, 4
		syscall
		
		add $t0, $0, '0'
		add $t1, $0, '9'
		add $t2, $0, '\n'
		
while:	li $v0, 12
		syscall
		move $t3, $v0
		beq $t3, $t2, fine
		ble $t3, $t0, errore
		bge $t3, $t1, errore
		j while
		
errore: la $a0, err
		li $v0, 4
		syscall
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main