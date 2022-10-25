RIGHE = 9
COLONNE = 9
#RIGHE = 2
#COLONNE = 2
N = 14
.data

mat: 	.byte 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
#mat: 	.byte 	0, 1, 1, 1
result:	.space RIGHE*COLONNE

		.text
		.globl main
		.ent main
		
main:	addi $sp, $sp, -4
		sw $ra, ($sp)
		
		la $s0, mat
		la $s1, result
		li $s2, 0
		
		move $a1, $s0
		li $a2, RIGHE
		li $a3, COLONNE
		jal stampaMatrice
		addi $s2, $s2, 1
		
dopo:	bgt $s2, N, fine
		move $a0, $s0
		move $a1, $s1
		li $a2, RIGHE
		li $a3, COLONNE
		jal evoluzione
		addi $s2, $s2, 1
		
stmp:	move $a1, $s1
		li $a2, RIGHE
		li $a3, COLONNE
		jal stampaMatrice
change:	move $t0, $s0
		move $s0, $s1
		move $s1, $t0		
		j dopo
		
fine:	lw $ra, ($sp)
		addi $sp, $sp, 4
		jr $ra
.end main


#	CREDOOOO	$a1 = indirizzo della matrice;	$a2 = RIGHE;	$a3 = COLONNE
	.ent stampaMatrice
stampaMatrice:
		
		
		li $t5, 0				# t5 == i
		move $t0, $a1
		
rig:	bge $t5, $a2, rit
		li $t6, 0				# t6 == j
colon:	bge $t6, $a3, finC
		lb $a0, ($t0)
		li $v0, 1
		syscall
		li $a0, ' '
		li $v0, 11
		syscall
		addi $t0, $t0, 1
		addi $t6, $t6, 1		#j++
		j colon
		
finC:	li $a0, '\n'
		li $v0, 11
		syscall
		addi $t5, $t5, 1		#i++
		j rig
		
rit:	li $a0, '\n'
		li $v0, 11
		syscall
		li $a0, '\n'
		li $v0, 11
		syscall
		jr $ra
.end stampaMatrice



	.ent evoluzione
evoluzione:	
		
		
		addi $sp, $sp, -28
		sw $ra, ($sp)
		sw $s0, 4($sp)
		sw $s1, 8($sp)
		sw $s2, 12($sp)
		sw $s3, 16($sp)
		sw $s4, 20($sp)
		sw $s5, 24($sp)
		
		move $s4, $a0
		move $s5, $a1			# s5 = result
		move $s2, $a2
		move $s3, $a3
		li $s0, 0
		mul $s1, $a3, $a2
		
itera:	bge $s0, $s1, close
		move $a0, $s4
		move $a1, $s0
		move $a2, $s2
		move $a3, $s3
		jal contaVicini
		
		li $t1, 0
		beq $v0, 3, caric1
		add $t0, $s4, $s0
		lb $t0, ($t0)
		bne $t0, 1, cFin
viv:	bne $v0, 2, cFin
		
caric1:	li $t1, 1

cFin:	sb $t1, ($s5)
		addi $s5, $s5, 1
		addi $s0, $s0, 1
		j itera
		
close:	lw $ra, ($sp)
		lw $s0, 4($sp)
		lw $s1, 8($sp)
		lw $s2, 12($sp)
		lw $s3, 16($sp)
		lw $s4, 20($sp)
		lw $s5, 24($sp)
		addi $sp, $sp, 28
		jr $ra
.end evoluzione



	.ent contaVicini
contaVicini:	
		
		
sx:		li $t8, 0
		div $a1, $a3
		mfhi $t0				#se t0 <= 0 sei al lato a SX
		ble $t0, $0, dx
		li $t8, 1				#se t8 == 1 NON è al lato SX
		
dx:		li $t9, 0
		addi $t1, $a1, 1
		div $t1, $a3
		mfhi $t0				#se t0 <= 0 sei al lato a DX
		ble $t0, $0, comin
		li $t9, 1				#se t9 == 1 NON è al lato DX
		
comin:	li $v0, 0
		add $t5, $a0, $a1 		#pos X in matrice
		
giu:	ble $a1, $a2, cntSx		#se a1 <= a2 non guardare linea dietro 
		sub $t6, $t5, $a3
		lb $v0, ($t6)
		
cntGSx:	beq $t8, $0, cntGDx
		lb $t0, -1($t6)
		add $v0, $v0, $t0

cntGDx:	beq $t9, $0, cntSx
		lb $t0, 1($t6)
		add $v0, $v0, $t0
		
cntSx:	beq $t8, $0, cntDx
		lb $t0, -1($t5)
		add $v0, $v0, $t0
		
cntDx:	beq $t9, $0, cntSu
		lb $t0, 1($t5)
		add $v0, $v0, $t0
	
cntSu:	add $t1, $a1, $a3		#pos X + C
		mul $t0, $a2, $a3		#t0 = R*C
		bge $t1, $t0, torna		#se t1 >= t0 ritorna nel main
		add $t6, $a0, $t1
		lb $t0, ($t6)
		add $v0, $v0, $t0
		
cntSuSx:beq $t8, $0, cntSuDx
		lb $t0, -1($t6)
		add $v0, $v0, $t0
		
cntSuDx:beq $t9, $0, torna
		lb $t0, 1($t6)
		add $v0, $v0, $t0

torna:	jr $ra
		
.end contaVicini