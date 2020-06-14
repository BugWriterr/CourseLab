%{
#include "zyp.tab.h"
#include "string.h"
#include "def.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int type_int;
	char type_char[32];
    int type_float;
	char type_id[32];
	char type_string[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL
%}

%option yylineno

ID      [A-Za-z_][A-Za-z0-9_]*  
INT_HEX [0][Xx]([1-9a-fA-F][0-9a-fA-F]*|[0])
INT_OCT	[0][0-7]*
INT     [0-9]+
ERRORINT [0][0-9]+
ERRORID [0-9][a-zA-Z0-9_]*
FLOAT   [0-9]+"."[0-9]+([eE][-+]?([1-9][0-9*]|[0]))? 
CHAR    (\'.\')|(\'\\[^\']*\')
STRING  \"(\\.|[^"\\])*\"

%%

\/\/[^\n]*   {printf("(%s,LINE_COMMENT)\n",yytext);} //行注释
"/*" 		{

				char c;
				do{
					while((c=input())!='*');
					c=input();
				}
				while(c!='/');
				printf("(%BLOCK_COMMENT)\n");
			} //块注释

"int"    {printf("(%s, INT)\n", yytext);strcpy(yylval.type_id, yytext);return TYPE;}
"float"  {printf("(%s, FLOAT)\n", yytext);strcpy(yylval.type_id, yytext);return TYPE;}
"char"   {printf("(%s, CHAR)\n", yytext);strcpy(yylval.type_id, yytext);return TYPE;}
"string" {printf("(%s, STRING)\n",yytext);strcpy(yylval.type_id,yytext);return TYPE;}

"struct" {printf("(%s, STRUCT)\n",yytext);strcpy(yylval.type_id,yytext);return STRUCT;}



"if"     	{printf("(%s, IF)\n", yytext);return IF;}
"else"   	{printf("(%s, ELSE)\n", yytext);return ELSE;}
"while"  	{printf("(%s, WHILE)\n", yytext);return WHILE;}
"for"		{printf("(%s, FOR)\n", yytext);return FOR;}
"break"	 	{printf("(%s, break)\n",yytext);return BREAK;}
"continue" 	{printf("(%s, CONTINUE)\n", yytext);return CONTINUE;} //continue
"return" 	{printf("(%s, RETURN)\n", yytext);return RETURN;}
"switch"	{printf("(%s, SWITCH)\n", yytext);return SWITCH;}
"case"		{printf("(%s, CASE)\n", yytext);return CASE;}
"default"	{printf("(%s, DEFAULT)\n", yytext);return DEFAULT;}



{ID}        {printf("(%s, ID)\n",yytext);strcpy(yylval.type_id,yytext);return ID;}

{INT_OCT}	{
				int length=strlen(yytext);
				int i=0,num=0;
				for(i=1;i<length;i++){
					num=num*8+yytext[i]-'0';
				}
				printf("(%s=%d,INT_OCT)\n",yytext,num);
				yylval.type_int=num;
				return INT;
			}
{ERRORINT}	{printf("(%s, ERRORINT) INT类型不允许0开头!\n),yytext");}
{INT}		{printf("(%s, INT)\n",yytext);yylval.type_int=atoi(yytext);return INT;}
{INT_HEX}	{
				int length=strlen(yytext);
				int i=0;
				int num=0;
				for(i=2;i<length;i++){
					char c=yytext[i];
					if('0'<=c&&c<='9')
					{
						c=c-'0';
						num=num*16+c;
					}
					else if('A'<=c&&c<='F')
					{
						c=c-'A'+10;
						num=num*16+c;
					}
					else if('a'<=c&&c<='f')
					{
						c=c-'a'+10;
						num=num*16+c;
					}
				}

				printf("(%s=%d,INT_HEX)\n",yytext,num);
				yylval.type_int=num;
				return INT;
			}

{ERRORID}   {printf("(%s, ERRORID:ID禁止以数字开头)\n",yytext);}
{FLOAT}		{printf("(%s, FLOAT)\n",yytext);yylval.type_float=atof(yytext);return FLOAT;}
{CHAR}		{printf("(%s, CHAR)\n",yytext);strcpy(yylval.type_char,yytext);return CHAR;}
{STRING}	{printf("(%s, STRING)\n",yytext);strcpy(yylval.type_string,yytext);return STRING;}

";"			{printf("(%s,SEMI)\n",yytext);return SEMI;}
","			{printf("(%s,COMMA)\n",yytext);return COMMA;}
"."         {printf("(%s,DOT)\n",yytext);return DOT;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);printf("(%s,RELOP)\n",yytext);return RELOP;}
"="			{printf("(%s,ASSIGN)\n",yytext);return ASSIGNOP;}
"+"			{printf("(%s,PLUS)\n",yytext);return PLUS;}
"-"			{printf("(%s,MINUS)\n",yytext);return MINUS;}
"*"			{printf("(%s,STAR)\n",yytext);return STAR;}
"/"			{printf("(%s,DIV)\n",yytext);return DIV;}
"%"			{printf("(%s,MOD)\n",yytext);return MOD;}
"&&"        {printf("(%s,AND)\n",yytext);return AND;}
"||"        {printf("(%s,OR)\n",yytext);return OR;}
"!"			{printf("(%s,NOT)\n",yytext);return NOT;}
"++"		{printf("(%s,AUTOPLUS)\n",yytext);return AUTOPLUS;}
"--"		{printf("(%s,AUTOMINUS)\n",yytext);return AUTOMINUS;}
"+="		{printf("(%s,PLUSASSIGN)\n",yytext);return PLUSASSIGNOP;}
"-="		{printf("(%s,MINUSASSIGN)\n",yytext);return MINUSASSIGNOP;}
"*="		{printf("(%s,STARASSIGN)\n",yytext);return STARASSIGNOP;}
"/="		{printf("(%s,DIVSASSIGN)\n",yytext);return DIVASSIGNOP;}
"%="		{printf("(%s,MODASSIGN)\n",yytext);return MODASSIGNOP;}
"("			{printf("(%s,LP)\n",yytext);return LP;}
")"			{printf("(%s,RP)\n",yytext);return RP;}
"{"			{printf("(%s,LC)\n",yytext);return LC;}
"}"			{printf("(%s,RC)\n",yytext);return RC;}
"["         {printf("(%s,LB)\n",yytext);return LB;}
"]"         {printf("(%s,RB)\n",yytext);return RB;}


[\n]        {printf("(\\n,EOL)\n");yycolumn=1;}   
[ \r\t]          {}   
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}



%%
/* 还需要识别注释*/ 
/*
和bison联用时，不需要这部分

void main()
{
yylex();
return 0;
}
*/

int yywrap()
{
return 1;
}
