# getaddrinfo

This is a simple program that calls
[getaddrinfo(3)](http://man7.org/linux/man-pages/man3/getaddrinfo.3.html)
and displays the results.

## Usage

To build do:

    make

And then

    ./getaddrinfo <hostname> <port number or service name>

E.g.

    $ ./getaddrinfo google.com http
    AF_INET SOCK_STREAM tcp 216.58.213.78 80 google.com
    AF_INET SOCK_DGRAM udp 216.58.213.78 80
    AF_INET6 SOCK_STREAM tcp 2a00:1450:4009:810::200e 80
    AF_INET6 SOCK_DGRAM udp 2a00:1450:4009:810::200e 80
