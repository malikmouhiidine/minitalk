NAME = minitalk
SRC = server.c client.c
BONUS_SRC = server_bonus.c client_bonus.c
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o server server.o
	$(CC) -o client client.o

bonus: $(BONUS_OBJ)
	$(CC) -o server_bonus server_bonus.o
	$(CC) -o client_bonus client_bonus.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f server client server_bonus client_bonus

re: fclean all

.PHONY: all bonus clean fclean re