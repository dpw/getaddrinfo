# gaiquery

This is a simple program that calls getaddrinfo(3) and displays the
results.

## Usage

To build do:

    make

And then

    ./gaiquery <hostname> <port number or service name>

E.g.

    $ ./gaiquery google.com http
    AF_INET SOCK_STREAM tcp 209.85.227.147 80 google.com
    AF_INET SOCK_STREAM tcp 209.85.227.99 80
    AF_INET SOCK_STREAM tcp 209.85.227.103 80
    AF_INET SOCK_STREAM tcp 209.85.227.104 80
    AF_INET SOCK_STREAM tcp 209.85.227.105 80
    AF_INET SOCK_STREAM tcp 209.85.227.106 80
