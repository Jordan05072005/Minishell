/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:05:39 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/27 16:05:39 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#	include <unistd.h>
# include <stdio.h>
#	include <signal.h>
#include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

#include "exec.h"

typedef struct s_pars
{
	int		n_sep;
	int		pipe;
	char	*in;
	char	*out;
	char	*cmd;
	char	*limiter;
	char	*append;
	char	sep;
	char	**split;
	t_cmd *exe;
}		t_pars;

//parseur.c
t_pars	*parseur(char *line);

//prompt.c
void new_prompt(int signum);
char	*get_prompt();
void	ft_exit();

//utils.c
int	in_str(char c, char *sep, int y);
int	ft_strstrlen(char **str);

//utils_lst.c
t_pars *init_struct_pars(char **split, int nbr);
void	init_struct_cmd(t_pars **pars, int nbr, char **arg);


#endif