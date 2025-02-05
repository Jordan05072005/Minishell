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

//parseur.c
int	parseur(char *line, t_data **d);

//prompt.c
void new_prompt(int signum);
char	*get_prompt();

//utils.c
int	in_str(char c, char *sep, int y);

//utils_lst.c
t_pars *init_struct_pars(char **split, int nbr);
void	init_struct_cmd(t_pars **pars, int nbr, char **arg);
// void	push_back_var(t_var **v, char *name, char *data, char **split);
char	**ft_split2(char *s, char *c);


#endif