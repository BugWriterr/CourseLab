#include "Semantic.h"

#define MAXDIM 10

void AssignopExp(struct ASTNode *T) //处理各种赋值
{
    struct opn opn1, opn2, result;
    if (T->ptr[0]->kind != ID && T->ptr[0]->kind != ARRAYLIST && T->ptr[0]->kind != ARRAY_VISIT)
    {
        semantic_error(T->pos, "", "对非左值进行赋值，赋值语句需要左值");
        return;
    }
    else
    {
        T->ptr[0]->offset=T->offset;
        Exp(T->ptr[0]); //处理左值，例中仅为变量

        T->place = T->ptr[0]->place;
        T->ptr[1]->offset = T->offset+T->ptr[0]->width;

        Exp(T->ptr[1]); //处理赋值表达式
        if (T->ptr[0]->type != T->ptr[1]->type)
        {
            printf("类型:%d,%d\n", T->ptr[0]->type, T->ptr[1]->type);
            semantic_error(T->pos, "", "赋值号两边类型不一致");
            return;
        }
        T->type = T->ptr[0]->type;
        T->width = T->ptr[1]->width;
        T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);
        opn1.kind = ID;
        if(T->ptr[1]->kind==ARRAY_VISIT) opn1.kind=ARRAY_VISIT;
        strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias);
        opn1.offset = symbolTable.symbols[T->ptr[1]->place].offset;
        opn1.offset2=symbolTable.symbols[T->ptr[1]->num].offset;
        if(T->kind==ARRAY_VISIT)
         opn1.isGlobal = symbolTable.symbols[T->ptr[1]->num].level;
        else   opn1.isGlobal = symbolTable.symbols[T->ptr[1]->place].level;

        result.kind = T->ptr[0]->kind;
        strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
        result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
        result.offset2=symbolTable.symbols[T->ptr[0]->num].offset;
        if(T->kind==ARRAY_VISIT)
        result.isGlobal = symbolTable.symbols[T->ptr[0]->num].level;
        else result.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;
        T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));
    }
}

