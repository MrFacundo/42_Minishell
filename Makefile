NAME	= minishell
SOURCES	= $(wildcard srcs/*.c)
OBJECTS	= $(patsubst srcs/%.c,objects/%.o,$(SOURCES))
LIBFT_DIR  = ./libft
CC		 = gcc
CFLAGS	 = -g -Wall -Wextra -Werror
LDFLAGS	= -L$(LIBFT_DIR) -lft

# --- COLORS ---

NONE=\033[0m
GRAY=\033[2;37m
RED=\033[31m
GREEN=\033[32m

# --- RULES ---

all: $(NAME)

$(NAME): $(OBJECTS) | libft
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

fclean: clean
	@echo "$(RED)Deleting everything! ( ͡° ͜ʖ ͡°) $(NONE)"
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

valgrind: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./minishell

re: fclean all

.PHONY: all libft clean fclean re valgrind
