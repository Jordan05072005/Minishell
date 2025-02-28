MAKEFLAGS += --no-print-directory

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g -I./includes
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

BUILTIN_SRC = \
    $(addprefix cd/, cd_env.c cd.c utils.c curpath.c) \
    $(addprefix pwd/, pwd.c) \
    $(addprefix env/, env.c) \
    $(addprefix unset/, unset.c) \
    $(addprefix exit/, exit.c) \
    $(addprefix echo/, echo.c) \
    $(addprefix export/, export.c export_var.c) \
    $(addprefix color/, color.c)

DATA_SRC = \
    clean_data.c create_var.c data.c env2env.c \
    ft_getenv_struct.c ft_getenv.c ft_getimp_struct.c ft_getimp.c \
    ft_getloc_struct.c ft_getloc.c init_imp.c is_env.c update_shlvl.c

EXEC_SRC = \
    $(addprefix exec/, exec_child.c exec_parent.c exec_builtin.c exec.c exec_define.c) \
    $(addprefix icmds/, clean_icmds.c define2child.c init_icmd.c init_icmds.c zero_icmds.c) \
    $(addprefix io/, close_fd.c here_doc.c set_io.c) \
    $(addprefix path/, get_path.c is_builtin.c)

PROMPT_SRC = \
    $(addprefix prompt/, color.c prompt.c main.c welcome.c) \
    $(addprefix parser/, parseur.c utils.c utils_lst.c fill.c split2.c get_var.c wildcard.c)

MINI_SRC = \
    $(addprefix srcs/builtin/, $(BUILTIN_SRC)) \
    $(addprefix srcs/data/, $(DATA_SRC)) \
    $(addprefix srcs/exec/, $(EXEC_SRC)) \
    $(addprefix srcs/prompt/, $(PROMPT_SRC))

OBJ = $(MINI_SRC:.c=.o)

.c.o:
	@printf "\r\033[K\033[34mCompiling: $<\033[0m"
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)
	@printf "\r\033[K"

all: $(NAME)

valgrind: $(LIBFT) all
	@valgrind --suppressions=supp.supp --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(NAME)

run: all
	@make clean
	@clear
	@./$(NAME) 4

$(LIBFT):
	@echo
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@echo "\n\033[2K\r\033[94mLinking $(NAME) 🗹\033[0m\n"
	@$(CC) $(OBJ) -o $(NAME) -L $(LIBFT_DIR) -lft -lreadline
	@len=$$(echo -n "$(NAME)" | wc -c); \
	border=$$(printf '=%.0s' $$(seq 1 $$((len + 36)))); \
	echo "\n\033[94m|$$border|\033[0m"; \
	echo "\033[94m|    🎉 $(NAME) Compilation Complete! 🎉    |\033[0m"; \
	echo "\033[94m|$$border|\033[0m\n"

clean:
	@echo -n "\033[34m"
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)
	@echo "Object files removed\033[0m"

fclean: clean
	@echo -n "\033[34m"
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@$(RM) $(NAME)
	@echo "Binary files and Libft removed\033[0m"

re: fclean all

.PHONY: all clean fclean re