void OPAssignopExp(struct ASTNode *T)
{
    struct opn opn1, opn2, result;
    if (T->ptr[0]->kind != ID && T->ptr[0]->kind != ARRAYLIST && T->ptr[0]->kind != ARRAY_VISIT)
    {
        semantic_error(T->pos, "", "对非左值进行赋值，赋值语句需要左值");
        return;
    }
    else
    {
        Exp(T->ptr[0]); //处理左值，例中仅为变量
        T->place = T->ptr[0]->place;
        T->ptr[1]->offset = T->offset;
        Exp(T->ptr[1]); //处理赋值表达式
        if (T->ptr[0]->type != T->ptr[1]->type)
        {
            semantic_error(T->pos, "", "赋值号两边类型不一致");
            return;
        }
        int kind;
        if (T->kind == PLUSASSIGNOP)
            T->kind = PLUS;
        else if (T->kind == MINUSASSIGNOP)
            T->kind = MINUS;
        else if (T->kind == STARASSIGNOP)
            T->kind = STAR;
        else if (T->kind == DIVASSIGNOP)
            T->kind = DIV;
        else if (T->kind == MODASSIGNOP)
            T->kind = MOD;

        T->type = T->ptr[0]->type;
        T->width = T->ptr[1]->width;
        T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);
        T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->ptr[0]->width + T->ptr[1]->width);
        opn1.kind = ID;
        strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
        opn1.type = T->ptr[0]->type;
        opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
        opn1.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;

        opn2.kind = ID;
        opn2.type = T->ptr[1]->type;
        strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
        opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
        opn2.isGlobal = symbolTable.symbols[T->ptr[1]->place].level;

        result.kind = ID;
        result.type = T->ptr[0]->type;
        strcpy(result.id, symbolTable.symbols[T->place].alias);
        result.offset = symbolTable.symbols[T->place].offset;
        result.isGlobal = symbolTable.symbols[T->place].level;

        T->code = merge(2, T->code, genIR(T->kind, opn1, opn2, result));

        T->width = T->ptr[0]->width + T->ptr[1]->width + (T->type == INT ? 4 : 4);
        T->type = T->ptr[0]->type;
        opn1.kind = ID;
        strcpy(opn1.id, symbolTable.symbols[T->place].alias);
        opn1.offset = symbolTable.symbols[T->place].offset;
        opn1.isGlobal = symbolTable.symbols[T->place].level;

        result.kind = ID;
        strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
        result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
        result.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;

        T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));
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
            if (T->type_int != 0)
                T->code = genGoto(T->Etrue);
            else
                T->code = genGoto(T->Efalse);
            T->width = 0;
            break;
        case FLOAT:
            if (T->type_float != 0.0)
                T->code = genGoto(T->Etrue);
            else
                T->code = genGoto(T->Efalse);
            T->width = 0;
            break;
        case CHAR:
            if (T->type_char[0] != '\0')
                T->code = genGoto(T->Etrue);
            else
                T->code = genGoto(T->Efalse);
            T->type = INT;
            T->width = 0;
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

                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[rtn].alias);
                opn1.offset = symbolTable.symbols[rtn].offset;
                opn1.isGlobal = symbolTable.symbols[rtn].level;
                opn2.kind = INT;
                opn2.const_int = 0;
                T->type = INT;
                result.kind = ID;

                T->type = INT;
                T->width = 0;
                strcpy(result.id, T->Etrue);
                T->code = genIR(NEQ, opn1, opn2, result);
                T->code = merge(2, T->code, genGoto(T->Efalse));
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
                T->place = rtn; //结点保存变量在符号表中的位置
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
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn1.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;

            opn2.kind = ID;
            strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            opn2.isGlobal = symbolTable.symbols[T->ptr[1]->place].level;
            result.kind = ID;
            strcpy(result.id, T->Etrue);
            if (strcmp(T->type_id, "<") == 0)
                op = JLT;
            else if (strcmp(T->type_id, "<=") == 0)
                op = JLE;
            else if (strcmp(T->type_id, ">") == 0)
                op = JGT;
            else if (strcmp(T->type_id, ">=") == 0)
                op = JGE;
            else if (strcmp(T->type_id, "==") == 0)
                op = EQ;
            else if (strcmp(T->type_id, "!=") == 0)
                op = NEQ;
            T->code = genIR(op, opn1, opn2, result);
            T->code = merge(4, T->ptr[0]->code, T->ptr[1]->code, T->code, genGoto(T->Efalse));
            break;
        case AND:
            // boolExp(T->ptr[0]);
            // T->width = T->ptr[0]->width;
            // boolExp(T->ptr[1]);
            // T->type = INT;
            // break;
        case OR:
            if (T->kind == AND)
            {
                strcpy(T->ptr[0]->Etrue, newLabel());
                strcpy(T->ptr[0]->Efalse, T->Efalse);
            }
            else
            {
                strcpy(T->ptr[0]->Etrue, T->Etrue);
                strcpy(T->ptr[0]->Efalse, newLabel());
            }
            strcpy(T->ptr[1]->Etrue, T->Etrue);
            strcpy(T->ptr[1]->Efalse, T->Efalse);
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            boolExp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            boolExp(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            if (T->kind == AND)
                T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
            else
                T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Efalse), T->ptr[1]->code);
            break;
        case NOT:
            strcpy(T->ptr[0]->Etrue, T->Efalse);
            strcpy(T->ptr[0]->Efalse, T->Etrue);
            boolExp(T->ptr[0]);
            T->code = T->ptr[0]->code;
            break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case MOD:
            MathOpExp(T);
            break;
        default:
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
    // T->place=fill_Temp(newTemp(),LEV,T->type,)
}

