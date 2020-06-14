#include"def.h"
//生成临时变量用插入到符号表中
char *strcat0(char *s1, char *s2);
char *newAlias();
char *newLabel();
char *newTemp();

//语义分析函数
void semantic_Analysis0(struct ASTNode *T);
void semantic_Analysis(struct ASTNode *T);
void semantic_error(int line,char *msg1,char *msg2);
void prnArray(struct ArrayInfo *T);
void prn_symbol();
int searchSymbolTable(char *name) ;
int fillSymbolTable(char *name,char *alias,int level,int type,char flag,int offset);
int fill_Temp(char *name,int level,int type,char flag,int offset);
int match_param(int i,struct ASTNode *T);


//语义分析中的函数
//处理不同类型的结点

void ext_def_list(struct ASTNode *T);//外部定义列表
void ext_var_def(struct ASTNode *T);//单个外部变量定义
void ext_var_list(struct ASTNode *T);//处理外部定义的标识符序列
void func_def(struct ASTNode *T);//函数声明
void func_dec(struct ASTNode *T);//函数名加函数参数列表
void param_list(struct ASTNode *T);//形参列表
void param_dec(struct ASTNode *T);//单个形参
void comp_stm(struct ASTNode *T);//复合语句
void def_list(struct ASTNode *T);//复合语句内的声明列表
void var_def(struct ASTNode *T);//VAR_DEF,定义局部变量
void stm_list(struct ASTNode *T);//处理语句列表
void if_then(struct ASTNode *T);
void if_then_else(struct ASTNode *T);
void while_handle(struct ASTNode *T);
void exp_stmt(struct ASTNode *T);
void return_handle(struct ASTNode *T);



void ext_struct_def(struct ASTNode *T);
void struct_def(struct ASTNode *T);
void struct_dec(struct ASTNode *T);
void array_dec(struct ASTNode *T);



//处理exp的函数
void boolExp(struct ASTNode *T);
void Exp(struct ASTNode *T);

//为了代码可读性Exp调用下列函数
void IdExp(struct ASTNode *T );
void IntExp(struct ASTNode *T );
void FloatExp(struct ASTNode *T );
void CharExp(struct ASTNode *T );
void StringExp(struct ASTNode *T );
void AssignopExp(struct ASTNode *T );//处理各种赋值
void MathOpExp(struct ASTNode *T);//+-*/%等算术运算
void RelopExp(struct ASTNode *T );//对于比较运算符
void AutoAddMinus(struct ASTNode *T );//自增自减运算符
void CallFunExp(struct ASTNode *T);//调用函数
struct ArrayInfo * ArrayHandle(struct ASTNode *P);
void Arrayvisit(struct ASTNode* T,struct ArrayInfo* info);

//需补充
void ArgsExp(struct ASTNode *T);

//
// void semantic_Analysis0(struct ASTNode *T);
// void semantic_Analysis(struct ASTNode *T);
// void boolExp(struct ASTNode *T);
// void Exp(struct ASTNode *T);
// void objectCode(struct codenode *head);









