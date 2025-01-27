MAKEFLAGS += --no-print-directory

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g #Has -g flag, watch out !
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MINISHELL = 

MINI_SRC = $(addprefix srcs/, $(MINISHELL))

OBJ = $(MINI_SRC:.c=.o)

.c.o: 
	@$(CC) $(FLAGS) -Imlx -c $< -o $(<:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(FRAMEWORK) -o $(NAME) -L $(LIBFT_DIR) -lft
	@echo "$(NAME) compiled successfully!"

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@echo "Object files removed"

fclean: clean
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@$(RM) $(NAME) checker
	@echo "Binary files and Libft removed"

re: fclean all

norminette:
	@make -C $(LIBFT_DIR) norminette
	@-norminette srcs | grep -E --color=always "Error" || echo "Norminette: Everything is fine!"

.PHONY: all clean fclean re bonus norminette