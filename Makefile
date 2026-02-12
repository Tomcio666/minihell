NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)
LIBS = -lreadline -lncurses

SRCS =	main.c \
	lexer.c \
	lexer_utils.c \
	lexer_word.c \
	lexer_ops.c \
	lexer_token.c \
	lexer_debug.c \
	parser.c \
	parser_cmd.c \
	parser_utils.c \
	parser_utils_token.c \
	ast_utils.c \
	cmd_utils.c \
	executor_nodes.c \
	local_env.c \
	cd_cmd.c \
	echo_cmd.c \
	export_cmd.c \
	unset_cmd.c \
	env_cmd.c \
	pwd_cmd.c \
	exit_cmd.c \
	redir.c \
	redir_utils.c \
	executables.c \
	local_env_utils.c \
	lexer_word_utils.c \
	executor_utils.c \
	executor_io.c \
	executor_process.c \
	prompt.c \
	signals.c \
	sort_env.c \
	wildcard.c \
	wildcard_utils.c \
	wildcard_sort.c

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
