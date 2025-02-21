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
	j = -1;
	while (str[++i])
	{
		while (c[++j])
		{
			if (str[i] == c[j])
				return (i);
		}
	}
	return (i);
}

void	t(char *str, t_icmd *cmd, int etat, int i)
{
	size_t	j;
	int		oct;
	char	*var;

	j = -1;
	oct = 0;
	if (!etat)
		return ;
	var = ft_substr(str, ft_strchri(str, "$"), ft_strchri(str, "[]"));
	printf("la :%s \n", var);
	while (++j < ft_strlen(str))
	{
		if (str[j] == '$' && (ft_getenv(var) ||ft_getloc(var)))
		{
			if (ft_getenv(var))
				oct += ft_putstr_fd(ft_getenv(var), 1);
			if (ft_getloc(var))
				oct += ft_putstr_fd(ft_getloc(var), 1);
			j += ft_strlen(var);
		}
		else
			oct += write(1, &str[j], 1);
	}
	if (cmd->args[i + 1] && oct != 0)
		write(1, " ", 1);
	return (ft_del(var));
}

char	*get_var(char *str)
{
	int		i;
	char	*var;
	char	*temp;

	i = 0;
	var = ft_strdup("");
	printf("str : %s\n", str)
	while (str[i])
	{
		temp = ft_substr(str, 0, ft_strchri(&str[i], "$"));
		printf("i : %d\n", i);
		i += ft_strlen(temp);
		printf("i : %d\n", i);
		printf("i : %d && c : %c && %d \n",i, str[i], ft_isalnum(str[i + 1]));
		var = ft_strjoin_free(var, temp);
		ft_del(temp);
		if (str[i] == '$' && str[i + 1] && ft_isalnum(str[i + 1]))
		{
			temp = ft_substr(str, i, ft_strchri(&str[i], "[]"));
			i += ft_strlen(temp);
			printf("i : %d\n", i);
			if (ft_getenv(temp))
				ft_strjoin_free(var, ft_getenv(temp));
			else if (ft_getloc(temp))
				ft_strjoin_free(var, ft_getloc(temp));
			else if (ft_getimp(temp))
				ft_strjoin_free(var, ft_getimp(temp));
		}
	}
	printf("la : %s\n", var);
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
		if (var) // is vcvar$
		{
			pt = (*pars)->exe[i].args[j];
			if (ft_getloc(&(*pars)->exe[i].args[j][1]))
				(*pars)->exe[i].args[j] = ft_strdup(ft_getloc(&(*pars)->exe[i].args[j][1]));
			else if (ft_getenv(&(*pars)->exe[i].args[j][1]))
				(*pars)->exe[i].args[j] = ft_strdup(ft_getenv(&(*pars)->exe[i].args[j][1]));
			else
				shift_left((*pars)->exe[i].args, j);
		}
		ft_del(pt);
	}
	(*pars)->exe[i].here_doc = (*pars)->limiter;
	(*pars)->exe[i].append = 0;
	if (((*pars)->append) && !ft_strncmp((*pars)->append, ">>", 3))
		(*pars)->exe[i].append = 1;
}