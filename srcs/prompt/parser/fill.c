/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:33:16 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/14 19:33:16 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	fill_struct2(t_pars *cmd, char **arg, int *n_arg, int max)
{
	if (ft_strlen(arg[*n_arg]) == 1 && ft_strncmp(arg[*n_arg], "<", 1) == 0
		&& max > *n_arg + 1)
		(cmd)->in = arg[++(*n_arg)];
	else if ((*n_arg) + 1 < max && ft_strlen(arg[*n_arg]) == 2
		&& ft_strncmp(arg[(*n_arg)], "<<", 2) == 0)
		(cmd)->limiter = arg[++(*n_arg)];
	else
	{
		if (!cmd->cmd)
			(cmd)->cmd = ft_strjoin(arg[*n_arg], " ");
		else
		{
			(cmd)->cmd = ft_strjoin_free((cmd)->cmd, arg[*n_arg]);
			(cmd)->cmd = ft_strjoin_free((cmd)->cmd, " ");
		}
	}
}

int	fill_struct(t_pars *cmd, char **arg, int *n_arg)
{
	int	fd;
	int	max;

	max = ft_strslen(arg);
	while (++(*n_arg) < max && !(ft_strlen(arg[*n_arg]) == 1
			&& ft_strchri(arg[*n_arg], "|") != (int)ft_strlen(arg[*n_arg])))
	{
		if ((*n_arg) + 1 < max
			&& (!ft_strncmp(arg[*n_arg], ">>", ft_strlen(arg[*n_arg]))
				|| !ft_strncmp(arg[*n_arg], ">", ft_strlen(arg[*n_arg]))))
		{
			fd = open(arg[*n_arg + 1], O_WRONLY | O_CREAT, 0777);
			cmd->append = arg[(*n_arg)];
			(cmd)->out = arg[++(*n_arg)];
			close(fd);
		}
		else
			fill_struct2(cmd, arg, n_arg, max);
	}
	if (*n_arg == max)
		return (0);
	cmd->sep = arg[(*n_arg)][0];
	return (1);
}

void	fill_exe(t_pars **pars, int i, int j)
{
	char	*var;

	(*pars)->exe[i].in = (*pars)->in;
	(*pars)->exe[i].out = (*pars)->out;
	if ((*pars)->cmd)
		(*pars)->exe[i].args = ft_split2((*pars)->cmd, " ");
	else
		(*pars)->exe[i].args = NULL;
	while ((*pars)->exe[i].args && (*pars)->exe[i].args[++j])
	{
		var = NULL;
		if (ft_strchr((*pars)->exe[i].args[j], '*'))
			(*pars)->exe[i].args = wildcard((*pars)->exe[i].args, j);
		if (ft_strchr((*pars)->exe[i].args[j], '$') || ft_strchr((*pars)->exe[i].args[j], '~'))
			var = get_var((*pars)->exe[i].args[j]);
		if (var && var[0]) // is vcvar$
		{
			ft_del((*pars)->exe[i].args[j]);
			(*pars)->exe[i].args[j] = var;
		}
		else if (var)
			shift_left((*pars)->exe[i].args, j);
	}
	(*pars)->exe[i].here_doc = (*pars)->limiter;
	(*pars)->exe[i].append = ((*pars)->append) && !ft_strncmp((*pars)->append, ">>", 3);
}