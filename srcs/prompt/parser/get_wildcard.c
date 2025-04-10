/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:49:58 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/28 18:49:58 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**get_file(DIR *dir, char *end, char *path)
{
	struct stat		statbuf;
	struct dirent	*entry;
	char			**file;
	char			*all_path;
	int				i;

	file = malloc(sizeof(char *));
	file[0] = NULL;
	entry = readdir(dir);
	while (entry)
	{
		all_path = ft_strjoin(path, entry->d_name);
		stat(all_path, &statbuf);
		ft_del(all_path);
		if ((end[0] && S_ISDIR(statbuf.st_mode)) || !end[0])
		{
			i = 0;
			while (file[i]
				&& ft_strncmp(entry->d_name, file[i], ft_strlen(file[i])) > 0)
				i++;
			file = insert_strs(file, ft_strdup(entry->d_name), i, 0);
		}
		entry = readdir(dir);
	}
	return (ft_del(end), file);
}

char	*get_end(char *after)
{
	int		len;
	int		i;
	char	*str;
	int		j;

	len = 0;
	i = ft_strchri(after, "*")
		+ ft_strchri(&after[ft_strchri(after, "*")], "/");
	i--;
	while (after[++i])
		len++;
	i = ft_strchri(after, "*")
		+ ft_strchri(&after[ft_strchri(after, "*")], "/");
	j = 0;
	if (!len)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (len + 1));
	i--;
	while (after[++i])
		str[j++] = after[i];
	str[j] = 0;
	return (str);
}

char	*get_before(char *str)
{
	int		i;
	int		j;
	int		it;
	char	*before;

	i = ft_strchri(str, "*");
	j = ft_strchri(str, "*");
	while (j > 0 && str[j] && str[j] != '/')
		--j;
	if (j == i)
		return (ft_strdup(""));
	before = malloc(sizeof(char) * (i - j + 1));
	if (str[j] != '/')
		j--;
	it = -1;
	while (++j < i)
		before[++it] = str[j];
	before[++it] = 0;
	return (before);
}

char	*get_start(char *str)
{
	int		i;
	int		j;
	char	*start;

	i = -1;
	j = ft_strchri(str, "*");
	while (j > 0 && str[j] && str[j] != '/')
		--j;
	if (j == 0)
		return (ft_strdup(""));
	start = malloc(sizeof(char) * (j + 2));
	while (++i <= j)
		start[i] = str[i];
	start[i] = 0;
	return (start);
}

char	**get_after(char *str)
{
	int		i;
	char	**after;
	char *temp;

	i = ft_strchri(str, "*");
	if (ft_strchri(&str[i], "/"))
		temp = ft_substr(&str[i], 0, ft_strchri(&str[i], "/"));
	else
		temp = ft_substr(&str[i], 0, ft_strlen(&str[i]));

	if (!temp || !temp[0])
		return (NULL);
	after = ft_split(temp, '*');	
	return (ft_del(temp), after);
}
