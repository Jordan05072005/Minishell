/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:03:47 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/03 08:48:48 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../libft/libft.h"

typedef struct s_cmd
{
	char	*in;
	char	*out;
	char	**args;
	char	*here_doc;
	int		append;
	char	**split;
}	t_cmd;

typedef struct s_info_cmd
{
	int		fd_in;
	int		fd_out;
	char	*here_doc;
	char	*path;
	char	**args;
	int		pipe[2];
	int		pid;
	int		exit;
}	t_icmd;

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
	char	*line;
	t_cmd *exe;
}		t_pars;

typedef struct s_data
{
	t_pars	cmd;
	t_list	*env;
	t_list	*loc;
}	t_data;

int	ft_strstrlen(char **str);
int	clean_temp(t_pars *pars);

#endif