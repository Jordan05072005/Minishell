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


typedef struct s_cmd
{
	char	*in;
	char	*out;
	char	*cmd;
	int		here_doc;
	char	*limiter;
	char	*append;
	char	sep;
	char	**split;
}		t_cmd;

//parseur.c
t_cmd	*parseur(char *line);

//prompt.c
void new_prompt(int signum);
char	*get_prompt();

//utils.c
int	in_str(char c, char *sep, int y);
int	ft_strstrlen(char **str);

//utils_lst.c
t_cmd *init_struct(char **split, int nbr);

#endif