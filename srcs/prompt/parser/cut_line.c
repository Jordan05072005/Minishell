/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:34:55 by jguaglio          #+#    #+#             */
/*   Updated: 2025/03/09 14:34:55 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**addback_str(char **str, char *add)
{
	char	**strf;
	int		i;

	if (add == NULL)
		return (str);
	strf = malloc(sizeof(char *) * (ft_strslen(str) + 2));
	i = -1;
	while (str[++i])
		strf[i] = str[i];
	strf[i] = add;
	strf[i + 1] = 0;
	return (ft_del(str), strf);
}

int	is_cut(char c, char old, int *etat)
{
	char	*sep;

	sep = ft_strdup("<>|& \t");
	if ((*etat) && c == old)
		return (ft_del(sep), 0);
	if ((*etat) && c != old)
	{
		if (!ft_strchr(sep, c))
			(*etat) = 0;
		return (ft_del(sep), 1);
	}
	if (!(*etat) && ft_strchr(sep, c))
	{
		(*etat) = 1;
		return (ft_del(sep), 1);
	}
	if (!(*etat) && !ft_strchr(sep, c))
		return (ft_del(sep), 0);
	return (ft_del(sep), 0);
}

char	**cut_line(char *line)
{
	int		i;
	int		old;
	char	**arg;
	int		etat;
	char	quote;

	i = -1;
	etat = 0;
	arg = malloc(sizeof(char *));
	arg[0] = NULL;
	old = 0;
	while (++i <= (int)ft_strlen(line))
	{
		if (line[i] == '"' || line[i] == '\'' || line[i] == '(')
		{
			quote = line[i];
			if (line[i] == '(')
				quote = ')';
			if (i > 0 && line[i - 1] != '"' && line[i - 1] != '\'' && line[i - 1] != ')')
				arg = addback_str(arg, ft_substr(line, old, i - old));
			old = i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote && line[i] != line[old + 1])
				arg = addback_str(arg, ft_substr(line, old, i - old + 1));
			else if (!line[i])
				return (ft_free_tab((void *)arg, ft_strslen(arg)), NULL);
			old = i + 1;
		}
		else if (is_cut(line[i], line[old], &etat) || !line[i])
		{
			if ((old != 0 || i != 0) && (old != (int)ft_strlen(line)))
				arg = addback_str(arg, ft_substr(line, old, i - old));
			old = i;
		}
	}
	return (arg);	
}
