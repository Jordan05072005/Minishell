/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:16:11 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/07 09:32:38 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*create_path(char *first_component, char *second_component)
{
	char	*path;
	char	*dir_path;

	if (first_component[ft_strlen(first_component) - 1] != '/')
		path = ft_strjoin(first_component, "/");
	else
		path = ft_strdup(first_component);
	dir_path = ft_strjoin(path, second_component);
	ft_del(path);
	return (dir_path);
}

char	*test_cdpath(char **cdpath, char *arg)
{
	int			i;
	char		*dir_path;
	struct stat	path_stat;

	i = -1;
	if (!cdpath)
		return (NULL);
	while (cdpath[++i])
	{
		dir_path = create_path(cdpath[i], arg);
		if (stat(dir_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
			return (dir_path);
		ft_del(dir_path);
	}
	return (NULL);
}
