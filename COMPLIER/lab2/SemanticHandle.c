#include "Semantic.h"
#define DEBUG 0

void ext_def_list(struct ASTNode *T) //对于节点为EXT_DEF_LIST类型的
{
    if (!T->ptr[0])
        return;
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]); //访问外部定义列表中的第一个
    if (T->ptr[1])
    {
        T->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
        semantic_Analysis(T->ptr[1]); //访问该外部定义列表中的其它外部定义
    }
    return;
}

void ext_var_def(struct ASTNode *T)
{
    //这里假定外部变量不支持初始化

    T->type = T->ptr[0]->type;
    T->ptr[1]->type = T->ptr[0]->type;

    //将一个变量的宽度向下传递
    if (strcmp(T->ptr[0]->type_id, "int") == 0)
    {
        T->ptr[1]->width = 4;
    }
    else if (strcmp(T->ptr[0]->type_id, "float") == 0)
    {
        T->ptr[1]->width = 4;
    }
    else if (strcmp(T->ptr[0]->type_id, "char") == 0)
    {
        T->ptr[1]->width = 1;
    }
    //string类型的宽度是怎么计算,假定为32位8个字节
    else if (strcmp(T->ptr[0]->type_id, "string") == 0)
    {
        T->ptr[1]->width = 8;
    }
    T->ptr[1]->offset = T->offset;                    //这个外部变量的偏移量向下传递
    ext_var_list(T->ptr[1]);                          //处理外部变量说明中的标识符序列
    T->width = (T->ptr[1]->width) * (T->ptr[1]->num); //计算这个外部变量说明的宽度
}

