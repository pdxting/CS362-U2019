CFLAGS= -Wall -fpic -coverage -lm -std=c99

all: testme.c
	gcc -o randomQuiz -g testme.c $(CFLAGS)
	./randomQuiz > randomQuiz.out
	
coverage:	
	gcov testme.c >> randomQuiz.out
	
clean:
	rm -f randomQuiz *.gcov *.gcda *.gcno *.out