/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:01:07 by jguaglio          #+#    #+#             */
/*   Updated: 2025/03/04 00:01:07 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	accessv(char *start, char *file, char *end)
{
	char	*path;
	char	*ende;

	if (strchr(end, '*'))
		ende = ft_strdup("\0");
	else
		ende = ft_strdup(end);
	path = ft_strsjoin((char *[]){start, file, ende, NULL});
	if (access(path, F_OK) == -1)
		return (ft_del(path), ft_del(ende), 1);
	return (ft_del(path), ft_del(ende), 0);
}

int existing2(t_wildcard *w, char *path, char *str, int i)
{
	struct dirent	*entry;

	entry = readdir(w->dir);
	w->before = get_before(str);
	w->after = get_after(&str[i]);
	while (entry)
	{
		if (!ft_strncmp(entry->d_name, w->before, ft_strlen(w->before)) &&
			!ft_strncmp(&entry->d_name[ft_strlen(entry->d_name) - ft_strlen(w->after) - 1],
			w->after, ft_strlen(w->after))
			&& ft_strncmp(entry->d_name, ".", 1) != 0)
		{
			path = ft_strjoin(w->path_temp, entry->d_name);
			if (access(path, F_OK) == 0)
				w->val += existing(path, &str[i + 1]);
			ft_del(path);
		}
		entry = readdir(w->dir);
	}
	i = w->val;
	return (cleanW(&w), i);
}

int existing(char *path, char *str)
{
	t_wildcard *w;
	int	i;

	i = -1;
	w = initWildcard(path);
	while (str[++i])
	{
		if (str[i] == '*')
		{
			w->dir = opendir(path);
			if (!(w->dir))
				return (cleanW(&w), 0);
			return (existing2(w, path, str, i));
		}
		if (str[i] == '/')
			w->path_temp = ft_strjoin_free(w->path_temp, "/");
	}
	path = ft_strjoin(path, str);
	i = w->val;
	if (access(path, F_OK) == 0)
		return (ft_del(path), cleanW(&w), i + 1);
	return (ft_del(path), cleanW(&w), i);
}