void ext_var_list(struct ASTNode *T)
{ //处理变量列表
    int rtn, num = 1;
    switch (T->kind)
    {
    case EXT_DEC_LIST:
        T->ptr[0]->type = T->type;                //将类型属性向下传递变量结点
        T->ptr[0]->offset = T->offset;            //外部变量的偏移量向下传递
        T->ptr[1]->type = T->type;                //将类型属性向下传递变量结点
        T->ptr[1]->offset = T->offset + T->width; //外部变量的偏移量向下传递
        T->ptr[1]->width = T->width;
        ext_var_list(T->ptr[0]);
        ext_var_list(T->ptr[1]);
        T->num = T->ptr[1]->num + 1;
        break;
    case ID:
        rtn = fillSymbolTable(T->type_id, "", LEV, T->type, 'V', T->offset); //最后一个变量名
        if (rtn == -1)
            semantic_error(T->pos, T->type_id, "变量重复定义");
        else
        {
            T->place = rtn;
            T->num = 1;
        }
        break;

    //处理数组的情况
    case ARRAYLIST:
        rtn = fillSymbolTable(T->type_id, "", LEV, T->type, 'A', T->offset);
        if (rtn == -1)
        {
            semantic_error(T->pos, T->type_id, "数组名已重复定义");
            break;
        }
        else
        {
            struct ArrayInfo *temp =
                ArrayHandle(T);
            if (temp == NULL)
            {
                break;
            }
            T->place = rtn;
            symbolTable.symbols[rtn].info = temp;
        }
        break;
    }
}
struct ArrayInfo *ArrayHandle(struct ASTNode *P) //数组处理
{
    struct ASTNode *T = P;
    T = T->ptr[0];
    struct ArrayInfo *info = NULL;
    info = (struct ArrayInfo *)malloc(sizeof(struct ArrayInfo));
    info->dim = 0;
    memset(info->diminfo, 0, sizeof(info->diminfo));
    info->type = P->type;
    while (T)
    {
        if (T->kind == INT)
        {
            if (T->type_int <= 0)
            {
                semantic_error(P->pos, P->type_id, "数组大小只能大于0");
                return NULL;
            }
            info->diminfo[info->dim][2] = T->type_int;
            info->diminfo[info->dim][0] = 0;
            info->diminfo[info->dim][1] = T->type_int - 1;
            info->dim++;
            if (info->dim > MAXDIM)
            {
                semantic_error(P->pos, P->type_id, "数组维数超出");
                return NULL;
            }
            T=T->ptr[0];
        }
        else if (T->kind == ARRAYLIST)
        {
            if (T->ptr[0]->kind == INT)
            {
                if (T->ptr[0]->type_int <= 0)
                {
                    semantic_error(P->pos, P->type_id, "数组大小只能大于0");
                    return NULL;
                }
                info->diminfo[info->dim][2] = T->ptr[0]->type_int;
                info->diminfo[info->dim][0] = 0;
                info->diminfo[info->dim][1] = T->ptr[0]->type_int - 1;
                info->dim++;
                if (info->dim > MAXDIM)
                {
                    semantic_error(P->pos, P->type_id, "数组维数超出");
                    return NULL;
                }
                T = T->ptr[1];
            }
        }
    }
    return info;
}
void func_def(struct ASTNode *T)
{
    return_flag++;
    //获取函数返回类型送到含函数名、参数的结点
    T->ptr[1]->type = T->ptr[0]->type;
    //函数的宽度设置为0，不会对外部变量的地址分配产生影响
    T->width = 0;
    T->offset = DX;                //设置局部变量在活动记录中的偏移量初值
    semantic_Analysis(T->ptr[1]);  //处理函数名和参数结点部分，这里不考虑用寄存器传递参数
    T->offset += T->ptr[1]->width; //用形参单元宽度修改函数局部变量的起始偏移量
    T->ptr[2]->offset = T->offset;
    //strcpy(T->ptr[2]->Snext, newLabel()); //函数体语句执行结束后的位置属性
    semantic_Analysis(T->ptr[2]); //处理函数体结点
    //计算活动记录大小,这里offset属性存放的是活动记录大小，不是偏移
    if(return_flag!=0)
    {
        semantic_error(T->pos,T->ptr[1]->type_id,"函数需要返回语句");
        return_flag=0;
        return ;
    }
    symbolTable.symbols[T->ptr[1]->place].offset = T->offset + T->ptr[2]->width;
}
void func_dec(struct ASTNode *T)
{

    int rtn;                                                     //返回的是符号在符号表中的位置序号
    rtn = fillSymbolTable(T->type_id, "", LEV, T->type, 'F', 0); //函数不在数据区中分配单元，偏移量为0
    if (rtn == -1)
    {
        semantic_error(T->pos, T->type_id, "函数重复定义");
        return;
    }
    else
        T->place = rtn;

    T->offset = DX; //设置形式参数在活动记录中的偏移量初值
    if (T->ptr[0])
    { //判断是否有参数
        T->ptr[0]->offset = T->offset;
        semantic_Analysis(T->ptr[0]); //处理函数参数列表
        T->width = T->ptr[0]->width;
        symbolTable.symbols[rtn].paramnum = T->ptr[0]->num;
    }
    else
    {
        symbolTable.symbols[rtn].paramnum = 0;
        T->width = 0;
    }
}

void param_list(struct ASTNode *T) //处理形式参数列表
{
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);
    if (T->ptr[1])
    {
        T->ptr[1]->offset = T->offset + T->ptr[0]->width;
        semantic_Analysis(T->ptr[1]);
        T->num = T->ptr[0]->num + T->ptr[1]->num;       //统计参数个数
        T->width = T->ptr[0]->width + T->ptr[1]->width; //累加参数单元宽度
    }
    else
    {
        T->num = T->ptr[0]->num;
        T->width = T->ptr[0]->width;
    }
}