void MathOpExp(struct ASTNode *T) //对算术运算进行检查
{
    struct opn opn1, opn2, result;
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
        T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
    }
    else if (T->ptr[0]->type == CHAR && T->ptr[1]->type == CHAR)
    {

        T->type = CHAR;
        T->width = T->ptr[0]->width + T->ptr[1]->width + 1;
    }
    else //类型不匹配
    {
        semantic_error(T->pos, " 算术运算符左右类型不匹配", "");
        return;
    }

    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->ptr[0]->width + T->ptr[1]->width);
    opn1.kind = ID;
    strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
    opn1.type = T->ptr[0]->type;
    opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
    opn1.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;
    opn2.kind = ID;
    strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
    opn2.type = T->ptr[1]->type;
    opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
    opn2.isGlobal = symbolTable.symbols[T->ptr[1]->place].level;

    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.type = T->type;
    result.offset = symbolTable.symbols[T->place].offset;
    result.isGlobal = symbolTable.symbols[T->place].level;

    T->code = merge(3, T->ptr[0]->code, T->ptr[1]->code, genIR(T->kind, opn1, opn2, result));
}

void AutoAddMinus(struct ASTNode *T)
{

    struct opn opn1, opn2, result;
    T->ptr[0]->offset = T->offset;
    Exp(T->ptr[0]);
    int templace = T->ptr[0]->place;
    if (templace >= 0 && (symbolTable.symbols[templace].flag == 'V' || symbolTable.symbols[templace].flag == 'P'))
    {
        T->type = T->ptr[0]->type;
    }
    else //非左值自增自减
    {
        semantic_error(T->pos, "", "非左值不可进行自增自减运算");
    }
    //printf("自增中的type为%d\n",T->type);

    T->type = T->ptr[0]->type;
    T->ptr[0]->offset = T->offset;

    opn1.kind = ID;
    strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
    opn1.type = T->ptr[0]->type;
    opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
    opn1.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;

    // result.kind = ID;
    // strcpy(result.id, symbolTable.symbols[T->place].alias);
    // result.type = T->type;
    // result.offset = symbolTable.symbols[T->place].offset;
    // result.isGlobal = symbolTable.symbols[T->place].level;

    if (strcmp(T->type_id, "LPAUTOPLUS") == 0 || strcmp(T->type_id, "LPAUTOMINUS") == 0)
    { //左边
        T->place = T->ptr[0]->place;
        result.kind = ID;
        strcpy(result.id, symbolTable.symbols[T->place].alias);
        result.type = T->type;
        result.offset = symbolTable.symbols[T->place].offset;
        result.isGlobal = symbolTable.symbols[T->place].level;
        opn2.kind = LPAUTO;
    }
    else
    { //在右边
        T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
        result.kind = ID;
        strcpy(result.id, symbolTable.symbols[T->place].alias);
        result.type = T->type;
        result.offset = symbolTable.symbols[T->place].offset;
        result.isGlobal = symbolTable.symbols[T->place].level;
        opn2.kind = RPAUTO;
    }
    T->code = merge(2, T->ptr[0]->code, genIR(T->kind, opn1, opn2, result));
    T->width = T->ptr[0]->width + (T->type == INT ? 4 : 8);
    return;
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
        T->code = NULL;
        T->type = symbolTable.symbols[rtn].type;
        T->offset = symbolTable.symbols[rtn].offset;
        T->width = 0; //未再使用新单元
    }
}

void IntExp(struct ASTNode *T)
{
    struct opn opn1, opn2, result;
    T->type = INT;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为整常量生成一个临时变量
    opn1.kind = INT;
    opn1.const_int = T->type_int;
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.offset = symbolTable.symbols[T->place].offset;
    result.isGlobal = symbolTable.symbols[T->place].level;
    T->code = genIR(ASSIGNOP, opn1, opn2, result);
    T->width = 4;
}

