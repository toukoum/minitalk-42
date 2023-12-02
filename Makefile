CLIENT = client
SERVER = server

CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

SRC_CLIENT = srcs/client.c
SRC_SERVER = srcs/server.c

SRC_CLIENT_BONUS = srcs/client_bonus.c
SRC_SERVER_BONUS = srcs/server_bonus.c

LIBFT = libft/
LIBFT_LIB = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(CLIENT) $(SERVER)

$(CLIENT): $(SRC_CLIENT) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SRC_CLIENT) $(LIBFT_LIB) -o $(CLIENT)

$(SERVER): $(SRC_SERVER) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SRC_SERVER) $(LIBFT_LIB) -o $(SERVER)

$(LIBFT_LIB):
	make -C $(LIBFT)

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): $(SRC_CLIENT_BONUS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SRC_CLIENT_BONUS) $(LIBFT_LIB) -o $(CLIENT_BONUS)

$(SERVER_BONUS): $(SRC_SERVER_BONUS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SRC_SERVER_BONUS) $(LIBFT_LIB) -o $(SERVER_BONUS)

clean:
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)
	rm -f $(LIBFT_LIB)

re: fclean all

.PHONY: all clean fclean re
