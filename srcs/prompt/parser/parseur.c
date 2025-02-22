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

char	*ft_strdelchar(char *str, char del)
{
	int	i;
	int	len;
	char	*str_f;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != del)
			len++;
	}
	str_f = malloc(sizeof(char) * (len + 1));
	if (!str_f)
		return (NULL);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != del)
			str_f[len++] = str[i];
	}
	str_f[len] = 0;
	return (ft_del(str), str_f);
}

char *syntax_error(char *line)
{
	char	*temp;
	char	**err;
	int	i;
	int	j;
	int	is_str;

	temp = ft_strsjoin((const char *[]){"||.", "|.", "&&.", "&.", NULL});
	err = ft_split(temp, '.');
	i = -1;
	is_str = 0;
	while (err[++i])	
	{
		j = -1;
		while (line[++j])
		{
			if (line[j] == '"')
				is_str++;
			else if (is_str % 2 == 0 && ft_strlen(&line[j]) >= ft_strlen(err[i]) 
				&& !ft_strncmp(err[i], &line[j], ft_strlen(err[i])))
				return (ft_strsjoin((const char *[])
					{"mini: syntax error near unexpected token `", err[i], "'.", NULL}));
		}
	}	
	return (NULL);
}
	
void	pars_line(char *line, t_pars *exe)
{
	char	**arg;
	int		n_arg;
	int		i;

	arg = ft_split2(line, " ");
	if (!arg)
		return(ft_perror(1, NULL, 1));
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
	mess = syntax_error(line);
	if (mess)
		return (ft_perror(-1, mess, 0), 1);
	exe = ft_split2(line, "&");
	if (!exe)
		return(ft_perror(1, NULL, 1), 1);
	(*d)->cmd = init_struct_pars(exe, ft_strslen(exe));
	if (!(*d)->cmd)
		return (1);
	(*d)->cmd->line = line;
	while (++i < ft_strslen(exe))
		pars_line(exe[i], &(*d)->cmd[i]);
	// reader((*d)->cmd, ft_strslen(exe));
	return (0);
}
