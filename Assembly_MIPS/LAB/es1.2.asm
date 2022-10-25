.data

var1:		.byte 'm'
var2:		.byte 'i'
var3:		.byte 'p'
var4:		.byte 's'
var5:		.byte 0
tmp1:		.byte 'A'
tmp2:		.byte 'a'
		.text
		.globl main
		.ent main
		
main:	lb $t1, tmp1
		lb $t2, tmp2
		sub $t1, $t1, $t2		#'A' - 'a'
		
		lb $t2, var1
		add $t2, $t2, $t1
		sb $t2, var1 
		
		lb $t2, var2
		add $t2, $t2, $t1
		sb $t2, var2  
		
		lb $t2, var3
		add $t2, $t2, $t1
		sb $t2, var3
		
		lb $t2, var4
		add $t2, $t2, $t1
		sb $t2, var4
		
		li $v0, 4
		la $a0, var1
		syscall
		
		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
		.end main