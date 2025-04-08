/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 02:02:36 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/27 02:02:36 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


char **del_strs(char **str, int j, char *s)
{
	int	i;
	int	len;
	int	it;
	char	**str2;

	i = j - 1;
	len = 0;
	while (str[++i])
	{
		if (ft_strncmp(str[i], s, ft_strlen(s)) != 0)
			len++;
	}
	str2 = malloc(sizeof(char *) * (len + 1 + j));
	i = -1;
	it = -1;
	while (str[++i])
	{
		if (i < j || ft_strncmp(str[i], s, ft_strlen(s)) != 0)
			str2[++it] = str[i];
		else
			ft_del2((void **)&str[i]);
	}
	str2[++it] = NULL;
	return (ft_del2((void **)&s), ft_del(str), str2);
}

char	**insert_strs(char **str1, char *str2, int j, int overwrite)
{
	int		i;
	int		i1;
	int		len;
	char	**str_f;

	len = ft_strslen(str1) + (overwrite == 0);
	str_f = malloc(sizeof(char *) * (len + 1));
	i = -1;
	i1 = -1;
	while (++i < len)
	{
		if (i != j)
			str_f[i] = ft_strdup(str1[++i1]);
		else
			str_f[i] = ft_strdup(str2);
		if (overwrite && i == j)
			++i1;
	}
	str_f[i] = NULL;
	return (ft_free_tab((void *)str1, ft_strslen(str1)), ft_del(str2), str_f);
}

int	name_correct(char *name, char *before, char *after, int len)
{
	size_t	s;
	size_t	end;

	end = ft_strlen(name);
	if (!before[0] && !after[0])
		return (0);
	end = 0;
	s = 0;
	while (s < ft_strlen(before) || end < (ft_strlen(after)))
	{
		if (before[0] && name[s] != before[s])
			return (1);
		if (after[0] && name[len - end] != after[ft_strlen(after) - end - 1]) // a modif
			return (1);
		if (s < ft_strlen(before))
			s++;
		if (end < ft_strlen(after))
			end++;
	}
	return (0);
}

char	**insert_file(char **str, int j, char **file)
{
	int		f;
	char	*before;
	char	*after;
	char *end;
	char	*start;

	before = get_before(str[j]);
	after = get_after(str[j]);
	end = get_end(str[j]);
	start = get_start(str[j]);
	f = -1;
	while (file && file[++f])
	{
		if (!ft_strchr(before, '.') && file[f][0] == '.')
			any(0);
		else if (!name_correct(file[f], before, after, ft_strlen(file[f]) - 1) && !accessv(start, file[f], end))
			str = insert_strs(str, ft_strsjoin((char *[]){start, file[f], end, NULL}), j++, 0);
	}
	return (ft_del(before), ft_del(after),
		ft_free_tab((void *)file, ft_strslen(file)), ft_del(end), ft_del(start), str);
}

char	**wildcard(char **str, int *j)
{
	DIR		*dir;
	char	**file;
	char	*path;
	char	*temp;

	path = get_start(str[*j]);
	temp = ft_strdup(str[*j]);
	if (!path[0])
	{
		ft_del2((void **)&path);
		path = ft_strdup("./");
	}
	if (existing(path, str[*j]) <= 0)
		return (ft_del(path), ft_del(temp), str);
	dir = opendir(path);
	if (!dir)
		return (del_strs(str, (*j)--, temp));
	file = get_file(dir	,ft_substr(str[*j], ft_strchri(str[*j], "*") + ft_strchri(&str[*j][ft_strchri(str[*j], "*")], "/"), ft_strlen(str[*j])), path);
	str = insert_file(str, *j, file);
	return (closedir(dir), ft_del(path), del_strs(str, (*j)--, temp));
}
