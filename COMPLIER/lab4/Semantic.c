#include "Semantic.h"
#define DEBUG 0

//负责进行语法树的语义分析
//该函数调用semantic_Analysis函数进行符号表的构建
void semantic_Analysis0(struct ASTNode *T)
{
    symbolTable.index = 0;
    fillSymbolTable("read", "", 0, INT, 'F', 4);
    symbolTable.symbols[0].paramnum = 0; //read的形参个数
    fillSymbolTable("write", "", 0, INT, 'F', 16);
    symbolTable.symbols[1].paramnum = 1;
    fillSymbolTable("x","",1,INT,'P',12);
    symbol_scope_TX.TX[0] = 0; //外部变量在符号表中的起始序号为0
    symbol_scope_TX.top = 1;
    T->offset = 0; //外部变量在数据区的偏移量
    flag=0;
    return_flag=0;
    LEV=0;
    semantic_Analysis(T);
    //打印中间代码
    prn_symbol();
    prnIR(T->code);
    objectCode(T->code);
}

void semantic_Analysis(struct ASTNode *T)
{ //对抽象语法树的先根遍历,按display的控制结构修改完成符号表管理和语义检查和TAC生成（语句部分）
    int rtn, num, width;
    struct ASTNode *T0;
    struct opn opn1, opn2, result;
    if (T)
    {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            ext_def_list(T);
            break;
        case EXT_VAR_DEF: //处理外部说明,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
            ext_var_def(T);
            break;
        case FUNC_DEF: //填写函数定义信息到符号表
            func_def(T);
            break;
        case FUNC_DEC: //根据返回类型，函数名填写符号表
            func_dec(T);
            break;
        case PARAM_LIST: //处理函数形式参数列表
            param_list(T);
            break;
        case PARAM_DEC:
            param_dec(T);
            break;
        case COMP_STM:
            comp_stm(T);
            break;
        case DEF_LIST:
            def_list(T);
            break;
        case VAR_DEF: //处理一个局部变量定义,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
                      //类似于上面的外部变量EXT_VAR_DEF，换了一种处理方法
            var_def(T);
            break;
        case STM_LIST:
            stm_list(T);
            break;
        case IF_THEN:
            if_then(T);
            break; //控制语句都还没有处理offset和width属性
        case IF_THEN_ELSE:
            if_then_else(T);
            break;
        case WHILE:
            while_handle(T);
            break;
        case EXP_STMT:
            exp_stmt(T);
            break;
        case FOR:
            flag++;
            for_handle(T);
            flag--;
            break;
        case FOR_DEC:
            semantic_Analysis(T->ptr[0]);
            semantic_Analysis(T->ptr[1]);
            semantic_Analysis(T->ptr[2]);
            break;
        case FOR_DEC1:
            T->ptr[0]->offset=T->offset;
            semantic_Analysis(T->ptr[0]);
            T->width=T->ptr[0]->width;
          //  semantic_Analysis(T->ptr[1]);
            break;
        case FOR_DEC2: 
            strcpy(T->ptr[0]->Etrue,T->Etrue);
            strcpy(T->ptr[0]->Efalse,T->Efalse);
            T->ptr[0]->offset=T->offset;
            boolExp(T->ptr[0]);
            T->width=T->ptr[0]->width;

            T->code=T->ptr[0]->code;
            break;
        case FOR_DEC3:
            T0=T;
            T->code=NULL;
            while (T0)
            {
                T0->ptr[0]->offset=T0->offset;
                semantic_Analysis(T0->ptr[0]);
                T0->width=T0->ptr[0]->width;
                T->code=merge(2,T->code,T0->ptr[0]->code);
                T0=T0->ptr[1];
            }
            break;
        case BREAK:
            if(flag==0)
                semantic_error(T->pos,"","break语句位置错误");
            else{
                T->code=merge(2,T->code,genGoto(T->Sbreak));
            }
            break;
        case CONTINUE:
            if(flag==0)
                semantic_error(T->pos,"","continue语句位置错误");
            else
            {
                T->code=genGoto(T->Scontinue);
            }
            
            break;
        case RETURN:
             return_handle(T);
             break;
                
        case ASSIGNOP:
        case PLUSASSIGNOP:
        case MINUSASSIGNOP:
        case STARASSIGNOP:
        case DIVASSIGNOP:
        case MODASSIGNOP:
        case AND:
        case OR:
        case RELOP:
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case MOD:
        case AUTOMINUS:
        case AUTOPLUS:
        case UMINUS:
        case NOT:
        case FUNC_CALL:
        case ID:
        case CHAR:
        case STRING:
        case FLOAT:
        case ARRAY_VISIT:
        case STRUCTVI: 
        case ARRAYLIST:
        case ARGS:
            Exp(T); //处理基本表达式
            break;
        }
    }
}

