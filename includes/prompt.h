/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:05 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 13:00:05 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define S_ERR "mini: syntax error near unexpected token `"

char		**cut_line(char *line);

char		*get_color(int option);
int			set_colors(char	*col1, char *col2, char *col3, char *col4);
void		print_welcome(void);

/* -------------------------------------------------------------------------- */
/*                  wildcard.c                                                */
/* -------------------------------------------------------------------------- */
char		**wildcard(char **str, int *j);
char		**insert_strs(char **str1, char *str2, int j, int overwrite);

/* -------------------------------------------------------------------------- */
/*                  get_wildcard.c                                            */
/* -------------------------------------------------------------------------- */
char		**get_file(DIR *dir, char *after, char *path);
char		*get_end(char *after);
char		*get_before(char *str);
char		*get_after(char *str);
char		*get_start(char *str);

/* -------------------------------------------------------------------------- */
/*                  utils_wildcard.c                                          */
/* -------------------------------------------------------------------------- */

int			accessv(char *start, char *file, char *str);
int			existing(char *path, char *str);

/* -------------------------------------------------------------------------- */
/*                  get_var.c                                                 */
/* -------------------------------------------------------------------------- */
char		*get_var(char *str);

/* -------------------------------------------------------------------------- */
/*                  fill.c                                                    */
/* -------------------------------------------------------------------------- */
int			farg(char **str);
void		fill_exe(t_pars **pars, int i, int j);
int			fill_struct(t_pars *cmd, char **arg, int *n_arg);

/* -------------------------------------------------------------------------- */
/*                  parser.c                                                  */
/* -------------------------------------------------------------------------- */
t_pars		*parseur(char *line);
t_list		*getLineParsing(char *line, char **err);
char		*syntax_error(char **arg, char *line, int i, int j);

/* -------------------------------------------------------------------------- */
/*                  prompt.c                                                  */
/* -------------------------------------------------------------------------- */
void		new_prompt(int signum);
char		*get_prompt(void);
void		any(int signum);

/* -------------------------------------------------------------------------- */
/*                  utils.c                                                   */
/* -------------------------------------------------------------------------- */
int			ft_strchri(char *str, char *c);
int			nbr_sep(char **str, char *sep);
char		*ft_strdelquotes(char *str);
void		free_tpars(t_pars **pars);
void		shift_left(char **str, size_t i);

/* -------------------------------------------------------------------------- */
/*                  utils2.c                                                  */
/* -------------------------------------------------------------------------- */
char		*nextc(char **str);
int			farg(char **str);
int			farg2(char *str);
char		*beforec(char **str, int i);
int			*quotes(char c, int *tab);

/* -------------------------------------------------------------------------- */
/*                  utils_lst.c                                               */
/* -------------------------------------------------------------------------- */
t_pars		*init_struct_pars(void);
void		init_struct_cmd(t_pars **pars, int nbr, char **arg);
char		**ft_split2(char *s, char *c);
t_wildcard	*initWildcard(char *path);
void		cleanW(t_wildcard **w);

char		*ft_readline(void);

t_bt		*create_bt_node(void *content);
t_bt		*ft_btnew(void *content);
void		set_parent(t_bt *parent, t_bt *child, int right);
t_bt		*get_ast(char *line);
void		clear_tree(t_bt *tree);
int			run_ast(t_bt *ast);
void		clear_blocks(t_list *cmds);
void		del_unusedlst(t_list *lst);
int			run_ast(t_bt *ast);

#endif