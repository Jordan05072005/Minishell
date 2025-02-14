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

#include "mini.h"

void	reader(t_pars *cmd, int i)
{
	int	j=0;
	int	y=0;

	while (j < i)
	{
		printf("exe : %d :\n", j);
		while (y < cmd[j].pipe)
		{ 
			printf("  pipe %d :\n", y);
			if (cmd[j].exe[y].args)
				printf("    cmd : %s\n",cmd[j].exe[y].args[0]);
			if (cmd[j].exe[y].in)
				printf("    in : %s\n",cmd[j].exe[y].in);
			if (cmd[j].exe[y].out)
				printf("    out : %s \n",cmd[j].exe[y].out);
			if (cmd[j].exe[y].here_doc)
				printf("    limiter : %s\n",cmd[j].exe[y].here_doc);
			if (cmd[j].exe[y].append)
				printf("    append : %d\n",cmd[j].exe[y].append);
			y++;
		}
		y = 0;
		j++;
	}
}

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

void	fill_exe(t_pars **pars, int i, int j)
{
	char	*pt;

	(*pars)->exe[i].in = (*pars)->in;
	(*pars)->exe[i].out = (*pars)->out;
	(*pars)->exe[i].args = ft_split2((*pars)->cmd, " ");
	while ((*pars)->exe[i].args[++j])
	{
		(*pars)->exe[i].args[j] = ft_delcot((*pars)->exe[i].args[j], 1);
		if ((*pars)->exe[i].args[j][0] == '$')
		{
			pt = (*pars)->exe[i].args[j];
			if (ft_getloc(&(*pars)->exe[i].args[j][1]))
				(*pars)->exe[i].args[j] = ft_strdup(ft_getloc(&(*pars)->exe[i].args[j][1]));
			else if (ft_getenv(&(*pars)->exe[i].args[j][1]))
				(*pars)->exe[i].args[j] = ft_strdup(ft_getenv(&(*pars)->exe[i].args[j][1]));
			else
				shift_left((*pars)->exe[i].args, j);
			ft_del(pt);
		}
	}
	(*pars)->exe[i].here_doc = (*pars)->limiter;
	(*pars)->exe[i].append = 0;
	if (((*pars)->append) && !ft_strncmp((*pars)->append, ">>", 3))
		(*pars)->exe[i].append = 1;
}

void	pars_line(char *line, t_pars *exe)
{
	char	**arg;
	int		n_arg;
	int		i;

	arg = ft_split2(line, " ");
	init_struct_cmd(&exe, nbr_sep(arg, "|"), arg);
	n_arg = -1;
	i = 0;
	while (fill_struct(exe, arg, &n_arg))
	{
		fill_exe(&exe, i, -1);
		free_tpars(&exe);
		i++;
	}
	fill_exe(&exe, i, -1);
}

int	parseur(char *line, t_data **d)
{
	char	**exe;
	size_t	i;

	i = -1;
	if (!line || line[0] == '\0')
		return (1);
	exe = ft_split2(line, "&");
	(*d)->cmd = init_struct_pars(exe, ft_strslen(exe));
	if (!(*d)->cmd)
		return (1);
	(*d)->cmd->line = line;
	while (++i < ft_strslen(exe))
		pars_line(exe[i], &(*d)->cmd[i]);
	// reader((*d)->cmd, ft_strslen(exe));
	return (0);
}
