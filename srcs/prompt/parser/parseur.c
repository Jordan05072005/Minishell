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

char	*syntax_error2(char **arg, char *mess)
{
	char	*temp;
	char	**err;
	int		i;

	temp = ft_strsjoin((const char *[]){">>.", ">.", "<<.", "<", NULL});
	err = ft_split(temp, '.');
	i = -1;
	while (!mess && ++i < 4)
	{
		ft_del2((void **)&temp);
		if (!ft_strncmp(arg[0], err[i], ft_strlen(err[i])))
		{	
			if ((ft_strslen(arg) - (arg[1] && ft_isspace(arg[1][0]) == 1)) == 1 
				&& ft_strlen(arg[0]) <= 2)
				mess = ft_strsjoin((const char *[]){S_ERR, "newline'.", NULL});
			else if ((ft_strslen(arg) - (arg[1] && ft_isspace(arg[1][0]) == 1)) == 1
				&& ft_strlen(arg[0]) > 2 && !ft_isalnum(arg[0][2]))
				temp = ft_substr(arg[0], 2, 2);
			else if (ft_strslen(arg) > 1 && !ft_isalnum(arg[farg(&arg[1])][0]))
				temp = ft_substr(arg[farg(&arg[1])], 0 , 2);
			if (temp)
				mess = ft_strsjoin((const char *[]){S_ERR, temp, "'.", NULL});
		}
	}
	return (ft_del(temp), ft_free_tab((void *)err, ft_strslen(err)), mess);
}
// ft_isalnum(arg[farg(arg) - 1][0]
char	*syntax_error(char **arg, int i, int j)
{
	char	*temp;
	char	**err;

	temp = ft_strsjoin((const char *[]){"||.", "|.", "&&.", "&.", NULL});
	err = ft_split(temp, '.');
	ft_del(temp);
	temp = NULL;
	while (!temp && arg[++j])
	{
		i = -1;
		while (!temp && err[++i] && arg[j])
		{
			if (((ft_strlen(arg[j]) > 2|| ((!nextc(&arg[j + 1])
				|| !ft_isalnum(nextc(&arg[j + 1])[0]))
				&& ft_strlen(arg[j]) == ft_strlen(err[i])))
				&& ft_strnstr(arg[j], err[i], ft_strlen(arg[j]))) || (j  == 0
				&& ft_strnstr(arg[j], err[i], ft_strlen(arg[j]))))
				temp = ft_strsjoin((const char *[]){S_ERR, err[i], "'.", NULL});
			else
				temp = syntax_error2(&arg[j], NULL);
		}
	}	
	return (ft_free_tab((void *)err, ft_strslen(err)), temp);
}

int	pars_line(char *line, t_pars *exe)
{
	char	**arg;
	int		n_arg;
	int		i;
	char	*mess;

	n_arg = -1;
	i = -1;
	i = 0;
	arg = cut_line(line);
	int	j = -1;
	while (arg && arg[++j])
		printf("zrg : %s\n", arg[j]);
	if (!arg)
		return (1);
	mess = syntax_error(arg, -1, -1);
	if (mess)
		return (set_exit_val(2), ft_perror(-1, mess, 0), 1);
	init_struct_cmd(&exe, nbr_sep(arg, "|"), arg);
	while (fill_struct(exe, arg, &n_arg))
	{
		fill_exe(&exe, i++, -1);
		free_tpars(&exe);
	}
	fill_exe(&exe, i, -1);
	return (0);
}

// typedef struct s_list
// {
// 	void			*content;
// 	char		*sep;
// 	struct s_list	*next;
// }	t_list;

int	get_cut(char *str)
{
	int	i;

	i = -1;

	while (str[++i])
	{
		if ((!ft_strncmp(&str[i], "||", 2) || !ft_strncmp(&str[i], "&&", 2)) && i != 0)
			return (i);
	}
	return (i);
}

int	parseur(char *line, t_data **d)
{
	char	*temp_line;
	size_t	i;
	int		len;
	int	err;
	t_pars *temp;
	t_list *l;
	
	printf("hello world");
	
	err = 0;
	i = -1;
	if (!line || line[0] == '\0' || (ft_strlen(line) == 1 
		&& (line[0] == '!' || line[0] == ':')))
		return (1);
	l = NULL;
	// exe = ft_split2(line, "&");
	// if (!exe)	
	// 	return (ft_perror(1, NULL, 1), 1);
	temp = init_struct_pars(1);
	// if (!(*d)->cmd)
	// 	return (1);
	(void)(*d);
	temp->line = line;
	// pars_line(line, &(*d)->cmd[i]);
	while (++i < ft_strlen(line) && !err)
	{
		len = get_cut(&line[i]);
		printf("i : %ld et len : %d\n", i, len);
		temp_line = ft_substr(&line[i], 0, len);
		temp = init_struct_pars(1);
		err = pars_line(temp_line, temp);
		ft_lstadd_back(&l, ft_lstnew(temp));
		i += len;
		if (line[i] == '|' || line[i] == '&')
		{
			ft_lstadd_back(&l, ft_lstnew((void *)ft_substr(&line[i], 0, 2)));
			i += 2;
		}
	}
	//if err all free;
	int	it = 0;
	while (l != NULL)
	{
		if (it % 2 == 0)
		{
			reader(l->content, 1);
			printf("la");
			// printf("%p\n", l->content);
		}
		else
			printf("%s\n", (char *)l->content);

		l = l->next;
		it++;
	}
	if (err)
		return (1);
	//reader((*d)->cmd, ft_strslen(exe));
	return (0);
}
