NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I./include -I$(LIBFT_DIR)
LIBS = -lreadline -lncurses

SRC_DIR = src
OBJ_DIR = obj

SRCS =	$(SRC_DIR)/main.c \
	$(SRC_DIR)/lexer.c \
	$(SRC_DIR)/lexer_utils.c \
	$(SRC_DIR)/lexer_word.c \
	$(SRC_DIR)/lexer_ops.c \
	$(SRC_DIR)/lexer_token.c \
	$(SRC_DIR)/lexer_debug.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/parser_cmd.c \
	$(SRC_DIR)/parser_utils.c \
	$(SRC_DIR)/parser_utils_token.c \
	$(SRC_DIR)/ast_utils.c \
	$(SRC_DIR)/cmd_utils.c \
	$(SRC_DIR)/executor_nodes.c \
	$(SRC_DIR)/local_env.c \
	$(SRC_DIR)/cd_cmd.c \
	$(SRC_DIR)/echo_cmd.c \
	$(SRC_DIR)/export_cmd.c \
	$(SRC_DIR)/unset_cmd.c \
	$(SRC_DIR)/env_cmd.c \
	$(SRC_DIR)/pwd_cmd.c \
	$(SRC_DIR)/exit_cmd.c \
	$(SRC_DIR)/redir.c \
	$(SRC_DIR)/redir_utils.c \
	$(SRC_DIR)/executables.c \
	$(SRC_DIR)/local_env_utils.c \
	$(SRC_DIR)/lexer_word_utils.c \
	$(SRC_DIR)/executor_utils.c \
	$(SRC_DIR)/executor_io.c \
	$(SRC_DIR)/executor_process.c \
	$(SRC_DIR)/prompt.c \
	$(SRC_DIR)/signals.c \
	$(SRC_DIR)/signals_heredoc.c \
	$(SRC_DIR)/sort_env.c \
	$(SRC_DIR)/wildcard.c \
	$(SRC_DIR)/wildcard_utils.c \
	$(SRC_DIR)/redir_heredoc.c \
	$(SRC_DIR)/pre_heredoc.c \
	$(SRC_DIR)/wildcard_sort.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS = include/minishell.h

all:	$(NAME)


$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY:	all clean fclean re
