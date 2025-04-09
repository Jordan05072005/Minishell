/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:57:40 by jguaglio          #+#    #+#             */
/*   Updated: 2025/03/19 14:57:40 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_sep(char c)
{
	if (c == '|' || c == '<' || c == '&' || c == '>')
		return (1);
	return (0);
}

char	*error_line(char *line, char *temp, int i)
{
	int	prof;
	int *quote;

	prof = 0;
	quote = 0;
	while (line[++i])
	{
		quote = quotes(line[i], quote);
		if (line[i] == '(' && quote[2] && prof >= 0)
			prof++;
		else if (line[i] == ')' && quote[2])
			prof--;
	}
	if (!quote[2] || prof > 0)
		return (ft_del(temp), ft_del(quote), ft_strdup("newline"));
	if (prof < 0)
		return (ft_del(temp), ft_del(quote), ft_strdup(")"));
	return (ft_del(temp), ft_del(quote), NULL);
}

char	*syntax_error3(char **arg, char *mess, int i)
{
	char	*temp;
	char	**err;

	temp = ft_strsjoin((char *[]){">>.", ">.", "<<.", "<", NULL});
	err = ft_split(temp, '.');
	while (!mess && ++i < 4)
	{
		ft_del2((void **)&temp);
		if (!ft_strncmp(arg[0], err[i], ft_strlen(err[i])))
		{	
			if ((ft_strslen(arg) - (arg[1] && ft_isspace(arg[1][0]) == 1)) == 1 
				&& ft_strlen(arg[0]) <= 2)
				mess = ft_strdup("newline");
			else if ((ft_strslen(arg) - (arg[1] && ft_isspace(arg[1][0]) == 1)) == 1
				&& ft_strlen(arg[0]) > 2 && is_sep(arg[0][2]))
				temp = ft_substr(arg[0], 2, 2);
			else if (ft_strslen(arg) > 1 && is_sep(arg[farg(&arg[1])][0]))
				temp = ft_substr(arg[farg(&arg[1])], 0 , 2);
			if (temp)
				mess = ft_strdup(temp) ; 
		}
	}
	return (ft_del(temp), ft_free_tab((void *)err, ft_strslen(err)), mess);
}

char *syntax_error2(char **arg, int j, char *line2)
{
	char	*err;
	char	*line;

	if (arg[j][0] == '(')
	{
		if (j > 0 && beforec(arg, j) && !is_sep(beforec(arg, j)[0]))
			return (ft_strdup("("));
		else if ((arg[j + 1] && nextc(&arg[j + 1]) && !is_sep(nextc(&arg[j + 1])[0])))
			return (ft_substr(nextc(&arg[j + 1]), 0, 2));
		else if (arg[j][farg2(&arg[j][1])] == ')')
			return (ft_strdup(")"));
		else
		{
			line = ft_strtrim(arg[j], "()");
			err = syntax_error(cut_line(line), line2,  -1, -1);
			ft_del(line);
			return (err);
		}
	}
	return (syntax_error3(&arg[j], NULL, -1));
}

// ft_isalnum(arg[farg(arg) - 1][0]
char	*syntax_error(char **arg, char *line, int i, int j)
{
	char	**err;
	char	*temp;

	temp = ft_strsjoin((char *[]){"||.", "|.", "&&.", "&.", NULL});
	err = ft_split(temp, '.');
	temp = error_line(line, temp, -1);
	while (arg && arg[0] && !temp && arg[++j])
	{
		i = -1;
		while (!temp && err[++i] && arg[j])
		{
			if (arg[j][0] == err[i][0] && (((ft_strlen(arg[j]) > 2 || ((!nextc(&arg[j + 1])
				|| (is_sep(nextc(&arg[j + 1])[0])))
				&& ft_strlen(arg[j]) == ft_strlen(err[i])))
				&& ft_strnstr(arg[j], err[i], ft_strlen(arg[j]))) || (j  == 0
				&& ft_strnstr(arg[j], err[i], ft_strlen(arg[j])))))
				temp = ft_strdup(err[i]);
			else if (!temp)
				temp = syntax_error2(arg, j, line);
		}
	}
	return (ft_free_tab((void *)arg, ft_strslen(arg)),
			ft_free_tab((void *)err, ft_strslen(err)), temp);
}