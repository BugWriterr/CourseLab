t:
	flex zyp.l
	bison -d zyp.y 
	gcc lex.yy.c zyp.tab.c ast.c -o zyp

flex:zyp.l
	flex zyp.l
bison:zyp.y
	bison -d zyp.y
all:zyp.l zyp.y
	flex zyp.l
	bison -d zyp.y
result:wl83.l wl83.y ast2.c
	flex wl83.l
	bison -d wl83.y
	gcc lex.yy.c wl83.tab.c ast2.c -o wl83
	./wl83 test.c
test:zyp.l zyp.y ast.c
	flex zyp.l
	bison -d zyp.y
	gcc lex.yy.c zyp.tab.c ast.c -o zyp
	./zyp test.c
out:lex.yy.c zyp.tab.c ast.c
	gcc lex.yy.c zyp.tab.c ast.c -o a.exe
	a.exe test.c
output:test.c
	a.exe test.c
clean:lex.yy.c zyp.tab.c zyp.tab.h zyp.exe
	rm lex.yy.c zyp.tab.c zyp.tab.h zyp.exe
conflict:zyp.y
	bison -d -v zyp.y