void param_dec(struct ASTNode *T) //单个形式参数
{
    int rtn = fillSymbolTable(T->ptr[1]->type_id, "", 1, T->ptr[0]->type, 'P', T->offset);
    if (rtn == -1)
        semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "参数名重复定义");
    else
        T->ptr[1]->place = rtn;
    T->num = 1; //参数个数计算的初始值
    //参数宽度
    if (strcmp(T->ptr[0]->type_id, "int") == 0)
    {
        T->width = 4;
    }
    else if (strcmp(T->ptr[0]->type_id, "float") == 0)
    {
        T->width = 4;
    }
    else if (strcmp(T->ptr[0]->type_id, "char") == 0)
    {
        T->width = 1;
    }
    else if (strcmp(T->ptr[0]->type_id, "string") == 0)
    {
        T->width = 8;
    }
}
//处理comst
void comp_stm(struct ASTNode *T)
{
    LEV++;
    //设置层号加1，并且保存该层局部变量在符号表中的起始位置在symbol_scope_TX
    symbol_scope_TX.TX[symbol_scope_TX.top++] = symbolTable.index;
    T->width = 0;
    T->code = NULL;
    if (T->ptr[0]) //deflist
    {
        T->ptr[0]->offset = T->offset;
        semantic_Analysis(T->ptr[0]); //处理该层的局部变量DEF_LIST
        T->width += T->ptr[0]->width;
    }
    if (T->ptr[1]) //stmlist
    {
        T->ptr[1]->offset = T->offset + T->width;
        semantic_Analysis(T->ptr[1]); //处理复合语句的语句序列
        T->width += T->ptr[1]->width;
    }
if (DEBUG){
    prn_symbol(); //c在退出一个符合语句前显示的符号表
    getchar();
}
    LEV--;                                                         //出复合语句，层号减1
    symbolTable.index = symbol_scope_TX.TX[--symbol_scope_TX.top]; //删除该作用域中的符号
}

void def_list(struct ASTNode *T)
{
    if (T->ptr[0]) //def，类型为VAR_DEF
    {
        T->ptr[0]->offset = T->offset;
        semantic_Analysis(T->ptr[0]); //处理一个局部变量定义
        T->width = T->ptr[0]->width;
    }
    if (T->ptr[1]) //def_list 类型为DEF_LIST
    {
        T->ptr[1]->offset = T->offset + T->ptr[0]->width;
        semantic_Analysis(T->ptr[1]); //处理剩下的局部变量定义
        T->width += T->ptr[1]->width;
    }
}

void var_def(struct ASTNode *T)
{
    int rtn, width, num;
    struct ASTNode *T0 = NULL;
    T->type = T->ptr[0]->type;
    T->ptr[1]->type = T->ptr[0]->type; //确定变量序列各变量类型

    if (strcmp(T->ptr[0]->type_id, "int") == 0)
    {
        width = 4;
    }
    else if (strcmp(T->ptr[0]->type_id, "float") == 0)
    {
        width = 4;
    }
    else if (strcmp(T->ptr[0]->type_id, "char") == 0)
    {
        width = 1;
    }
    //string类型的宽度是怎么计算,假定为32位8个字节
    else if (strcmp(T->ptr[0]->type_id, "string") == 0)
    {
        width = 8;
    }

    T0 = T->ptr[1]; //T0为变量名列表子树根指针，对ID、ASSIGNOP类结点在登记到符号表，作为局部变量
    num = 0;
    T0->offset = T->offset;
    T->width = 0;
    while (T0)
    { //处理所以DEC_LIST结点
        num++;
        T0->ptr[0]->type = T0->type; //类型属性向下传递
        if (T0->ptr[1])
            T0->ptr[1]->type = T0->type;
        T0->ptr[0]->offset = T0->offset; //类型属性向下传递
        if (T0->ptr[1])
            T0->ptr[1]->offset = T0->offset + width;
        if (T0->ptr[0]->kind == ID)
        {
            rtn = fillSymbolTable(T0->ptr[0]->type_id, "", LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //此处偏移量未计算，暂时为0
            if (rtn == -1)
                semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "变量重复定义");
            else
                T0->ptr[0]->place = rtn;
            T->width += width;
        }
        else if(T0->ptr[0]->kind == ARRAYLIST)
        {
            rtn=fillSymbolTable(T0->ptr[0]->type_id,"",LEV,T0->ptr[0]->type,'A',T->offset+T->width);
            if (rtn == -1)
                semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "数组重复定义");
            else
            {
                struct ArrayInfo *temp=ArrayHandle(T0->ptr[0]);
                if(temp==NULL)  break;
                T0->ptr[0]->place = rtn;
                symbolTable.symbols[rtn].info=temp;
            }  
            T->width += width;
        }
        else if (T0->ptr[0]->kind == ASSIGNOP)
        {
            rtn = fillSymbolTable(T0->ptr[0]->ptr[0]->type_id, "", LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //此处偏移量未计算，暂时为0
            if (rtn == -1)
                semantic_error(T0->ptr[0]->ptr[0]->pos, T0->ptr[0]->ptr[0]->type_id, "变量重复定义");
            else
            {
                T0->ptr[0]->place = rtn;
                T0->ptr[0]->ptr[1]->offset = T->offset + T->width + width;
                Exp(T0->ptr[0]->ptr[1]);
            }
            T->width += width + T0->ptr[0]->ptr[1]->width;
        }
        T0 = T0->ptr[1];
    }
}

