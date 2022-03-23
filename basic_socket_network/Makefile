NAME = socket
CLIENT = client
SERVER = server

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

CLIENT_SRC = ./client_dir/client.c
SERVER_SRC = ./server_dir/server.c

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT)
	@$(CC) $(CFLAGS) $(SERVER_SRC) -o $(SERVER)

client:
	@./$(CLIENT)

server:
	@./$(SERVER)

fclean:
	@$(RM) $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all fclean re client server
