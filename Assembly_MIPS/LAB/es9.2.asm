.data

str_orig: .asciiz "% nella citta' dolente, % nell'eterno dolore, % tra la perduta gente"
str_sost: .asciiz "per me si va"
str_new: .space 200


		.text
		.globl main
		.ent main
		
main:	la $a0, str_orig
		la $a1, str_sost
		la $a2, str_new
		jal sostituisci
		
		move $a0, $v0
		li $v0, 1
		syscall
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

	.ent sostituisci
sostituisci:

		
		li $t6, 0x00
		li $t5, 0
		move $t0, $a0
		move $t2, $a2
		
cont:	lb $t3, ($t0)
		addi $t0, $t0, 1
		beq $t3, 0x00, torna
		bne $t3, '%', copia
		
		move $t1, $a1
sost:	lb $t3, ($t1)
		beq $t3, $t6, cont
		sb $t3, ($t2)
		addi $t5, $t5, 1
		addi $t2, $t2, 1
		addi $t1, $t1, 1
		j sost
		
copia:	sb $t3, ($t2)
		addi $t5, $t5, 1
		addi $t2, $t2, 1
		j cont
		
torna:	sb $t6, ($t2)
		move $v0, $t5
		jr $ra		
		
.end sostituisci
#per me si va nella citta' dolente, per me si va nell'eterno dolore, per me si va tra la perduta gente