void stm_list(struct ASTNode *T) //StmList
{
    if (!T->ptr[0])
    {
        T->code = NULL;
        T->width = 0;
        return;
    } //空语句序列
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);
    T->width = T->ptr[0]->width;
    if (T->ptr[1])
    {                                  //2条以上语句连接,S.next属性向下传递
        T->ptr[1]->offset = T->offset; //顺序结构共享单元方式
                                       //                  T->ptr[1]->offset=T->offset+T->ptr[0]->width; //顺序结构顺序分配单元方式
        semantic_Analysis(T->ptr[1]);
        if (T->ptr[1]->width > T->width)
            T->width = T->ptr[1]->width; //顺序结构共享单元方式
                     T->width+=T->ptr[1]->width;//顺序结构顺序分配单元方式
    }
}

void if_then(struct ASTNode *T) //处理if
{
    T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
    boolExp(T->ptr[0]); //处理条件表达式
    T->width = T->ptr[0]->width;
    semantic_Analysis(T->ptr[1]); //if子句
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
}

void if_then_else(struct ASTNode *T) //处理if else
{
    T->ptr[0]->offset = T->ptr[1]->offset = T->ptr[2]->offset = T->offset;
    boolExp(T->ptr[0]); //条件，要单独按短路代码处理
    T->width = T->ptr[0]->width;
    semantic_Analysis(T->ptr[1]); //if子句
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
    semantic_Analysis(T->ptr[2]); //else子句
    if (T->width < T->ptr[2]->width)
        T->width = T->ptr[2]->width;
}

void while_handle(struct ASTNode *T) //处理while子句
{
    T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
    boolExp(T->ptr[0]); //循环条件，要单独按短路代码处理
    T->width = T->ptr[0]->width;
    flag++;//
    semantic_Analysis(T->ptr[1]); //循环体
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
    flag--;
}

void exp_stmt(struct ASTNode *T) //处理exp子句表达式子句
{
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);
    T->width = T->ptr[0]->width;
}

void return_handle(struct ASTNode *T)
{
    int rtn, num;
    num = symbolTable.index - 1;
    while (symbolTable.symbols[num].flag != 'F')
        num--; //得到最近的调用函数返回类型
    return_flag=0;
    if (T->ptr[0])
    {
        T->ptr[0]->offset = T->offset;
        Exp(T->ptr[0]);

        /*需要判断返回值类型是否匹配*/
        if (T->ptr[0]->type != symbolTable.symbols[num].type) //返回类型不匹配
        {
            semantic_error(T->pos, "返回值类型错误", "");
            T->width = 0;
            return;
        }
        T->width = T->ptr[0]->width;
    }
    else //没返回什么东西
    {
        T->width = 0;
        semantic_error(T->pos, "返回值类型错误", "返回值不能为void!");
    }
    
}

