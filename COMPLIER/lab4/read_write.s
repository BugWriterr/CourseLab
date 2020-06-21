
.data
_Prompt: .asciiz "Enter an integer:  "
_ret: .asciiz "\n"

# .globl main
.text
read:
  li $v0,4
  la $a0,_Prompt     
  syscall            # //v0=4,4号中断，输出字符串
  li $v0,5           # //5表示读入整数   
  syscall            # //结果保存在$v0中
  jr $ra

write:
  li $v0,1          # //v0=1，1号中断,a0为输出的数据
  syscall           # //a0为输出的数据
  li $v0,4          # //4号中断，
  la $a0,_ret       # //输出回车
  syscall           #  //响应系统功能调用
  move $v0,$0       # //return 0;
  jr $ra    


# read调用

addi $sp, $sp, -4  # //开活动记录空间
sw $ra,0($sp)      #  //保留返回地址
jal read           #      //跳转到函数read
lw $ra,0($sp)      # //恢复返回地址
addi $sp, $sp, 4   # //删除活动记录空间
sw $v0, 偏移量($sp) # //取得函数返回值

# write调用

lw $a0, 偏移量($sp)      # //去要输出的数据到 $a0,$a0为函数参数
addi $sp, $sp, -4      #   //开活动记录空间
sw $ra,0($sp)           #  //保存返回地址
jal write               #  //跳转到write函数
lw $ra,0($sp)            #  //恢复返回地址
addi $sp, $sp, 4         # //删除活动记录空间

# $v0寄存器存储函数返回值 $a0存储参数