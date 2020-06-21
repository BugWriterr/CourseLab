#include"def.h"

//生成临时变量用插入到符号表中
//中间代码生成


//复制s2到s1
char *strcat0(char *s1, char *s2);
//生成一个ID别名
char *newAlias();
//产生一个新标号
char *newLabel();
//产生一个新的临时变量
char *newTemp();

//生成一条TAC代码的结点组成的双向循环链表，返回头指针
struct codenode *genIR(int op, struct opn opn1, struct opn opn2, struct opn result);

//生成一条标号语句，返回头指针
struct codenode *genLabel(char *label);

//生成GOTO语句，返回头指针
struct codenode *genGoto(char *label);

// 合并多个中间代码的双向循环链表，首尾相连
struct codenode *merge(int num, ...);

//输出中间代码
void prnIR(struct codenode *head);

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
void for_handle(struct ASTNode* T);

//计算数组的元素个数
int countArray(struct ArrayInfo *info );



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
void OPAssignopExp(struct ASTNode *T );//处理复合赋值
void MathOpExp(struct ASTNode *T);//+-*/%等算术运算
void RelopExp(struct ASTNode *T );//对于比较运算符
void AutoAddMinus(struct ASTNode *T );//自增自减运算符
void CallFunExp(struct ASTNode *T);//调用函数
struct ArrayInfo * ArrayHandle(struct ASTNode *P);
void Arrayvisit(struct ASTNode* T,struct ArrayInfo* info);

//需补充
void ArgsExp(struct ASTNode *T);



//目标代码生成
 void objectCode(struct codenode *head);
 int isGlbVar(char *alias);









