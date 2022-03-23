#include "client.h"

void set_socket_address(struct sockaddr_in *socket_address)
{
	// メンバsin_zero は埋め草で、すべて値ゼロに設定するべき
	bzero(socket_address->sin_zero, sizeof(socket_address->sin_zero)/sizeof(socket_address->sin_zero[0]));

	/* サーバーのIPアドレスとポートの情報を設定 */
	socket_address->sin_family = AF_INET;
	socket_address->sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
	socket_address->sin_port = htons(SERVER_PORT);
}

int get_response(int socket_fd) {
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes;

	while (1) {

		// サーバーからの応答を受信
		bytes = recv(socket_fd, &buffer, BUFFER_SIZE, DEFAULT_RECV_FALG);
		if (bytes == ERROR) {
			printf("recv error\n");
			return (ERROR);
		}

		if (bytes == 0) {
			// 受信サイズが 0 の場合は相手が接続閉じていると判断
			printf("Connection closed.\n");
			break;
		}

		// 応答が0の場合はデータ送信終了
		if (strlen(buffer) == 0) {
			printf("Finish receiving data.\n");
			break;
		}
		printf("%s\n", buffer);
		bzero(buffer, BUFFER_SIZE);
	}
	return (0);
}

int main(void)
{
	int		socket_fd;
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

	// サーバーに接続要求送信
	printf("Start connecting to server %s:%d\n", SERVER_ADDRESS, SERVER_PORT);
	if (connect(socket_fd, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_in)) == ERROR)
	{
		printf("Failed to connect with server.\n");
		// SHUT_RDWR: further receptions and transmissions will be disallowed.
		shutdown(socket_fd, SHUT_RDWR);
		return (ERROR);
	}
	printf("Connection established!\n");

	get_response(socket_fd);

	shutdown(socket_fd, SHUT_RDWR);
	return (0);
}
