.data

msg:	.asciiz "Metti parola: "

		.text
		.globl main
		.ent main
		
main:	la $a0, msg
		li $v0, 4
		syscall	
		
		addi $t1, $0, 'a'
		addi $t2, $0, 'A'
		sub $a1, $t1, $t2
		
acq:	li $v0, 12
		syscall
		move $a0, $v0
		
		beq $a0, '\n', fine
		
		jal conv
		move $a0, $v0
		li $v0, 11
		syscall
		j acq
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

.ent conv
conv:	
		addi $t0, $0, 'Z'
		blt $t0, $a0, cmb		#se 'Z' < $a0
		bgt $t0, $a0, nFN
cnt:	jr $ra
		
cmb:	sub $v0, $a0, $a1
		j cnt
		
nFN:	move $v0, $a0
		j cnt
.end conv