void FloatExp(struct ASTNode *T)
{
    struct opn opn1, opn2, result;
    T->type = FLOAT;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为浮点常量生成一个临时变量
    opn1.kind = FLOAT;
    opn1.const_float = T->type_float;
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.offset = symbolTable.symbols[T->place].offset;
    result.isGlobal = symbolTable.symbols[T->place].level;
    T->code = genIR(ASSIGNOP, opn1, opn2, result);
    T->width = 4;
}

void CharExp(struct ASTNode *T)
{
    struct opn opn1, opn2, result;
    T->type = CHAR;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
    T->width = 1;
    opn1.kind = CHAR;
    opn1.const_char = T->type_char[1];
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.offset = symbolTable.symbols[T->place].offset;
    result.isGlobal = symbolTable.symbols[T->place].level;
    T->code = genIR(ASSIGNOP, opn1, opn2, result);
}

void StringExp(struct ASTNode *T)
{
    struct opn opn1, opn2, result;
    T->type = STRING;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
    T->width = 8;
    opn1.kind = STRING;
    strcpy(opn1.const_string, T->type_string);
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.offset = symbolTable.symbols[T->place].offset;
    result.isGlobal = symbolTable.symbols[T->place].level;
    T->code = genIR(ASSIGNOP, opn1, opn2, result);
}

