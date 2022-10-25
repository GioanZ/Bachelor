.data

DIM:	.word 4
msg:	.asciiz "immetti i numeri:\n"
msg2:	.asciiz "quoziente: "

		.text
		.globl main
		.ent main
		
main:	add $t0, $0, $0			#x = 0
		add $t1, $0, $0			#i = 0
		lw $t3, DIM				#$t3 = DIM
		la $a0, msg
		li $v0, 4
		syscall
		
for:	li $v0, 5
		syscall
		move $t2, $v0			#scanf int in tmp
		
		add $t0, $t0, $t2		#x += tmp
		add $t1, $t1, 1			#i++
		
		blt $t1, $t3, for		#if $t1 < DIM vai al for
		
		la $a0, msg2
		li $v0, 4
		syscall
		
		div $t0, $t3
		mflo $a0				#prendi quoziente
		
		li $v0, 1
		syscall
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main