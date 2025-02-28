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
	return (ft_free_tab((void *)str1, ft_strslen(str1)), str_f);
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
		if (after[0] && name[len - s] != after[ft_strlen(after) - end - 1])
			return (1);
		if (s < ft_strlen(before))
			s++;
		if (end < ft_strlen(after))
			end++;
	}
	return (0);
}

char	**insert_file(char **str, int j, int i, char **file)
{
	int		f;
	int		w;
	char	*before;
	char	*after;

	before = ft_substr(str[j], 0, i);
	after = ft_substr(str[j], i + 1, ft_strlen(str[j]));
	w = 0;
	f = -1;
	while (file[++f])
	{
		if (!ft_strchr(before, '.') && file[f][0] == '.')
			any(0);
		else if (!name_correct(file[f], before, after, ft_strlen(file[f]) - 1))
			str = insert_strs(str, file[f], j++, 0 == w++);
	}
	return (ft_del(before), ft_del(after),
		ft_free_tab((void *)file, ft_strslen(file)), str);
}

char	**get_file(DIR *dir)
{
	struct dirent	*entry;
	char			**file;
	int				i;

	file = malloc(sizeof(char *));
	file[0] = NULL;
	entry = readdir(dir);
	while (entry)
	{
		i = 0;
		while (file[i]
			&& ft_strncmp(entry->d_name, file[i], ft_strlen(file[i])) > 0)
			i++;
		file = insert_strs(file, entry->d_name, i, 0);
		entry = readdir(dir);
	}
	return (file);
}

// si avant y'a / -> prend se chemin
// sinon reduire la recherche a avant apres 
// juste * == all
// riens on ecrit jsute *dededde = *dededde
char	**wildcard(char **str, int j)
{
	DIR		*dir;
	char	**file;

	dir = opendir(ft_getimp("PWD"));
	if (!dir)
		return (NULL);
	file = get_file(dir);
	str = insert_file(str, j, ft_strchri(str[j], "*"), file);
	return (free(dir), str);
}
