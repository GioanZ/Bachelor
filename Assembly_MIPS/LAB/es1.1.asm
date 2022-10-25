.data
n1:		.byte 10
n2:		.byte 0x10
n3:		.byte '1'
res:	.space 1	#prendi dello spazio di dimensione 1

		.text
		.globl main
		.ent main
		
main:	lb $t1, n1
		lb $t2,n2
		sub $t1,$t1,$t2
		lb $t2,n3
		add $t1, $t1, $t2
		
		sb $t1, res	#salva il risultato in memoria
		
		li $v0, 10	#codice per uscita dal programma
		syscall		#fine
		
		.end main