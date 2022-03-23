#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <string.h>
# include <sys/socket.h> // socket, connect
# include <netinet/in.h> // sockaddr_in
# include <arpa/inet.h> // inet_addr,

# define DEFAULT_SOCKET_PROTOCOL 0
# define ERROR -1
# define SERVER_ADDRESS "127.0.0.1"
# define SERVER_PORT 8080
# define BUFFER_SIZE 1024
# define DEFAULT_LISTEN_BACKLOG 128 // キューに入れるべき保留中の接続要求個数
# define DEFAULT_SEND_FALG 0

#endif