void semantic_error(int line, char *msg1, char *msg2)
{
    //这里可以只收集错误信息，最后一次显示
    printf("在%d行,%s %s\n", line, msg1, msg2);
}
void prnArray(struct ArrayInfo *T)
{
    char *symbolsType;
    if (T->type == INT)
    {
        symbolsType = "int";
    }
    if (T->type == FLOAT)
    {
        symbolsType = "float";
    }
    if (T->type == CHAR)
    {
        symbolsType = "char";
    }
    if (T->type == STRING)
    {
        symbolsType = "string";
    }
    printf("数组信息:\n");
    printf("  %6s  %6s  \n", "维数", "元素类型");
    printf("%6d%6s  \n", T->dim,symbolsType);
    printf("  %6s  %6s  %6s\n", "下界", "上界","大小");
    for(int i=0;i<T->dim;i++)
    {
        printf("%6d%6d%6d\n",T->diminfo[i][0],T->diminfo[i][1],T->diminfo[i][2]);
    }
}
void prn_symbol()
{ //显示符号表
    int i = 0;
    char *symbolsType;
    printf("  %6s  %6s   %6s   %6s  %4s  %6s\n", "变量名", "别名", "层号", "类型", "标记", "偏移量");
    for (i = 0; i < symbolTable.index; i++)
    {
        if (symbolTable.symbols[i].type == INT)
        {
            symbolsType = "int";
        }
        if (symbolTable.symbols[i].type == FLOAT)
        {
            symbolsType = "float";
        }
        if (symbolTable.symbols[i].type == CHAR)
        {
            symbolsType = "char";
        }
        if (symbolTable.symbols[i].type == STRING)
        {
            symbolsType = "string";
        }
        printf("%6s %6s %6d  %6s %4c %6d\n", symbolTable.symbols[i].name,
               symbolTable.symbols[i].alias, symbolTable.symbols[i].level,
               symbolsType,
               symbolTable.symbols[i].flag, symbolTable.symbols[i].offset);
        if(symbolTable.symbols[i].flag=='A')
            prnArray(symbolTable.symbols[i].info);
    }
}

int searchSymbolTable(char *name)
{
    int i, flag = 0;
    for (i = symbolTable.index - 1; i >= 0; i--)
    {
        if (symbolTable.symbols[i].level == 0)
            flag = 1;
        if (flag && symbolTable.symbols[i].level == 1)
            continue; //跳过前面函数的形式参数表项
        if (!strcmp(symbolTable.symbols[i].name, name))
            return i;
    }
    return -1;
}
int fillSymbolTable(char *name, char *alias, int level, int type, char flag, int offset)
{
    //首先根据name查符号表，不能重复定义 重复定义返回-1
    int i;
    /*符号查重，考虑外部变量声明前有函数定义，
    其形参名还在符号表中，这时的外部变量与前函数的形参重名是允许的*/
    for (i = symbolTable.index - 1; i >= 0 && (symbolTable.symbols[i].level == level || level == 0); i--)
    {
        if (level == 0 && symbolTable.symbols[i].level == 1)
            continue; //外部变量和形参不必比较重名
        if (!strcmp(symbolTable.symbols[i].name, name))
            return -1;
    }
    //填写符号表内容
    strcpy(symbolTable.symbols[symbolTable.index].name, name);
    strcpy(symbolTable.symbols[symbolTable.index].alias, alias);
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
    return symbolTable.index++; //返回的是符号在符号表中的位置序号，中间代码生成时可用序号取到符号别名
}

//填写临时变量到符号表，返回临时变量在符号表中的位置
int fill_Temp(char *name, int level, int type, char flag, int offset)
{
    strcpy(symbolTable.symbols[symbolTable.index].name, "");
    strcpy(symbolTable.symbols[symbolTable.index].alias, name);
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
    return symbolTable.index++; //返回的是临时变量在符号表中的位置序号
}

int match_param(int i, struct ASTNode *T)
{
    int j, num = symbolTable.symbols[i].paramnum;
    int type1, type2, pos = T->pos;
    T = T->ptr[0];
    if (num == 0 && T == NULL)
        return 1;
    for (j = 1; j <= num; j++)
    {
        if (!T)
        {
            semantic_error(pos, "", "函数调用参数太少!");
            return 0;
        }
        type1 = symbolTable.symbols[i + j].type; //形参类型
        type2 = T->ptr[0]->type;
        if (type1 != type2)
        {
            semantic_error(pos, "", "参数类型不匹配");
            return 0;
        }
        T = T->ptr[1];
    }
    if (T)
    { //num个参数已经匹配完，还有实参表达式
        semantic_error(pos, "", "函数调用参数太多!");
        return 0;
    }
    return 1;
}

char *strcat0(char *s1, char *s2)
{
    static char result[10];
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *newAlias()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    // itoa(no++, s, 10);
    return strcat0("v", s);
}

char *newLabel()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    // itoa(no++, s, 10);
    return strcat0("label", s);
}

char *newTemp()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    // itoa(no++, s, 10);
    return strcat0("temp", s);
}