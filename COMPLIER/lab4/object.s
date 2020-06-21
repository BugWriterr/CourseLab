.data
_Prompt: .asciiz "Enter an integer:  "
_ret: .asciiz "\n"
.globl main
.text
  li $t7,0x40
jal main
li $v0,10
syscall
read:
  li $v0,4
  la $a0,_Prompt
  syscall
  li $v0,5
  syscall
  jr $ra
write:
  li $v0,1
  syscall
  li $v0,4
  la $a0,_ret
  syscall
  move $v0,$0
  jr $ra

main:
  addi $sp, $sp, -64
  li $t3, 0
  sw $t3, 60($sp)
  lw $t1, 60($sp)
  move $t3, $t1
  sw $t3, 52($sp)
label4:
  li $t3, 10
  sw $t3, 64($sp)
  lw $t1, 52($sp)
  lw $t2, 64($sp)
  blt $t1,$t2,label3
  j label2
label3:
  lw $t1, 52($sp)
  move $t3, $t1
  sw $t3, 64($sp)
  lw $t1, 64($sp)
  li $t2,4
  mul $t3,$t1,$t2
  sw $t3, 64($sp)
  addi $sp,$sp,-4
  sw $ra,0($sp)
  jal read
  lw $ra,0($sp)
  addi $sp,$sp,4
  sw $v0,60($sp)
  lw $t1, 60($sp)
  move $t3, $t1
  add $t1,$zero,$sp
  add $t1,$t1,12
  lw $t2,64($sp)
  add $t1,$t1,$t2
  sw $t3, 0($t1)
  j label5
label5:
  lw $t1, 52($sp)
  move $t3, $t1
  sw $t3, 64($sp)
  addi $t3,$t3,1
  sw $t3, 52($sp)
  j label4
label2:
  li $t3, 0
  sw $t3, 60($sp)
  lw $t1, 60($sp)
  move $t3, $t1
  sw $t3, 52($sp)
label8:
  li $t3, 10
  sw $t3, 64($sp)
  lw $t1, 52($sp)
  lw $t2, 64($sp)
  blt $t1,$t2,label7
  j label6
label7:
  lw $t1, 52($sp)
  move $t3, $t1
  sw $t3, 64($sp)
  lw $t1, 64($sp)
  li $t2,4
  mul $t3,$t1,$t2
  sw $t3, 64($sp)
  add $t1,$zero,$sp
  add $t1,$t1,12
  lw $t2,64($sp)
  add $t1,$t1,$t2
  lw $t3, 0($t1)
  sw $t3, 56($sp)
  lw $a0,56($sp)
  addi $sp,$sp,-4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp,$sp,4
  
  lw $t1, 52($sp)
  move $t3, $t1
  sw $t3, 64($sp)
  lw $t1, 64($sp)
  li $t2,4
  mul $t3,$t1,$t2
  sw $t3, 64($sp)
  lw $a0,64($sp)
  addi $sp,$sp,-4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp,$sp,4
  j label9
label9:
  lw $t1, 52($sp)
  move $t3, $t1
  sw $t3, 64($sp)
  addi $t3,$t3,1
  sw $t3, 52($sp)
  j label8
label6:
  li $t3, 1
  sw $t3, 60($sp)
  lw $v0, 60($sp)
  jr $ra
label1:
