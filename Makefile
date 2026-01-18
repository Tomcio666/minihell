NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)
LIBS = -lreadline -lncurses

SRCS =	main.c \
	pwd.c \
	lexer.c \
	lexer_utils.c \
	lexer_word.c \
	lexer_ops.c \
	lexer_token.c \
	lexer_debug.c \
	parser.c \
	parser_cmd.c \
	parser_utils.c \
	ast_utils.c \
	cmd_utils.c \
	executor.c
# Add each source file (relative path) to the SRCS list above.

OBJS = $(SRCS:.c=.o)
HEADERS = minishell.h

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY:	all clean fclean re
