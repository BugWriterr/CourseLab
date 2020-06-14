t:
	flex zyp.l
	bison -d zyp.y 
	gcc -g lex.yy.c zyp.tab.c ast.c Semantic.c SemanticHandle.c ExpHandle.c code.c -o zyp
	./zyp mytest.c > out.txt
	
test:
	./zyp test.c > out.txt
test1:
	./zyp test1.c > out.txt
test2:
	./zyp test2.c > out.txt
test3:
	./zyp test3.c > out.txt
test4:
	./zyp test4.c > out.txt
test5:
	./zyp test5.c > out.txt
mytest:
	./zyp mytest.c > out.txt
clean:lex.yy.c zyp.tab.c zyp.tab.h
	-rm -rf  lex.yy.c zyp.tab.c zyp.tab.h zyp