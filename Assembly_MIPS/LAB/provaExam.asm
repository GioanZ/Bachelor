.data 
cognome: .asciiz "ROSSI" 
nome: .asciiz "GENNARO" 
data1: .asciiz "120892" 
CF: .space 12 
.text 
.globl main 
 .ent main 
main: subu $sp, $sp, 4 
 sw $ra, ($sp) 
 
 la $a0, cognome 
 la $a1, nome 
la $a2, data1 
 la $a3, CF 
 jal CalcoloCF
 
 lw $ra, ($sp) 
 addiu $sp, $sp, 4 
 jr $ra 
 .end main 
.ent MonthToChar 

.ent MonthToChar 
MonthToChar: 
subu $sp, $sp, 4 
sw $ra, ($sp) 
subu $sp, $sp, 12 
sw $t0, ($sp) 
sw $t1, 4($sp) 
sw $t2, 8($sp) 
move $t0, $a0 
srl $t0, $t0, 8 
subu $t0, $t0, '0' 
mul $t0, $t0, 10 
move $t1, $a0 
li $t2, 0xFF 
and $t1, $t1, $t2 
subu $t1, $t1, '0' 
addu $t1, $t1, $t0 
#in $t1 il numero 
subu $t1, $t1, 1 # per partire con A 
addu $v0, $t1, 'A' 
lw $t2, 8($sp) 
lw $t1, 4($sp) 
lw $t0, ($sp) 
addiu $sp, $sp, 12 
lw $ra, ($sp) 
addiu $sp, $sp, 4 
jr $ra 
.end MonthToChar 








.ent CalcoloCF
CalcoloCF:
subu $sp, $sp, 4
sw $ra, ($sp)



move $t5, $a0
move $t6, $a3
move $t3, $a3
li $t4, 0

inizio:
li $t0, 0


ciclo1:
lb $t1, 0($t5)
li $t2, 'A'
beq $t1, $t2, cnt
li $t2, 'E'
beq $t1, $t2, cnt
li $t2, 'I'
beq $t1, $t2, cnt
li $t2, 'O'
beq $t1, $t2, cnt
li $t2, 'U'
beq $t1, $t2, cnt
addi $t0, $t0, 1
sb $t1, 0($t6)
addi $t6, $t6, 1
li $t2, 3
beq $t0, $t2, finConsonanti

cnt:
addi $t5, $t5, 1
j ciclo1


finConsonanti:
beqz $t4, controllaNome
j data

controllaNome:
addi $t4, $t4, 1
move $t5, $a1
j inizio



data:
li $t0, 0
li $t1, 3
move $t2, $a2

lb $t9, 0($t2)
sb $t9, 0($t6)
lb $t9, 1($t2)
sb $t9, 1($t6)
addi $t2, $t2, 2
addi $t6, $t6, 2

inzio2:
addi $t0, $t0, 1
lhu $a0, 0($t2)
lb $t9, 1($t2)
lb $a0, 0($t2)
sll $a0, $a0, 8 
addi $t2, $t2, 2
or $a0, $a0, $t9

subu $sp, $sp, 20
sw $t0, 0($sp)
sw $t1, 4($sp)
sw $t2, 8($sp)
sw $t3, 12($sp)
sw $t6, 16($sp)
jal MonthToChar
lw $t0, 0($sp)
lw $t1, 4($sp)
lw $t2, 8($sp)
lw $t3, 12($sp)
lw $t6, 16($sp)
addiu $sp, $sp, 20

sb $v0, 0($t6)
addi $t6, $t6, 1
#bne $t0, $t1, inizio2
lb $t9, 0($t2)
sb $t9, 0($t6)
lb $t9, 1($t2)
sb $t9, 1($t6)
addi $t2, $t2, 2
addi $t6, $t6, 2

#12-esimo carattere
li $t0, 10
lb $t5, 0($t3)
addi $t3, $t3, 1


ciclo3:
lb $t1, 0($t3)
addi $t3, $t3, 1

xor $t5, $t5, $t1
subu $t0, $t0, 1
beqz $t0, fine
j ciclo3


fine:
sb $t5, 0($t6)

lw $ra, ($sp)
addiu $sp, $sp, 4
jr $ra
.end CalcoloCF