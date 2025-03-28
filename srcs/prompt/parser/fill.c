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
	char	*temp;

	if ((*n_arg) + 1 < max
	&& (ft_strncmp(arg[*n_arg], ">>", 3) == 0
		|| ft_strncmp(arg[*n_arg], ">", 1) == 0 || cmd->out))
	{
		if (!cmd->out)
			cmd->append = arg[(*n_arg)];
		(*n_arg) += (farg(&arg[*n_arg + 1]));
		ft_lstadd_back(&(cmd)->out, ft_lstnew(ft_strdelquotes(arg[(*n_arg)])));
		// ft_del(arg[(*n_arg)]);
	}
	else if (((ft_strlen(arg[*n_arg]) == 1 && ft_strncmp(arg[*n_arg], "<", 2) == 0)
		|| cmd->in) && max > *n_arg + 1 )
		{
			(*n_arg) += farg(&arg[*n_arg + 1]);
			ft_lstadd_back(&(cmd)->in, ft_lstnew(ft_strdelquotes(arg[(*n_arg)])));
			//ft_del(arg[(*n_arg)]);
		}
	else
	{
		if (!cmd->cmd)
			(cmd)->cmd = ft_strdup(arg[*n_arg]);
		else
			(cmd)->cmd = ft_strjoin_free((cmd)->cmd, arg[*n_arg]);
	}
}

int	fill_struct(t_pars *cmd, char **arg, int *n_arg)
{
	int	max;

	max = ft_strslen(arg);
	while (++(*n_arg) < max && !(ft_strlen(arg[*n_arg]) == 1
			&& ft_strchri(arg[*n_arg], "|") != (int)ft_strlen(arg[*n_arg]))) //ft_strncmp(arg[*n_arg], "|", 2))
	{
	if ((*n_arg) + 1 < max && ft_strlen(arg[*n_arg]) == 2
		&& ft_strncmp(arg[(*n_arg)], "<<", 3) == 0)
	{
		(*n_arg) += farg(&arg[*n_arg + 1]);
		(cmd)->limiter = arg[(*n_arg)];
	}
		else
			fill_struct2(cmd, arg, n_arg, max);
	}
	if (*n_arg == max)
		return (0);
	cmd->sep = arg[(*n_arg)][0];
	return (1);
}

char	**fill_args(char **str, int j)
{
	char	*var;

	j = -1;
	while (str && ++j < (int)ft_strslen(str))
	{
		var = NULL;
		if (ft_strchr(str[j], '*'))
		{
			str = wildcard(str, &j);
			continue;
		}
		// if (!str || !str[1])
		// 	printf("hello");
		if (ft_strchr(str[j], '$') || ft_strchr(str[j], '~'))
			var = get_var(str[j]);
		if (var && var[0]) // is vcvar$
		{
			ft_del2((void **)&str[j]);
			str[j] = var;
		}
		else if (var)
			shift_left(str, j);
		str[j] = ft_strdelquotes(str[j]);
	}
	return (str);
}

void	fill_exe(t_pars **pars, int i, int j)
{
	char	*temp;

	(*pars)->exe[i].in = (*pars)->in;
	(*pars)->exe[i].out = (*pars)->out;
	(*pars)->exe[i].subshell = 0;
	if ((*pars)->cmd && (*pars)->cmd[0] == '(')
		(*pars)->exe[i].subshell = 1;
	if ((*pars)->cmd && !(*pars)->exe[i].subshell)
		(*pars)->exe[i].args = ft_split2((*pars)->cmd, " ");
	else if ((*pars)->cmd)
	{
		(*pars)->exe[i].args = malloc(sizeof(char *));
		temp = ft_strtrim((*pars)->cmd, " ");
		(*pars)->exe[i].args[0] = ft_substr(temp, 1, ft_strlen(temp) - 2);
		ft_del(temp);
	}
	else
		(*pars)->exe[i].args = NULL;
	if (!(*pars)->exe[i].subshell)
		(*pars)->exe[i].args = fill_args((*pars)->exe[i].args, j);;
	(*pars)->exe[i].here_doc = ft_strdelquotes((*pars)->limiter);
	(*pars)->exe[i].append = ((*pars)->append) && !ft_strncmp((*pars)->append, ">>", 3); // a modif
}