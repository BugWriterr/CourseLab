t:
	flex zyp.l
	bison -d zyp.y 
	gcc -g lex.yy.c zyp.tab.c ast.c Semantic.c SemanticHandle.c ExpHandle.c -o zyp
test:
	./zyp test.c


clean:lex.yy.c zyp.tab.c zyp.tab.h
	-rm -rf  lex.yy.c zyp.tab.c zyp.tab.h zyp