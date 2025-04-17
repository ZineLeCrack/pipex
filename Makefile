NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/utils.c srcs/find_path.c srcs/main.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = srcs/libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

libft:
	@make fclean -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)
	@make clean -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all