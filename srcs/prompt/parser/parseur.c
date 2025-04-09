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
			// if (cmd[j].exe[y].in)
			// 	printf("    in : %s\n",cmd[j].exe[y].in);
			// if (cmd[j].exe[y].out)
			// 	printf("    out : %s \n",cmd[j].exe[y].out);
			// if (cmd[j].exe[y].here_doc)
			// 	printf("    limiter : %s\n",cmd[j].exe[y].here_doc);
			if (cmd[j].exe[y].append)
				printf("    append : %d\n",cmd[j].exe[y].append);
			if (cmd[j].exe[y].subshell)
				printf("    subshell : %d\n",cmd[j].exe[y].subshell);
			y++;
		}
		y = 0;
		j++;
	}
}

void	read2(t_list *l)
{
	while (l != NULL)
	{
		printf("arg : %s\n", (char *)l->content);
		l = l->next;
	}
}

void pars_line(char *line, t_pars *exe)
{
	char	**arg;
	int		n_arg;
	int		i;
	n_arg = -1;
	i = 0;
	arg = cut_line(line);
	int	j = -1;
	while (arg && arg[++j])
		printf("zrg : %s\n", arg[j]);
	if (!arg)
		return ;
	init_struct_cmd(&exe, nbr_sep(arg, "|"), arg);
	while (fill_struct(exe, arg, &n_arg))
	{
		fill_exe(&exe, i++, -1);
		free_tpars(&exe);
	}
	fill_exe(&exe, i, -1);
	return ;
}

int	get_cut(char *str)
{
	int	i;
	int	para;
	int *quote;

	quote = 0;
	i = -1;
	para = 0;
	while (str[++i])
	{
		quote = quotes(str[i], quote);
		if (!ft_strncmp(&str[i], "(", 1) && quote[2])
			para++;
		else if (para && !ft_strncmp(&str[i], ")", 1) && quote[2])
			para--;
		else if ((!ft_strncmp(&str[i], "||", 2) || !ft_strncmp(&str[i], "&&", 2))
				&& i != 0 && para == 0 && quote[2])
			return (ft_del(quote), i);
	}
	return (ft_del(quote), i);
}

t_list *getLineParsing(char *line, char **err)
{
	size_t	i;
	t_list *cutLine;
	char	*lineTemp;

	i = -1;
	if (!line || line[0] == '\0' || (ft_strlen(line) == 1 
	&& (line[0] == '!' || line[0] == ':')))
		return (NULL);
	*err = syntax_error(cut_line(line), line, -1, -1);
	if (*err)
		set_exit_val(2);
	cutLine = NULL;
	while (++i < ft_strlen(line) && !(*err))
	{
		lineTemp = ft_substr(&line[i], 0, get_cut(&line[i]));
		ft_lstadd_back(&cutLine, ft_lstnew(lineTemp));
		i += get_cut(&line[i]);
		if (line[i] == '|' || line[i] == '&')
		{
			ft_lstadd_back(&cutLine, ft_lstnew((void *)ft_substr(&line[i], 0, 2)));
			i += 2;
		}
	}
	// read2(cutLine);
	if (*err)
		return (ft_lstclear(&cutLine, free), NULL);
	return (cutLine);
}

t_pars	*parseur(char *line)
{
	t_pars	*pars;

	pars = init_struct_pars();
	pars->line = line;
 	pars_line(pars->line, pars);
	// reader(pars, 1);

	return (pars);
}
