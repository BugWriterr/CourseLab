#include "Semantic.h"

void AssignopExp(struct ASTNode *T) //处理各种赋值
{
    if (T->ptr[0]->kind != ID&&T->ptr[0]->kind != ARRAYLIST&&T->ptr[0]->kind != ARRAY_VISIT)
    {
        semantic_error(T->pos, "", "对非左值进行赋值，赋值语句需要左值");
        return;
    }
    else
    {
        Exp(T->ptr[0]); //处理左值，例中仅为变量
        T->ptr[1]->offset = T->offset;
        Exp(T->ptr[1]); //处理赋值表达式
        if (T->ptr[0]->type != T->ptr[1]->type)
        {
            semantic_error(T->pos, "", "赋值号两边类型不一致");
            return;
        }
        T->type = T->ptr[0]->type;
        T->width = T->ptr[1]->width;
    }
}

void boolExp(struct ASTNode *T)
{ //布尔表达式，参考文献[2]p84的思想
    struct opn opn1, opn2, result;
    int op;
    int rtn;
    if (T)
    {
        switch (T->kind)
        {
        case INT:
            break;
        case FLOAT:
            break;
        case CHAR:
            break;
        case STRING:
            break;
        case ID:
            rtn = searchSymbolTable(T->type_id);
            if (rtn == -1)
            {
                semantic_error(T->pos, T->type_id, "变量未定义");
            }
            if (symbolTable.symbols[rtn].flag == 'F')
                semantic_error(T->pos, T->type_id, "对函数名采用非函数调用形式访问");
            else if (symbolTable.symbols[rtn].flag == 'A')
                semantic_error(T->pos, T->type_id, "为数组名，类型不匹配");
            else
            {
                T->place = rtn; //结点保存变量在符号表中的位置
                T->type = symbolTable.symbols[rtn].type;
                T->offset = symbolTable.symbols[rtn].offset;
                T->width = 0; //未再使用新单元
            }
            break;
        case ARRAYLIST:
            rtn = searchSymbolTable(T->type_id);
            if (rtn == -1)
            {
                semantic_error(T->pos, T->type_id, "数组名未定义");
            }
            if (symbolTable.symbols[rtn].flag == 'F')
                semantic_error(T->pos, T->type_id, "对函数名采用非函数调用形式访问");
            else if (symbolTable.symbols[rtn].flag == 'V')
                semantic_error(T->pos, T->type_id, "不是数组变量，类型不匹配");
            else
            {
                T->place=rtn; //结点保存变量在符号表中的位置
                T->type = symbolTable.symbols[rtn].type;
                T->offset = symbolTable.symbols[rtn].offset;
                T->width = 0; //未再使用新单元
            }
            break;
        case RELOP: //处理关系运算表达式,2个操作数都按基本表达式处理
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            Exp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            Exp(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            break;
        case AND:
        case OR:
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            boolExp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            boolExp(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            break;
        case NOT:
            boolExp(T->ptr[0]);
            break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case MOD:
            MathOpExp(T);
            break;
        default :
           // printf("default!\n");
            Exp(T->ptr[0]);
            break;
        }
    }
}

void RelopExp(struct ASTNode *T) //处理逻辑和比较运算
{
    T->type = INT;
    T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
    Exp(T->ptr[0]);
    Exp(T->ptr[1]);
}
void MathOpExp(struct ASTNode *T) //对算术运算进行检查
{
    //需要进行类型检查
    T->ptr[0]->offset = T->offset;
    Exp(T->ptr[0]);
    T->ptr[1]->offset = T->offset + T->ptr[0]->width;
    Exp(T->ptr[1]);
    //判断T->ptr[0]，T->ptr[1]类型是否正确，可能根据运算符生成不同形式的代码，给T的type赋值
    //下面的类型属性计算，没有考虑错误处理情况
    if (T->ptr[0]->type == FLOAT && T->ptr[1]->type == FLOAT)
    {
        T->type = FLOAT;
        T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
    }
    else if (T->ptr[0]->type == INT && T->ptr[1]->type == INT)
    {

        T->type = INT;
        T->width = T->ptr[0]->width + T->ptr[1]->width + 2;
    }
    else if (T->ptr[0]->type == CHAR && T->ptr[1]->type == CHAR)
    {

        T->type = CHAR;
        T->width = T->ptr[0]->width + T->ptr[1]->width + 2;
    }
    else //类型不匹配
    {
        semantic_error(T->pos, " 算术运算符左右类型不匹配", "");
        return;
    }
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->ptr[0]->width + T->ptr[1]->width);
    T->width = T->ptr[0]->width + T->ptr[1]->width + (T->type == INT ? 4 : 8);
}

void AutoAddMinus(struct ASTNode *T)
{

    T->ptr[0]->offset = T->offset;
    Exp(T->ptr[0]);
    //printf("place为:%d\n",T->ptr[0]->place);
    int templace = T->ptr[0]->place;
    if (templace >= 0 && (symbolTable.symbols[templace].flag == 'V' || symbolTable.symbols[templace].flag == 'P'))
    {
        T->type = T->ptr[0]->type;
    }
    else //非左值自增自减
    {
        semantic_error(T->pos, "", "非左值不可进行自增自减运算");
    }
}

void IdExp(struct ASTNode *T)
{
    int rtn = searchSymbolTable(T->type_id);
    if (rtn == -1)
        semantic_error(T->pos, T->type_id, "变量未定义");
    if (symbolTable.symbols[rtn].flag == 'F')
        semantic_error(T->pos, T->type_id, "对函数名采用非函数调用形式访问");
    else if (symbolTable.symbols[rtn].flag == 'A')
        semantic_error(T->pos, T->type_id, "是数组变量，不能作为左值");
    else
    {
        T->place = rtn; //结点保存变量在符号表中的位置
        T->type = symbolTable.symbols[rtn].type;
        T->offset = symbolTable.symbols[rtn].offset;
        T->width = 0; //未再使用新单元
    }
}

void IntExp(struct ASTNode *T)
{
    T->type = INT;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为整常量生成一个临时变量
    T->width = 4;
}

void FloatExp(struct ASTNode *T)
{
    T->type = FLOAT;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为浮点常量生成一个临时变量
    T->width = 4;
}
void CharExp(struct ASTNode *T)
{
    T->type = CHAR;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
    T->width = 1;
}
void StringExp(struct ASTNode *T)
{
    T->type = STRING;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
    T->width = 8;
}
void Arrayvisit(struct ASTNode* T,struct ArrayInfo* info)
{
    int dimsize=info->dim;
    int i=0;
    struct ASTNode *T0=T;
    while(T0)
    {
        if(T0-> kind ==INT||T0->kind ==PLUS||T0->kind==ID)
        {
            if(T0->kind==INT&&T0->type_int<0) 
            {
                semantic_error(T->pos,"","数组下标小于0，异常");
                return ;
            }
            else if(T0->kind== ID&&T0->type!=INT)
            {
                semantic_error(T->pos,T0->type_id,"数组下标不是INT类型");
            }
            
            Exp(T0);
            i++;
            if(i>dimsize)
            {
                semantic_error(T->pos,"","数组访问维数过大");
                return ;
            }
            T0=T0->ptr[0];
        }
        else if(T0->kind==ARRAYLIST)
        {
            // printf("DBEUG\n");
            struct ASTNode *T1=T0->ptr[0];
              if(T1->type==INT&&T1->type_int<0) 
            {
                semantic_error(T->pos,"","数组下标小于0，异常");
                return ;
            }
             else if(T1->kind==CHAR||T1->kind==FLOAT||T1->kind==STRING)
            {
                semantic_error(T->pos,"","数组下标表达式不正确");
                return ;
            }
            Exp(T1);
            i++;
            if(i>dimsize)
            {
                semantic_error(T->pos,"","数组访问维数过大");
                return ;
            }
            T0=T0->ptr[1];
        }
        else //if(T0->kind==CHAR||T0->kind==FLOAT||T0->kind==STRING)
        {
            if(T0->kind==UMINUS)
            {
                semantic_error(T->pos,"","数组下标不能为负数");
                return ;
            }
                semantic_error(T->pos,"","数组下标表达式不正确");
                return ;
        }
    }
    
    if(i<dimsize) semantic_error(T->pos,"","数组维数过小");
    
}
void Exp(struct ASTNode *T)
{ //处理基本表达式，参考文献[2]p82的思想
    int rtn, num, width;
    struct ASTNode *T0;
    int type;
    struct opn opn1, opn2, result;
    if (T)
    {
        switch (T->kind)
        {
        case ASSIGNOP:
        case PLUSASSIGNOP:
        case MINUSASSIGNOP:
        case STARASSIGNOP:
        case DIVASSIGNOP:
        case MODASSIGNOP:
            //以上都是赋值号
            AssignopExp(T);
            break;
        case AND:   //按算术表达式方式计算布尔值，未写完
        case OR:    //按算术表达式方式计算布尔值，未写完
        case RELOP: //按算术表达式方式计算布尔值，未写完
            RelopExp(T);
            break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case MOD:
            MathOpExp(T);
            break;
        case AUTOPLUS:
        case AUTOMINUS:
            AutoAddMinus(T);
            break;
        case UMINUS:
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            if (T->ptr[0]->type != INT) //负号
            {
                semantic_error(T->pos, "", "负号只能对整数表达式有效");
                break;
            }
            T->type = T->ptr[0]->type;
            break;
        case NOT:
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->type = INT;
            break;
        case FUNC_CALL: //根据T->type_id查出函数的定义，如果语言中增加了实验教材的read，write需要单独处理一下
            rtn = searchSymbolTable(T->type_id);
            if (rtn == -1)
            {
                semantic_error(T->pos, T->type_id, "函数未定义");
                break;
            }
            if (symbolTable.symbols[rtn].flag != 'F')
            {
                semantic_error(T->pos, T->type_id, "对非函数名采用函数调用形式");
                break;
            }
            T->type = symbolTable.symbols[rtn].type;
            //width需要更改
            width = T->type == INT ? 4 : 8; //存放函数返回值的单数字节数
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                Exp(T->ptr[0]);      //处理所有实参表达式求值，及类型
                match_param(rtn, T); //处理所有参数的匹配
                //处理参数列表的中间代码

                T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->width - width);
                T->width = T->ptr[0]->width + width; //累加上计算实参使用临时变量的单元数
            }
            else if (symbolTable.symbols[rtn].paramnum != 0)
            {
                semantic_error(T->pos, T->type_id, "该函数需要参数!");
            }
            break;
        case ID: //查符号表，获得符号表中的位置，类型送type
            IdExp(T);
            break;
        case CHAR:
            CharExp(T);
            break;
        case INT:
            IntExp(T);
            break;
        case FLOAT:
            FloatExp(T);
            break;
        case STRING:
            StringExp(T);
            break;
        case ARRAY_VISIT:
          
            rtn = searchSymbolTable(T->type_id);
            if (rtn == -1)
            {
                semantic_error(T->pos, T->type_id, "数组未定义");
                break;
            }
            else if (symbolTable.symbols[rtn].flag == 'F')
            {
                semantic_error(T->pos, T->type_id, "对非数组变量采用下标形式访问");
                break;
            }
            else if (symbolTable.symbols[rtn].flag == 'V'||symbolTable.symbols[rtn].flag == 'P')
            {
                semantic_error(T->pos, T->type_id, "对非数组变量采用下标形式访问");
                break;
            }
            else
            {
                type=symbolTable.symbols[rtn].type;
                T->ptr[0]->type=type;
                Arrayvisit(T->ptr[0],symbolTable.symbols[rtn].info);
                T->place = rtn;
                T->type = symbolTable.symbols[rtn].type;
                T->offset = symbolTable.symbols[rtn].offset;
                break;
            }
            break;
        case ARGSLIST:
            Exp(T->ptr[0]);
            Exp(T->ptr[1]);
            break;
        case ARGS: //此处仅处理各实参表达式的求值的代码序列，不生成ARG的实参系列
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            // T->code = T->ptr[0]->code;
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                Exp(T->ptr[1]);
                T->width += T->ptr[1]->width;
            }
            break;
        }
    }
}
