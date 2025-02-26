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

char	*syntax_error2(char **arg, char *mess, int is_str)
{
	char	*temp;
	char	**err;
	int		i;

	temp = ft_strsjoin((const char *[]){">>.", ">.", "<<.", "<", NULL});
	err = ft_split(temp, '.');
	ft_del(temp);
	temp = NULL;
	i = -1;
	while (is_str % 2 == 0 && !mess && ++i < 4)
	{
		if (ft_strslen(arg) > 1)
			temp = ft_substr(arg[1], 0, 1 + (arg[1][0] == 62 || arg[1][0] == 60 || arg[1][0] == arg[1][1] || arg[1][1] == 62 || arg[1][1] == 60));
		if (!ft_strncmp(arg[0], err[i], ft_strlen(err[i])))
		{	
			if (ft_strslen(arg) == 1)
				mess = ft_strsjoin((const char *[]){S_ERR, "newline'.", NULL});
			else if (!ft_isalnum(arg[1][0]))
				mess = ft_strsjoin((const char *[]){S_ERR, temp, "'.", NULL});
		}
	}
	return (ft_del(temp), ft_free_tab((void *)err, ft_strslen(err)),
		ft_free_tab((void *)arg, ft_strslen(arg)), mess);
}

char	*syntax_error(char *line, int i, int j)
{
	char	*temp;
	char	**err;
	int		is_str;

	temp = ft_strsjoin((const char *[]){"||.", "|.", "&&.", "&.", NULL});
	err = ft_split(temp, '.');
	ft_del(temp);
	temp = NULL;
	is_str = 0;
	while (err[++i])
	{
		j = -1;
		while (!temp && line[++j])
		{
			if (line[j] == '"')
				is_str++;
			else if (is_str % 2 == 0 && ft_strlen(&line[j]) == ft_strlen(err[i])
				&& !ft_strncmp(err[i], &line[j], ft_strlen(err[i])))
				temp = ft_strsjoin((const char *[]){S_ERR, err[i], "'.", NULL});
			else if (i == 0)
				temp = syntax_error2(ft_split(line, 32), NULL, is_str);
		}
	}
	return (ft_free_tab((void *)err, i), temp);
}

void	pars_line(char *line, t_pars *exe)
{
	char	**arg;
	int		n_arg;
	int		i;

	arg = ft_split2(line, " ");
	if (!arg)
		return (ft_perror(1, NULL, 1));
	init_struct_cmd(&exe, nbr_sep(arg, "|"), arg);
	n_arg = -1;
	i = -1;
	while (arg[++i])
	{
		arg[i] = ft_strdelchar(arg[i], '"');
		arg[i] = ft_strdelchar(arg[i], '\'');
	}
	i = 0;
	while (fill_struct(exe, arg, &n_arg))
	{
		fill_exe(&exe, i++, -1);
		free_tpars(&exe);
	}
	fill_exe(&exe, i, -1);
}

int	parseur(char *line, t_data **d)
{
	char	**exe;
	size_t	i;
	char	*mess;

	i = -1;
	if (!line || line[0] == '\0')
		return (1);
	mess = syntax_error(line, -1, -1);
	if (mess)
		return (ft_perror(-1, mess, 0), 1);
	exe = ft_split2(line, "&");
	if (!exe)
		return (ft_perror(1, NULL, 1), 1);
	(*d)->cmd = init_struct_pars(exe, ft_strslen(exe));
	if (!(*d)->cmd)
		return (1);
	(*d)->cmd->line = line;
	while (++i < ft_strslen(exe))
		pars_line(exe[i], &(*d)->cmd[i]);
	// reader((*d)->cmd, ft_strslen(exe));
	return (0);
}
