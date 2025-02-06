MAKEFLAGS += --no-print-directory

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g -I./includes#Has -g flag, watch out !
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

PROMPT =	prompt.c			main.c
PARS =		parseur.c			utils.c			utils_lst.c			\
			split2.c
MINI_P =	$(addprefix prompt/, $(PROMPT))		\
			$(addprefix parser/, $(PARS))

EXEC =		exec_child.c		exec_parent.c	exec_builtin.c		\
			exec.c
ICMDS =		init_icmd.c			init_icmds.c	zero_icmds.c		\
			clean_icmds.c
IO =		close_fd.c			here_doc.c		set_io.c
PTH =		get_path.c			is_builtin.c
MINI_E =	$(addprefix exec/, $(EXEC))		\
			$(addprefix icmds/, $(ICMDS))	\
			$(addprefix io/, $(IO))			\
			$(addprefix path/, $(PTH))

MINI_D =	clean_data.c		data.c			env2env.c			\
			ft_getenv_struct.c	ft_getenv.c		ft_getloc_struct.c	\
			ft_getloc.c

CD =		cd.c				utils.c
PWD =		pwd.c
ENV =		env.c
EXIT =		exit.c
UN =		unset.c
ECHO = echo.c

MINI_B =	$(addprefix cd/, $(CD))		\
			$(addprefix pwd/, $(PWD))	\
			$(addprefix env/, $(ENV))	\
			$(addprefix unset/, $(UN))	\
			$(addprefix exit/, $(EXIT)) \
			$(addprefix echo/, $(ECHO))

MINI_SRC =	$(addprefix srcs/prompt/, $(MINI_P))	\
			$(addprefix srcs/exec/, $(MINI_E))		\
			$(addprefix srcs/data/, $(MINI_D))		\
			$(addprefix srcs/builtin/, $(MINI_B))

OBJ = $(MINI_SRC:.c=.o)

.c.o: 
	@$(CC) $(FLAGS) -Imlx -c $< -o $(<:.c=.o)

all: $(NAME)

run: re
	@./$(NAME)

valgrind: re all
	@valgrind --suppressions=supp.supp --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(NAME)

no-child: re all
	@valgrind --suppressions=supp.supp --leak-check=full --show-leak-kinds=all ./$(NAME)
# --suppressions=supp.supp

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