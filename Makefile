NAME	= minishell
SRC_DIR = srcs
OBJ_DIR = objects
SOURCES		=	srcs/builtins/export.c \
				srcs/builtins/builtins_utils.c \
				srcs/builtins/cd.c \
				srcs/builtins/builtins.c \
				srcs/builtins/pwd.c \
				srcs/builtins/exit.c \
				srcs/builtins/unset.c \
				srcs/builtins/echo.c \
				srcs/environment/env_utils_2.c \
				srcs/environment/env_utils_1.c \
				srcs/environment/env.c \
				srcs/executor/execution.c \
				srcs/executor/exec_path_finding.c \
				srcs/executor/exec_utils.c \
				srcs/executor/exec_error_handling.c \
				srcs/parser/parsing_utils.c \
				srcs/parser/parsing.c \
				srcs/tokenizer/token_utils_2.c \
				srcs/tokenizer/tokenizer.c \
				srcs/tokenizer/token_utils_3.c \
				srcs/tokenizer/token_utils.c \
				srcs/utils/utils.c \
				srcs/utils/utils_2.c \
				srcs/utils/free.c \
				srcs/constructors.c \
				srcs/debug.c \
				srcs/main.c \
				srcs/read.c \
				srcs/signals.c \

LIBFT_DIR  = ./libft
CC		 = gcc
CFLAGS	 = -g -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline
OBJECTS	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# --- COLORS ---

NONE=\033[0m
GRAY=\033[2;37m
RED=\033[31m
GREEN=\033[32m

# --- RULES ---

all: $(NAME)

$(NAME): 	$(OBJECTS) | libft
			@echo "$(GRAY)----Compiling $(NAME)----$(NONE)"
			$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)
			@echo "$(GREEN)$(NAME) Compiled! ᕦ(♥_♥)ᕤ$(NONE)\n"

objects/%.o: srcs/%.c | objects
			$(CC) $(CFLAGS) -c $< -o $@

libft:
			make -C $(LIBFT_DIR)

clean:
			@echo "$(GREEN)Deleting objects! ( ͡° ͜ʖ ͡°) $(NONE)"
			rm -f $(OBJECTS)
			make -C $(LIBFT_DIR) clean

fclean: 	clean
			@echo "$(RED)Deleting everything! ( ͡° ͜ʖ ͡°) $(NONE)"
			rm -f $(NAME)
			make -C $(LIBFT_DIR) fclean

restart:	all 
			./minishell

valgrind: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./minishell

re: fclean all

.PHONY: all libft clean fclean re valgrind
