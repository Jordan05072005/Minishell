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


char	**get_file(DIR *dir, char *after, char *path)
{
	struct dirent	*entry;
	char			**file;
	int				i;
	struct stat statbuf;
	char	*all_path;

	file = malloc(sizeof(char *));
	file[0] = NULL;
	entry = readdir(dir);
	while (entry)
	{
		all_path = ft_strjoin(path, entry->d_name);
		stat(all_path, &statbuf);
		ft_del(all_path);
		if ((after[0] == '/' && S_ISDIR(statbuf.st_mode) ) || after[0] != '/')
		{
			i = 0;
			while (file[i]
				&& ft_strncmp(entry->d_name, file[i], ft_strlen(file[i])) > 0)
				i++;
			file = insert_strs(file, ft_strdup(entry->d_name), i, 0);
		}
		entry = readdir(dir);
	}
	return (ft_del(after), file);
}

char	*get_end(char *after)
{
	int		len;
	int		i;
	char	*str;
	int		j;

	len = 0;
	i = ft_strchri(after, "*") + ft_strchri(&after[ft_strchri(after, "*")], "/");
	i--;
	while (after[++i])
			len++;
	i = ft_strchri(after, "*") + ft_strchri(&after[ft_strchri(after, "*")], "/");
	j = 0;
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
	j =  ft_strchri(str, "*");
	while (j > 0 && str[j] && str[j] != '/')
		--j;
	if (j == i)
		return (ft_strdup(""));
	before = malloc(sizeof(char) * (i - j));
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
	j =  ft_strchri(str, "*");
	while (j > 0 && str[j] && str[j] != '/')
		--j;
	if (j == 0)
		return (ft_strdup(""));
	start = malloc(sizeof(char) * (j + 1));
	while (++i <= j)
		start[i] = str[i];
	start[i] = 0;
	return (start);
}



char	*get_after(char *str)// tout apres la /
{
	int		i;
	int		j;
	int		it;
	char	*after;
	
	i = ft_strchri(str, "*");
	j = ft_strchri(str, "*");
	if (j == (int)ft_strlen(str))
		return (ft_strdup(""));
	j++;
	while (str[j] && str[j] != '/' && str[j] != '*')
		++j;
	after = malloc(sizeof(char) * (j - i + 1));
	it = -1;
	while (++i < j)
		after[++it] = str[i];
	after[++it] = 0;
	return (after);
}