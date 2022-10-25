.data

var1:	.byte 7
var2:	.byte 6
var3:	.byte 5
result:	.word 0

		.text
		.globl main
		.ent main
		
main:	add $s0, $0, 24
		add $s1, $0, 60
		
		lb $t1, var1
		lb $t2, var2
		lb $t3, var3
		
		mult $t1, $s0
		mflo $t4
		add $t0, $t4, $t2		#le ore totali
		
		mult $t0, $s1
		mflo $t4
		add $t0, $t4, $t3		#i minuti

		sw $t0, result
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main