/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:05:13 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/27 16:05:13 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_sep(char **str)
{
	int	i;
	int	compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		if (strncmp(str[i], "|", 1) == 0)
			compt++;
		i++;
	}
	return (compt + 1);
}

int	fill_struct(t_cmd *cmd, char **arg, int *n_arg, int max)
{
	int	i;
	int	fd;

	i = 0;
	while (*n_arg < max && !(ft_strlen(arg[*n_arg]) == 1 && in_str(arg[*n_arg][0], "|", -1)))
	{
		if ((*n_arg) + 1 < max && (!ft_strncmp(arg[*n_arg], ">>", ft_strlen(arg[*n_arg])) || !ft_strncmp(arg[*n_arg], ">", ft_strlen(arg[*n_arg]))))	
		{
			fd = open(arg[*n_arg + 1], O_WRONLY | O_CREAT, 0777);
			cmd->append = arg[(*n_arg)];
			(cmd)->out = arg[++(*n_arg)];
			close(fd);
			i++;
		}
		else if (ft_strlen(arg[*n_arg]) == 1 && ft_strncmp(arg[*n_arg], "<", 1) == 0 && max > *n_arg + 1)
		{
			cmd->append = arg[(*n_arg)];
			(cmd)->in = arg[++(*n_arg)];
			i++;
		}
		else if ((*n_arg) + 1 < max && ft_strlen(arg[*n_arg]) == 2 && ft_strncmp(arg[(*n_arg)], "<<", 2) == 0)
		{
			(cmd)->limiter = arg[++(*n_arg)];
			i++;
		}
		else
		{
			(cmd)->cmd = ft_strjoin2((cmd)->cmd, arg[*n_arg]);
			(cmd)->cmd = ft_strjoin2((cmd)->cmd, " ");
		}
		i++;
		(*n_arg)++;
		}
		if (*n_arg == max)
			return (0);
		cmd->sep = arg[*n_arg][0];
		(*n_arg)++;
		return (1);
}


void	reader(t_cmd *cmd, int i)
{
	int	j=0;

	while (j < i)
	{
		printf("%d :\n", j);
		if (cmd[j].cmd)
			printf(" cmd : %s\n",cmd[j].cmd);
		if (cmd[j].in)
			printf(" in : %s\n",cmd[j].in);
		if (cmd[j].out)
			printf(" out : %s \n",cmd[j].out);
		if (cmd[j].limiter)
			printf(" limiter : %s\n",cmd[j].limiter);
		if (cmd[j].sep != 0)
			printf(" sep : %c\n",cmd[j].sep);
		if (cmd[j].append)
			printf(" append : %s\n",cmd[j].append);
		j++;
	}
}

t_cmd	*parseur(char *line)
{
	char	**arg;
	t_cmd *cmd;
	int		n_arg;
	int	err;
	int	i;

	err = 1;
	arg = ft_split(line, ' ');
	cmd = init_struct(arg, nbr_sep(arg));
	n_arg = 0;
	i = 0;
	while (err == 1)
	{
		err = fill_struct(&(cmd[i]), arg, &n_arg, ft_strstrlen(arg));
		if (err == 1)
			i++;
	}
	reader(cmd, nbr_sep(arg));
	return (cmd);
}