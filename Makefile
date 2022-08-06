wish: wish.o token.o commands.o
	gcc -o wish wish.o token.o commands.o

wish.o: wish.c token.h commands.h
	gcc -c wish.c -Wall -Werror

token.o: token.c token.h
	gcc -c token.c -Wall -Werror

commands.o: commands.c commands.h
	gcc -c commands.c -Wall -Werror

clean:
	rm -f *.o wish
