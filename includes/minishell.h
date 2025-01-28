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
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_cmd
{
	char	*in;
	char	*out;
	char	*cmd;
	int		here_doc;
	char	*limiter;
	int		append;
	char	sep;
	char	**split;
	struct s_cmd	*next;
}		t_cmd;

int	parseur(char *line);
void new_prompt(int signum);
char	*get_prompt();
int	ft_strstrlen(char **str);

#endif