void Arrayvisit(struct ASTNode *T, struct ArrayInfo *info)
{
    struct opn opn1, opn2, result, result2;
    int op; //操作
    int temprtn = 0;
    int dimsize = info->dim;
    int diminfo[MAXDIM];
    for (int i = 0; i < MAXDIM; i++)
        diminfo[i] = info->diminfo[i][2];
    int i = 0;
    struct ASTNode *T0 = T->ptr[0];

    while (T0)
    {
        if (T0->kind == INT || T0->kind == PLUS || T0->kind == ID || T0->kind == MINUS || T0->kind == DIV || T0->kind == STAR)
        {
            Exp(T0);
            T->code = merge(2, T->code, T0->code);

            if (T0->kind == INT && T0->type_int < 0)
            {
                semantic_error(T->pos, "", "数组下标小于0，异常");
                return;
            }
            else if (T0->kind == ID && T0->type != INT)
            {
                semantic_error(T->pos, T0->type_id, "数组下标不是INT类型");
            }
            i++;
            if (i > dimsize)
            {
                semantic_error(T->pos, "", "数组访问维数过大");
                return;
            }

            if (i == 1) //第一维
            {
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T0->place].alias);
                opn1.offset = symbolTable.symbols[T0->place].offset;
                opn1.type = T0->type;
                opn1.isGlobal = symbolTable.symbols[T0->place].level;

                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->place].alias);
                result.type = INT;
                result.offset=symbolTable.symbols[T->place].offset;
                result.isGlobal = symbolTable.symbols[T->place].level;
                T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));
            }
            else
            { //最后一维
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T->place].alias);
                opn1.offset = symbolTable.symbols[T->place].offset;
                opn1.type = T0->type;
                opn1.isGlobal = symbolTable.symbols[T->place].level;

                opn2.kind = INT;
                opn2.const_int = diminfo[i - 1];

                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->place].alias);
                result.offset = symbolTable.symbols[T->place].offset;
                result.type = T->type;
                result.isGlobal = symbolTable.symbols[T->place].level;

                T->code = merge(2, T->code, genIR(STAR, opn1, opn2, result));

                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T->place].alias);
                opn1.offset = symbolTable.symbols[T->place].offset;
                opn1.type = T->type;
                opn1.isGlobal = symbolTable.symbols[T->place].level;

                opn2.kind = ID;
                strcpy(opn2.id, symbolTable.symbols[T0->place].alias);
                // printf("第二维的别名:%s",symbolTable.symbols[T0->place].alias);
                opn2.offset = symbolTable.symbols[T0->place].offset;
                opn2.type = T0->type;
                opn2.isGlobal = symbolTable.symbols[T0->place].level;

                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->place].alias);
                result.offset = symbolTable.symbols[T->place].offset;
                result.type = T->type;
                result.isGlobal = symbolTable.symbols[T->place].level;

                T->code = merge(2, T->code, genIR(PLUS, opn1, opn2, result));

                //需要将偏移temp*width
            }
            //
            break;
        }
        else if (T0->kind == ARRAYLIST)
        {
            // printf("DBEUG\n");
            struct ASTNode *T1 = T0->ptr[0];
            Exp(T1);

            T->code = merge(2, T->code, T1->code);

            if (T1->type == INT && T1->type_int < 0)
            {
                semantic_error(T->pos, "", "数组下标小于0，异常");
                return;
            }
            else if (T1->kind == CHAR || T1->kind == FLOAT || T1->kind == STRING)
            {
                semantic_error(T->pos, "", "数组下标表达式不正确");
                return;
            }
            else if (T1->kind == ID && T1->type != INT)
            {
                semantic_error(T->pos, T1->type_id, "数组下标不是INT类型");
            }
            // T1->place=fill_Temp(newTemp(),LEV)
            i++;
            if (i > dimsize)
            {
                semantic_error(T->pos, "", "数组访问维数过大");
                return;
            }
            if (i == 1) //第一维
            {
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T1->place].alias);
                opn1.offset = symbolTable.symbols[T1->place].offset;
                opn1.type = T1->type;
                opn1.isGlobal = symbolTable.symbols[T1->place].level;

                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->place].alias);
                result.type = INT;
                result.isGlobal = symbolTable.symbols[T->place].level;
                T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));
            }
            else
            {
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T->place].alias);
                opn1.offset = symbolTable.symbols[T->place].offset;
                opn1.type = T->type;
                opn1.isGlobal = symbolTable.symbols[T->place].level;

                opn2.kind = INT;
                opn2.const_int = diminfo[i - 1];
                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->place].alias);
                result.offset = symbolTable.symbols[T->place].offset;
                result.type = T->type;
                result.isGlobal = symbolTable.symbols[T->place].level;

                T->code = merge(2, T->code, genIR(STAR, opn1, opn2, result));

                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T->place].alias);
                opn1.offset = symbolTable.symbols[T->place].offset;
                opn1.type = T1->type;
                opn1.isGlobal = symbolTable.symbols[T->place].level;

                opn2.kind = ID;
                strcpy(opn2.id, symbolTable.symbols[T1->place].alias);
                opn2.offset = symbolTable.symbols[T1->place].offset;
                opn2.type = T1->type;
                opn2.isGlobal = symbolTable.symbols[T1->place].level;

                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->place].alias);
                result.offset = symbolTable.symbols[T->place].offset;
                result.type = T1->type;
                result.isGlobal = symbolTable.symbols[T->place].level;

                T->code = merge(2, T->code, genIR(PLUS, opn1, opn2, result));
            }
            T0 = T0->ptr[1];
        }
        else //if(T0->kind==CHAR||T0->kind==FLOAT||T0->kind==STRING)
        {
            if (T0->kind == UMINUS)
            {
                semantic_error(T->pos, "", "数组下标不能为负数");
                return;
            }
            semantic_error(T->pos, "", "数组下标表达式不正确");
            return;
        }
    }

    if (i < dimsize)
        semantic_error(T->pos, "", "数组维数过小");
}
void Exp(struct ASTNode *T)
{ //处理基本表达式，参考文献[2]p82的思想
    int rtn, num, width;
    struct ASTNode *T0;
    int type, op;
    struct opn opn1, opn2, result, result2;
    char Label2[15];
    char Label1[15];
    if (T)
    {
        switch (T->kind)
        {
        case ASSIGNOP:
            AssignopExp(T);
            break;
        case PLUSASSIGNOP:
        case MINUSASSIGNOP:
        case STARASSIGNOP:
        case DIVASSIGNOP:
        case MODASSIGNOP:
            //以上都是赋值号
            OPAssignopExp(T);
            break;
        case AND: //按算术表达式方式计算布尔值，未写完
            T->type = INT;
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->code = T->ptr[0]->code;
            strcpy(Label1, newLabel());
            strcpy(Label2, newLabel());
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn1.type = T->ptr[0]->type;
            opn1.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;

            opn2.kind = INT;
            opn2.const_int = 0;
            result.kind = ID;
            strcpy(result.id, Label1);
            op = EQ;
            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));

            T->ptr[1]->offset = T->offset + T->ptr[0]->width;
            Exp(T->ptr[1]);
            T->code = merge(2, T->code, T->ptr[1]->code);
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            opn1.type = T->ptr[1]->type;
            opn1.isGlobal = symbolTable.symbols[T->ptr[1]->place].level;

            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));
            opn1.kind = INT;
            opn1.const_int = 1;
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.type = T->type;
            result.offset = symbolTable.symbols[T->place].offset;
            result.isGlobal = symbolTable.symbols[T->place].level;

            T->code = merge(4, T->code, genIR(ASSIGNOP, opn1, opn2, result), genGoto(Label2), genLabel(Label1));
            opn1.kind = INT;
            opn1.const_int = 0;
            opn1.type = INT;

            T->code = merge(3, T->code, genIR(ASSIGNOP, opn1, opn2, result), genLabel(Label2));
            break;
        case OR: //按算术表达式方式计算布尔值，未写完
            T->type = INT;
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->code = T->ptr[0]->code;
            strcpy(Label1, newLabel());
            strcpy(Label2, newLabel());
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn1.type = T->ptr[0]->type;
            opn1.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;

            opn2.kind = INT;
            opn2.const_int = 0;
            result.kind = ID;
            strcpy(result.id, Label1);
            op = NEQ;
            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));

            T->ptr[1]->offset = T->offset + T->ptr[0]->width;
            Exp(T->ptr[1]);
            T->code = merge(2, T->code, T->ptr[1]->code);
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            opn1.type = T->ptr[1]->type;
            opn1.isGlobal = symbolTable.symbols[T->ptr[1]->place].level;

            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));
            opn1.kind = INT;
            opn1.const_int = 0;
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.type = T->type;
            result.offset = symbolTable.symbols[T->place].offset;
            result.isGlobal = symbolTable.symbols[T->place].level;

            T->code = merge(4, T->code, genIR(ASSIGNOP, opn1, opn2, result), genGoto(Label2), genLabel(Label1));
            opn1.kind = INT;
            opn1.const_int = 1;
            opn1.type = INT;

            T->code = merge(3, T->code, genIR(ASSIGNOP, opn1, opn2, result), genLabel(Label2));
            break;

        case RELOP: //按算术表达式方式计算布尔值，未写完
            T->type = INT;
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->ptr[1]->offset = T->offset + T->ptr[0]->width;
            Exp(T->ptr[1]);

            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn1.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;

            opn2.kind = ID;
            strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            opn2.isGlobal = symbolTable.symbols[T->ptr[1]->place].level;

            result.kind = ID;
            strcpy(result.id, newLabel());
            if (strcmp(T->type_id, "<") == 0)
                op = JLT;
            else if (strcmp(T->type_id, "<=") == 0)
                op = JLE;
            else if (strcmp(T->type_id, ">") == 0)
                op = JGT;
            else if (strcmp(T->type_id, ">=") == 0)
                op = JGE;
            else if (strcmp(T->type_id, "==") == 0)
                op = EQ;
            else if (strcmp(T->type_id, "!=") == 0)
                op = NEQ;
            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));
            opn1.kind = INT;
            opn1.const_int = 0;
            result2.kind = ID;
            strcpy(result2.id, symbolTable.symbols[T->place].alias);
            result2.offset = symbolTable.symbols[T->place].offset;
            result2.isGlobal = symbolTable.symbols[T->place].level;

            strcpy(Label2, newLabel());
            T->code = merge(4, T->code, genIR(ASSIGNOP, opn1, opn2, result2), genGoto(Label2), genLabel(result.id));
            opn1.const_int = 1;
            T->code = merge(3, T->code, genIR(ASSIGNOP, opn1, opn2, result2), genLabel(Label2));
            break;
        case MINUS:
        case PLUS:
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
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->ptr[0]->width);

            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.type = T->ptr[0]->type;
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn1.isGlobal = symbolTable.symbols[T->ptr[0]->place].level;

            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.type = T->type;
            result.offset = symbolTable.symbols[T->place].offset;
            result.isGlobal = symbolTable.symbols[T->place].level;

            T->code = merge(2, T->code, genIR(UMINUS, opn1, opn2, result));
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
                Exp(T->ptr[0]);                      //处理所有实参表达式求值，及类型
                T->width = T->ptr[0]->width + width; //累加上计算实参使用临时变量的单元数
                T->code = T->ptr[0]->code;
            }
            else if (symbolTable.symbols[rtn].paramnum != 0)
            {
                T->width = width;
                T->code = NULL; //没有参数
                //semantic_error(T->pos, T->type_id, "该函数需要参数");
            }
            match_param(rtn, T); //处理所有参数的匹配
            //处理参数列表的中间代码
            T0 = T->ptr[0];
            while (T0)
            {
                result.kind = ID;
                
                strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
                result.offset = symbolTable.symbols[T0->ptr[0]->place].offset;
                result.offset2=symbolTable.symbols[T0->ptr[0]->num].offset;

                result.isGlobal = symbolTable.symbols[T0->ptr[0]->place].level;
                

                T->code = merge(2, T->code, genIR(ARG, opn1, opn2, result));
                T0 = T0->ptr[1];
            }
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->width - width);
            opn1.kind = ID;
            strcpy(opn1.id, T->type_id); //保存函数名
            opn1.offset = rtn;           //这里offset用以保存函数定义入口,在目标代码生成时，能获取相应信息

            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.offset = symbolTable.symbols[T->place].offset;
            result.isGlobal = symbolTable.symbols[T->place].level;

            T->code = merge(2, T->code, genIR(CALL, opn1, opn2, result)); //生成函数调用中间代码
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
            else if (symbolTable.symbols[rtn].flag == 'V' || symbolTable.symbols[rtn].flag == 'P')
            {
                semantic_error(T->pos, T->type_id, "对非数组变量采用下标形式访问");
                break;
            }
            else
            {
                T->type = symbolTable.symbols[rtn].type;
               // T->offset = symbolTable.symbols[rtn].offset;
                T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
                width = 4;

                Arrayvisit(T, symbolTable.symbols[rtn].info);

                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T->place].alias);
                opn1.offset = symbolTable.symbols[T->place].offset;
                opn1.isGlobal = symbolTable.symbols[T->place].level;

                opn2.kind = INT;
                opn2.const_int = width;

                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->place].alias);
                result.offset = symbolTable.symbols[T->place].offset;
                result.isGlobal = symbolTable.symbols[T->place].level;

                T->code = merge(2, T->code, genIR(STAR, opn1, opn2, result));

                T->num = rtn;

                char alias[20];
                strcpy(alias,symbolTable.symbols[rtn].alias);
                char temps[20];
                strcpy(temps,symbolTable.symbols[T->place].alias);
                strcat(alias,"[");
                strcat(alias,temps);
                strcat(alias,"]");
                strcpy(symbolTable.symbols[T->place].alias,alias);

                //rtn为数组名对应的符号表入口
                //T-typeid为数组名
                //T->place为数组的偏移在符号表中的入口
                //T->code为数组的中间代码
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
            T->code = T->ptr[0]->code;
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                Exp(T->ptr[1]);
                T->width += T->ptr[1]->width;
                T->code = merge(2, T->code, T->ptr[1]->code);
            }
            break;
        default:
            break;
        }
    }
}
