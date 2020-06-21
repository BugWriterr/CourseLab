#include "Semantic.h"

//这段代码结合实验教材，采用朴素寄存器分配,完成将中间代码转换成MISPS代码，并输出MIPS代码文件

//全局变量和局部变量均存在数据段
//但他们的基址不同，全局的基址为0，局部的基址为

//t6为起始地址保存全局变量
//t0类似于ebp寄存器
//v0寄存器存储函数返回值
//进函数前保存函数返回值，类似于保护现场
//出函数的时候先回复函数返回值

//函数调用的流程

//首先保存sp的值到t0寄存器，用于取得实参的值
//然后开辟函数活动空间 addi sp指令
//保存当前函数的返回地址
//保存被调用函数的实参值，取出t0开始的offset中，即被调用函数的实参存储位置，
//取出之后存入sp开始的offset中，即被调用函数的形参的存储位置

//然后使用jal指令调用函数 ，会跳转到被调用函数，同时将调用点地址保存在ra寄存器中
//调用完成后，按顺序恢复现场

//被调用函数中将返回值存在寄存器v0寄存器中
//然后使用jr $ra回到调用处的下一条

void objectCode(struct codenode *head)
{
    FILE *fp;
    char opnstr1[32], opnstr2[32], resultstr[32];
    if (head == NULL)
    {
        fprintf(fp, "no objectCode\n");
        return;
    }

    struct codenode *h = head, *p;
    int i, j, index, type;
    fp = fopen("object.s", "w");
    fprintf(fp, ".data\n");
    fprintf(fp, "_Prompt: .asciiz \"Enter an integer:  \"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
    fprintf(fp, ".globl main\n");
    fprintf(fp, ".text\n");
    fprintf(fp, "  li $t7,0x40\n");
    fprintf(fp, "jal main\n");
    fprintf(fp, "li $v0,10\n");
    fprintf(fp, "syscall\n");
    fprintf(fp, "read:\n");
    fprintf(fp, "  li $v0,4\n");
    fprintf(fp, "  la $a0,_Prompt\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0,5\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  jr $ra\n");
    fprintf(fp, "write:\n");
    //write函数的参数在
    fprintf(fp, "  li $v0,1\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0,4\n");
    fprintf(fp, "  la $a0,_ret\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  move $v0,$0\n");
    fprintf(fp, "  jr $ra\n");

    do
    {
        switch (h->op)
        {
        case ASSIGNOP:
            if (h->opn1.kind == INT)
            {
                fprintf(fp, "  li $t3, %d\n", h->opn1.const_int);
            }
            else
            {
                if (h->opn1.kind == ARRAY_VISIT)
                {
                    if(h->opn1.isGlobal==0){
                        fprintf(fp, "  add $t1,$zero,$t7\n");
                        fprintf(fp, "  add $t1,$t1,%d\n", h->opn1.offset2);
                        fprintf(fp, "  lw $t2,%d($sp)\n", h->opn1.offset);
                        fprintf(fp, "  add $t1,$t1,$t2\n");
                        fprintf(fp, "  lw $t3,0($t1)\n");
                    }
                    else{
                         fprintf(fp, "  add $t1,$zero,$sp\n");
                        fprintf(fp, "  add $t1,$t1,%d\n", h->opn1.offset2);
                        fprintf(fp, "  lw $t2,%d($sp)\n", h->opn1.offset);
                        fprintf(fp, "  add $t1,$t1,$t2\n");
                        fprintf(fp, "  lw $t3, 0($t1)\n");
                    }
                }
                else
                {
                    if (h->opn1.isGlobal == 0)
                    {
                        fprintf(fp, "  lw $t1, %d($t7)\n", h->opn1.offset);
                    }
                    else
                    {
                        fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                    }
                    fprintf(fp, "  move $t3, $t1\n");
                }
            }
            if (h->result.kind == ARRAY_VISIT)
            {
                if (h->result.isGlobal == 0)
                {
                    //fprintf(fp, "  sw $t3, %d($t7)\n", h->result.offset);
                    fprintf(fp, "  add $t1,$zero,$t7\n");
                    fprintf(fp, "  add $t1,$t1,%d\n", h->result.offset2);
                    fprintf(fp, "  lw $t2,%d($sp)\n", h->result.offset);
                    fprintf(fp, "  add $t1,$t1,$t2\n");
                    fprintf(fp, "  sw $t3,0($t1)\n");
                }
                else
                {
                    fprintf(fp, "  add $t1,$zero,$sp\n");
                    fprintf(fp, "  add $t1,$t1,%d\n", h->result.offset2);
                    fprintf(fp, "  lw $t2,%d($sp)\n", h->result.offset);
                    fprintf(fp, "  add $t1,$t1,$t2\n");
                    fprintf(fp, "  sw $t3, 0($t1)\n");
                }
            }
            else
            {
                if (h->result.isGlobal == 0)
                {
                    fprintf(fp, "  sw $t3, %d($t7)\n", h->result.offset);
                }
                else
                {
                    printf("h->result->offset:%d\n",h->result.offset2);
                    fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
                }
            }
            //fprintf(fp,"  sw $t3, %d($sp)\n", h->result.offset);
            break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
            if (h->opn1.kind == INT)
                fprintf(fp, "  li $t1,%d\n", h->opn1.const_int);
            else
            {
                if (h->opn1.isGlobal == 0)
                {

                    fprintf(fp, "  lw $t1, %d($t7)\n", h->opn1.offset);
                }
                else
                {
                    fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                }
            }
            if (h->opn2.kind == INT)
                fprintf(fp, "  li $t2,%d\n", h->opn2.const_int);
            else
            {
                if (h->opn2.isGlobal == 0)
                {
                    fprintf(fp, "  lw $t2, %d($t7)\n", h->opn2.offset);
                }
                else
                {
                    fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
                }
            }

            if (h->op == PLUS)
                fprintf(fp, "  add $t3,$t1,$t2\n");
            else if (h->op == MINUS)
                fprintf(fp, "  sub $t3,$t1,$t2\n");
            else if (h->op == STAR)
                fprintf(fp, "  mul $t3,$t1,$t2\n");
            else if (h->op == DIV)
            {
                fprintf(fp, "  div $t1, $t2\n");
                fprintf(fp, "  mflo $t3\n");
            }
            if (h->result.isGlobal == 0)
            {
                fprintf(fp, "  sw $t3, %d($t7)\n", h->result.offset);
            }
            else
            {
                fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
            }
            break;
        case UMINUS:
            if (h->opn1.isGlobal == 0)
            {
                fprintf(fp, "  lw $t2, %d($t7)\n", h->opn1.offset);
            }
            else
            {
                fprintf(fp, "  lw $t2, %d($sp)\n", h->opn1.offset);
            }
            fprintf(fp, "  sub $t3,$zero,$t2\n");
            if (h->result.isGlobal == 0)
            {
                fprintf(fp, "  sw $t3, %d($t7)\n", h->result.offset);
            }
            else
            {
                fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
            }
            break;
        case AUTOMINUS:
        case AUTOPLUS:
            if (h->opn2.kind == LPAUTO)
            { //左
                if (h->opn1.isGlobal == 0)
                {
                    fprintf(fp, "  lw $t1, %d($t7)\n", h->opn1.offset);
                }
                else
                {
                    fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                }
                if (h->op == AUTOPLUS)
                    fprintf(fp, "  addi $t1,$t1,1\n");
                else
                    fprintf(fp, "  subi $t1,$t1,1\n");
                if (h->opn1.isGlobal == 0)
                {
                    fprintf(fp, "  sw $t1, %d($t7)\n", h->opn1.offset);
                }
                else
                {
                    fprintf(fp, "  sw $t1, %d($sp)\n", h->opn1.offset);
                }
            }
            else
            {
                if (h->opn1.isGlobal == 0)
                {
                    fprintf(fp, "  lw $t1, %d($t7)\n", h->opn1.offset);
                }
                else
                {
                    fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                }
                fprintf(fp, "  move $t3, $t1\n");
                if (h->result.isGlobal == 0)
                {
                    fprintf(fp, "  sw $t3, %d($t7)\n", h->result.offset);
                }
                else
                {
                    fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
                }
                if (h->op == AUTOPLUS)
                    fprintf(fp, "  addi $t3,$t3,1\n");
                else
                    fprintf(fp, "  subi $t3,$t3,1\n");

                if (h->opn1.isGlobal == 0)
                {
                    fprintf(fp, "  sw $t3, %d($t7)\n", h->opn1.offset);
                }
                else
                {
                    fprintf(fp, "  sw $t3, %d($sp)\n", h->opn1.offset);
                }
            }
            break;
        case FUNCTION:
            fprintf(fp, "\n%s:\n", h->result.id);
            if (!strcmp(h->result.id, "main")) //特殊处理main
            {
                // for (i = 0; symbolTable.symbols[i].flag == 1; i++)
                //     ;
                // fprintf(fp, "  addi $sp, $sp, -%d\n", i * 4);
                // i = 0;
                //fprintf(fp, "  move $t7, 0\n");                                                      //t6存最初始的sp值
                fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->result.offset].offset); //这个是函数空间大小
            }

            break;
        case PARAM: //直接跳到后面一条
                    //形参
            break;
        case LABEL:
            fprintf(fp, "%s:\n", h->result.id);
            break;
        case GOTO:
            fprintf(fp, "  j %s\n", h->result.id);
            break;
        case JLE:
        case JLT:
        case JGE:
        case JGT:
        case EQ:
        case NEQ:
            if (h->opn1.isGlobal == 0)
            {
                fprintf(fp, "  lw $t1, %d($t7)\n", h->opn1.offset);
            }
            else
            {
                fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
            }
            if (h->opn2.kind == INT)
            {
                fprintf(fp, "  li $t2,%d\n", h->opn2.const_int);
            }
            else
            {
                if (h->opn2.isGlobal == 0)
                {
                    fprintf(fp, "  lw $t2, %d($t7)\n", h->opn2.offset);
                }
                else
                {
                    fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
                }
            }

            if (h->op == JLE)
                fprintf(fp, "  ble $t1,$t2,%s\n", h->result.id);
            else if (h->op == JLT)
                fprintf(fp, "  blt $t1,$t2,%s\n", h->result.id);
            else if (h->op == JGE)
                fprintf(fp, "  bge $t1,$t2,%s\n", h->result.id);
            else if (h->op == JGT)
                fprintf(fp, "  bgt $t1,$t2,%s\n", h->result.id);
            else if (h->op == EQ)
                fprintf(fp, "  beq $t1,$t2,%s\n", h->result.id);
            else
                fprintf(fp, "  bne $t1,$t2,%s\n", h->result.id);
            break;

        case ARG: //直接跳到后面一条,回头反查
                  //实参
            break;
        case CALL:

            if (!strcmp(h->opn1.id, "read"))
            {
                fprintf(fp, "  addi $sp,$sp,-4\n");
                fprintf(fp, "  sw $ra,0($sp)\n");
                fprintf(fp, "  jal read\n");
                fprintf(fp, "  lw $ra,0($sp)\n");
                fprintf(fp, "  addi $sp,$sp,4\n");
                fprintf(fp, "  sw $v0,%d($sp)\n", h->result.offset);
                break;
            }
            if (!strcmp(h->opn1.id, "write"))
            {
                fprintf(fp, "  lw $a0,%d($sp)\n", h->prior->result.offset);
                fprintf(fp, "  addi $sp,$sp,-4\n");
                fprintf(fp, "  sw $ra,0($sp)\n");
                fprintf(fp, "  jal write\n");
                fprintf(fp, "  lw $ra,0($sp)\n");
                fprintf(fp, "  addi $sp,$sp,4\n");
                break;
            }
            for (p = h, i = 0; i < symbolTable.symbols[h->opn1.offset].paramnum; i++) //定位到第一个实参的结点
                p = p->prior;

            //开活动记录空间

            fprintf(fp, "  move $t0,$sp\n"); //保存当前函数的sp到$t0中，为了取实参表达式的值
            fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->opn1.offset].offset);
            fprintf(fp, "  sw $ra,0($sp)\n"); //保留返回地址
            i = h->opn1.offset + 1;           //第一个形参变量在符号表的位置序号

            while (symbolTable.symbols[i].flag == 'P')
            {
                if (p->result.isGlobal == 0)
                {
                    fprintf(fp, "  lw $t1, %d($t7)\n", p->result.offset);
                }
                else
                {
                    fprintf(fp, "  lw $t1, %d($t0)\n", p->result.offset);
                }
                fprintf(fp, "  move $t3,$t1\n");
                fprintf(fp, "  sw $t3,%d($sp)\n", symbolTable.symbols[i].offset); //送到被调用函数的形参单元
                p = p->next;
                i++;
            }
            fprintf(fp, "  jal %s\n", h->opn1.id);                                          //恢复返回地址
            fprintf(fp, "  lw $ra,0($sp)\n");                                               //恢复返回地址
            fprintf(fp, "  addi $sp,$sp,%d\n", symbolTable.symbols[h->opn1.offset].offset); //释放活动记录空间

            fprintf(fp, "  sw $v0,%d($sp)\n", h->result.offset); //取返回值

            break;
        case RETURN:
            if (h->result.isGlobal == 0)
            {
                fprintf(fp, "  lw $v0, %d($t7)\n", h->result.offset);
            }
            else
            {
                fprintf(fp, "  lw $v0, %d($sp)\n", h->result.offset);
            }
            fprintf(fp, "  jr $ra\n");
            break;
        }
        h = h->next;
    } while (h != head);
    fclose(fp);
}