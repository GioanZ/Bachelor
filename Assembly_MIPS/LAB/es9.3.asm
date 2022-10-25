RIGHE = 4
COLONNE = 5 
.data

matrice: .byte 0, 1, 3, 6, 2, 7, 13, 20, 12, 21, 11, 22, 10, 23, 9, 24, 8, 25, 43, 62

		.text
		.globl main
		.ent main
		
main:	la $a0, matrice
		li $a1, 4
		li $a2, RIGHE
		li $a3, COLONNE 
		jal contaVicini
		
		move $a0, $v0
		li $v0, 1
		syscall
		
fine:	li $v0, 10				#codice per uscita dal programma
		syscall					#fine
.end main

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