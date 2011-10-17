/* A simple program to display getaddrinfo(3) results.
 *
 * Run with a host and a port, and it will query getaddrinfo and show
 * the results.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static char *afstr(int af)
{
	switch (af) {
	case AF_INET:
		return "AF_INET";
	case AF_INET6:
		return "AF_INET6";
	default:
		return "<unknown address family>";
	}
}

static char *socktypestr(int st)
{
	switch (st) {
	case SOCK_STREAM:
		return "SOCK_STREAM";
	case SOCK_DGRAM:
		return "SOCK_DGRAM";
	case SOCK_SEQPACKET:
		return "SOCK_SEQPACKET";
	default:
		return "<unknown socktype>";
	}
}

int main(int argc, char *argv[])
{
	char *host;
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s;
	char buf[1000];

	if (argc < 3) {
		fprintf(stderr, "Usage: %s host port\n", argv[0]);
		return 1;
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_CANONNAME;

	/* If the host is empty, turn on AI_PASSIVE */
	host = argv[1];
	if (*host == 0) {
		hints.ai_flags = AI_PASSIVE;
		host = NULL;
	}

	s = getaddrinfo(host, argv[2], &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return 1;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		const char *addr;
		int port;
		struct protoent *pe = getprotobynumber(rp->ai_protocol);

		switch (rp->ai_family) {
		case AF_INET: {
			struct sockaddr_in *sin
				= (struct sockaddr_in *)rp->ai_addr;
			addr = inet_ntop(rp->ai_family, &sin->sin_addr,
					 buf, sizeof buf);
			port = ntohs(sin->sin_port);
			break;
		}
		case AF_INET6: {
			struct sockaddr_in6 *sin
				= (struct sockaddr_in6 *)rp->ai_addr;
			addr = inet_ntop(rp->ai_family, &sin->sin6_addr,
					 buf, sizeof buf);
			port = ntohs(sin->sin6_port);
			break;
		}
		default:
			addr = "<unknown address family>";
			port = -1;
			break;
		}

		printf("%s %s %s %s %d %s\n",
		       afstr(rp->ai_family),
		       socktypestr(rp->ai_socktype),
		       pe->p_name,
		       addr, port,
		       rp->ai_canonname ? rp->ai_canonname : "");
	}

	return 0;
}
