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

int	nbr_sep(char **str, char *sep)
{
	int	i;
	int	compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		if (strncmp(str[i], sep, ft_strlen(sep)) == 0)
			compt++;
		i++;
	}
	return (compt + 1);
}

int	is_var(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (i != 0 && i != (ft_strlen(str) - 1) && str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	fill_struct(t_pars *cmd, t_data **d, char **arg, int *n_arg)
{
	int	i;
	int	fd;
	int	max;
	char	**split;

	max = ft_strstrlen(arg);
	i = 0;
	while (*n_arg < max && !(ft_strlen(arg[*n_arg]) == 1 && in_str(arg[*n_arg][0], "|", -1)))
	{
		if (is_var(arg[*n_arg]) && ((*n_arg) + 1 >= max || in_str(arg[*n_arg][0], "|",(*n_arg) + 1 )))
		{
			split = ft_split(arg[*n_arg], '=');
			push_back_var(&(*d)->var, split[0], split[1], split);
		}
		else if ((*n_arg) + 1 < max && (!ft_strncmp(arg[*n_arg], ">>", ft_strlen(arg[*n_arg])) || !ft_strncmp(arg[*n_arg], ">", ft_strlen(arg[*n_arg]))))	
		{
			fd = open(arg[*n_arg + 1], O_WRONLY | O_CREAT, 0777);
			cmd->append = arg[(*n_arg)];
			(cmd)->out = arg[++(*n_arg)];
			close(fd);
			i++;
		}
		else if (ft_strlen(arg[*n_arg]) == 1 && ft_strncmp(arg[*n_arg], "<", 1) == 0 && max > *n_arg + 1)
		{
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
			(cmd)->cmd = ft_strjoin_free((cmd)->cmd, arg[*n_arg]);
			(cmd)->cmd = ft_strjoin_free((cmd)->cmd, " ");
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


void	reader(t_pars *cmd, int i, t_var *temp)
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
	printf("data : \n");
	while (temp != NULL)
	{
		printf("  key : %s, value : %s\n", temp->name, temp->data);
		temp = temp->next;
	}
}

void	fill_exe(t_pars **pars, int i)
{
	(*pars)->exe[i].in = (*pars)->in;
	(*pars)->exe[i].out = (*pars)->out;
	(*pars)->exe[i].args = ft_split2((*pars)->cmd, " ");
	(*pars)->exe[i].here_doc = (*pars)->limiter;
	(*pars)->exe[i].append = 0; // add append
}

void	free_tpars(t_pars **pars)  //vide ->free
{
	(*pars)->in = NULL;
	(*pars)->out = NULL;
	ft_del((*pars)->cmd);
	(*pars)->cmd = ft_strdup("");
	(*pars)->limiter = NULL;
	(*pars)->append = NULL;
	(*pars)->sep = 0;
}

void	pars_line(char *line, t_pars *exe, t_data **d)
{
	char	**arg;
	int	n_arg;
	int	i;

	arg = ft_split2(line, " ");
	init_struct_cmd(&exe, nbr_sep(arg, "|"), arg);
	n_arg = 0;
	i = 0;
	while (fill_struct(exe, d,  arg, &n_arg))
	{
		fill_exe(&exe, i);
		free_tpars(&exe);
		i++;
	}
	fill_exe(&exe, i);
}

int	parseur(char *line, t_data **d)
{
	char	**exe;
	int	i;

	i = -1;
	if (!line || line[0] =='\0')
		return (1);
	exe = ft_split2(line, "&");
	(*d)->cmd = init_struct_pars(exe, ft_strstrlen(exe));
	if (!(*d)->cmd)
		return (1);
	(*d)->cmd->line = line;
	while (++i < ft_strstrlen(exe))
	{
		pars_line(exe[i], &(*d)->cmd[i], d);
	}
	reader((*d)->cmd, ft_strstrlen(exe), (*d)->var);
	return (0);
}