.data

		.text
		.globl main
		.ent main
		
main:	li $t0, 15
		li $t1, 16
		li $t2, 17
		li $t3, 18
		li $s0, 223
		li $s1, 224
		li $s2, 225
		li $s3, 226
		
		addi $sp, $sp, -16
		sw $t0, 12($sp)			#save $t0 in sp_originale[4]
		sw $t1, 8($sp)			#save $t1 in sp_originale[8]
		sw $t2, 4($sp)			#save $t2 in sp_originale[12]
		sw $t3, 0($sp)			#save $t3 in sp_originale[16]
		
		addi $sp, $sp, -8		#valori che dimentico dopo la chiamata jal somma
		sw $t0, 4($sp)			#save $t0 in sp_mod[4]
		sw $s0, 0($sp)
		
		move $a0, $sp			#scrivi in a0 l'indirizzo di sp[16], in cui c'è t3
		jal somma
		move $t4, $v0
		
		addi $sp, $sp, 8		#ho dato per persi i valori di sp_mod
		
		lw $t0, 12($sp)
		lw $t1, 8($sp)
		lw $t2, 4($sp)
		lw $t3, 0($sp)
		addi $sp, $sp, 16		#ho riprisitinato ogni cosa

		li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main


	.ent somma
somma:	
		addi $sp, $sp, -16
		sw $s0, 12($sp)
		sw $s1, 8($sp)
		sw $s2, 4($sp)
		sw $s3, 0($sp)
		
		move $t0, $0
		move $t1, $0
		move $t2, $0
		move $t3, $0
		move $t4, $0
		move $s0, $0
		move $s1, $0
		move $s2, $0
		move $s3, $0
		move $s4, $0
		lw $t2, 4($a0)			#scrivi in t2 sp_mod[4]
		lw $s2, 0($a0)			#scrivi in s2 sp_mod[8]
		add $v0, $t2, $s2
		
		lw $s0, 12($sp)
		lw $s1, 8($sp)
		lw $s2, 4($sp)
		lw $s3, 0($sp)
		addi $sp, $sp, 16
		
		j $ra
.end somma