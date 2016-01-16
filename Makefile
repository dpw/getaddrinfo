CFLAGS=-Wall -Wextra -Werror -g

getaddrinfo: getaddrinfo.o
	gcc -o $@ $^

.PHONY: clean
clean::
	rm -f *.o *~ getaddrinfo
