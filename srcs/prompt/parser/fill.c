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
			&& in_str(arg[*n_arg][0], "|", -1)))
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




char	ft_strchri(char *str, char *c)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (c[++j])
		{
			if (str[i] == c[j])
				return (i);
		}
	}
	return (i);
}

char	*get_var(char *str)
{
	int		i;
	char	*var;
	char	*temp;

	i = -1;
	var = ft_strdup("");
	while (++i < (int)ft_strlen(str))
	{
		temp = ft_substr(&str[i], 0, ft_strchri(&str[i], "$"));
		i += ft_strlen(temp);
		var = ft_strjoin_free(var, temp);
		ft_del(temp);
		if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
			i++;
		else if (str[i] == '$' && str[i + 1] && ft_isalnum(str[i + 1]))
		{
			temp = ft_substr(str, i, ft_strchri(&str[i], "[]%"));
			i += (ft_strlen(temp) - 1);
			if (ft_getenv(&temp[1]))
				var = ft_strjoin_free(var, ft_getenv(&temp[1]));
			else if (ft_getloc(&temp[1]))
				var = ft_strjoin_free(var, ft_getloc(&temp[1]));
			else if (ft_getimp(&temp[1]))
				var = ft_strjoin_free(var, ft_getimp(&temp[1]));
		}
		else if (str[i] == '$')
			var = ft_strjoin_free(var, (const char *)"$");
	}
	return (var);
}

void	fill_exe(t_pars **pars, int i, int j)
{
	char	*pt;
	char	*var;

	pt = NULL;
	var = NULL;
	(*pars)->exe[i].in = (*pars)->in;
	(*pars)->exe[i].out = (*pars)->out;
	(*pars)->exe[i].args = ft_split2((*pars)->cmd, " ");
	while ((*pars)->exe[i].args[++j])
	{
		(*pars)->exe[i].args[j] = ft_delcot((*pars)->exe[i].args[j], 1);
		if ((*pars)->exe[i].args[j][0] == '~' && !(*pars)->exe[i].args[j][1])
		{
			pt = (*pars)->exe[i].args[j];
			(*pars)->exe[i].args[j] = ft_strdup("$HOME");
		}
		if (ft_strchr((*pars)->exe[i].args[j], '$'))
			var = get_var((*pars)->exe[i].args[j]);
		if (var && var[0]) // is vcvar$
		{
			pt = (*pars)->exe[i].args[j];
			(*pars)->exe[i].args[j] = var;
		}
		else if (var)
			shift_left((*pars)->exe[i].args, j);
		ft_del(pt);
	}
	(*pars)->exe[i].here_doc = (*pars)->limiter;
	(*pars)->exe[i].append = 0;
	if (((*pars)->append) && !ft_strncmp((*pars)->append, ">>", 3))
		(*pars)->exe[i].append = 1;
}