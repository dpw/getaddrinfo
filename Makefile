CFLAGS=-Wall -Wextra -Werror -g

gaiquery: gaiquery.o
	gcc -o $@ $^

.PHONY: clean
clean::
	rm -f *.o *~ gaiquery
