# Proposta di soluzione esercizio esame 01-07-2020
#

		DIM = 11
		.data
virgola :  .asciiz   "," 
veta:		.word 2, 14, 8, 54, 0, 42, 9, 24, 0, 91, 23
vetb:       	.byte 4*DIM

		.text
		.globl main
		.ent main
main:	subu $sp, $sp, 4
      sw $ra, ($sp)
      
		  la $a0, veta
		  la $a1, vetb
		  li $a2, DIM
		  jal media
      
      # PRINT VETB
      la  $t0, vetb 
      li $t1, 0   # $t1 contatore 
      lp_print :  lw  $a0, ($t0)    
                  li  $v0, 1        # Print integer   
                  syscall           
                                    # Print VIRGOLA
                  la $a0, virgola    
                  li $v0, 4             
                  syscall  
                  
                  beq $t1, DIM-1, lp_end
                  addi $t1, $t1, 1
                  addi $t0,$t0, 4  
                  j lp_print
       lp_end :
    
		  lw $ra, ($sp)
      addi $sp, $sp, 4
		.end main

   .ent media
   media :
        move  $t0, $a0
        move  $t1, $a1
        move  $t2, $a2
        ble   $a2, 3, tre
        
        li   $t3,3      #     Contatore
        lw  $s0, ($t0)
        sw  $s0, ($t1)
        addi  $t0, $t0, 4
        addi  $t1, $t1, 4
        lw  $s0, ($t0)
        sw  $s0, ($t1)
        addi  $t0, $t0, 4
        addi  $t1, $t1, 4
        
        loop: 
          subu  $sp,$sp,4
          sw    $t0, ($sp)
          subu  $t0, $t0, 8
          lw    $s0, ($t0)
          addi  $t0, $t0, 4
          lw    $s1, ($t0)
          addi  $t0, $t0, 4
          lw    $s2, ($t0)
          addi  $t0, $t0, 4
          lw    $s3, ($t0)
          addu  $s1, $s1, $s0
          addu  $s2, $s2, $s1
          addu  $s3, $s3, $s2
          divu  $s3, $s3, 4
          sw    $s3, ($t1)        # Valore calcolato MEMORIZZATO in VETB
          
          lw    $t0, ($sp)
          addi  $sp, $sp, 4
          
          # Test se siamo a DIM-1        
          addi $t3, $t3, 1
          beq   $t3, $t2, tre_1
          addu  $t0, $t0, 4       # Incremento puntatore VETA
          addu  $t1, $t1, 4       # Incremento puntatore VETB
          j loop
        
        j fine
                  
    tre :
        lw  $s0, ($t0)
        sw  $s0, ($t1)
        beq $t2, 1, fine
        addi  $t0, $t0, 4
        addi  $t1, $t1, 4
        lw  $s0, ($t0)
        sw  $s0, ($t1)
        beq $t2, 2, fine
        tre_1:
        addi  $t0, $t0, 4
        addi  $t1, $t1, 4
        lw  $s0, ($t0)
        sw  $s0, ($t1)   
        j fine
   
    fine:
        jr $ra
   .end media
   
   