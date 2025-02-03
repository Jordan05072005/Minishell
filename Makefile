MAKEFLAGS += --no-print-directory

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g -I./includes#Has -g flag, watch out !
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MINISHELL_F =	prompt.c main.c parseur.c utils.c utils_lst.c split2.c

EXEC =	exec_child.c	exec_parent.c	exec_builtin.c	\
		exec.c

ICMDS =	init_icmd.c		init_icmds.c	zero_icmds.c	\
		clean_icmds.c

IO =	close_fd.c		here_doc.c		set_io.c

PTH =	get_path.c		is_builtin.c

MINI_B =	$(addprefix exec/, $(EXEC))		\
			$(addprefix icmds/, $(ICMDS))	\
			$(addprefix io/, $(IO))			\
			$(addprefix path/, $(PTH))

MINI_SRC =	$(addprefix srcs/frontend/, $(MINISHELL_F))	\
$(addprefix srcs/exec/, $(MINI_B)) srcs/env/clean.c

OBJ = $(MINI_SRC:.c=.o)

.c.o: 
	@$(CC) $(FLAGS) -Imlx -c $< -o $(<:.c=.o)

all: $(NAME)

run: re all
	@./$(NAME)

valgrind: re all
	@valgrind --suppressions=supp.supp --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(NAME)

bonus: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(FRAMEWORK) -o $(NAME) -L $(LIBFT_DIR) -lft -lreadline
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