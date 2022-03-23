#include "server.h"

void	set_socket_address(struct sockaddr_in *socket_address)
{
	// メンバsin_zero は埋め草で、すべて値ゼロに設定するべき
	bzero(socket_address->sin_zero, sizeof(socket_address->sin_zero)/sizeof(socket_address->sin_zero[0]));

	/* サーバーのIPアドレスとポートの情報を設定 */
	socket_address->sin_family = AF_INET;
	socket_address->sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
	socket_address->sin_port = htons(SERVER_PORT);
}

int		send_response(int socket_fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes;

	while (1)
	{
		// クライアントに送るメッセージを入力
		printf("Message: ");
		scanf("%s", buffer);
		bytes = send(socket_fd, buffer, strlen(buffer), DEFAULT_SEND_FALG);
		if (bytes == ERROR)
		{
			printf("Faild to send message to client.\n");
			return (ERROR);
		}
	}
	return (0);
}

int		main(void)
{
	int		socket_fd;
	int		client_socket_fd;
	struct	sockaddr_in socket_address; // socket address for IPv4 Internet protocols

	/*
	** create an endpoint for communication
	** AF_INET: IPv4 Internet protocols
	** SOCK_STREAM: Provides sequenced, reliable, two-way, connection-based byte streams.
	** protocol: 0 indicates TCP here
	*/
	socket_fd = socket(AF_INET, SOCK_STREAM, DEFAULT_SOCKET_PROTOCOL);
	if (socket_fd == ERROR)
	{
		printf("Failed to create socket descriptor.\n");
		return (ERROR);
	}

	set_socket_address(&socket_address);

	// ソケットにアドレスを対応付ける
	if (bind(socket_fd, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_in)) == ERROR)
	{
		printf("Failed to bind address to socket.\n");
		shutdown(socket_fd, SHUT_RDWR);
		return (ERROR);
	}

	// 接続要求の受付
	if (listen(socket_fd, DEFAULT_LISTEN_BACKLOG) == ERROR)
	{
		printf("Failed to listen to connection .\n");
		shutdown(socket_fd, SHUT_RDWR);
		return (ERROR);
	}

	while (1)
	{
		printf("Waiting connection....\n");
		// 接続要求の受け付け
		client_socket_fd = accept(socket_fd, NULL, NULL);
		if (client_socket_fd == ERROR)
		{
			printf("Failed to accept connection\n");
			shutdown(socket_fd, SHUT_RDWR);
			return (ERROR);
		}
		printf("Connection established!\n");

		if (send_response(client_socket_fd) == ERROR)
		{
			shutdown(socket_fd, SHUT_RDWR);
			shutdown(client_socket_fd, SHUT_RDWR);
			return (ERROR);
		}

		shutdown(client_socket_fd, SHUT_RDWR);

		// 次の接続要求に移る
	}
	shutdown(socket_fd, SHUT_RDWR);
	return (0);
}
