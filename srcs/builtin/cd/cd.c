/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/13 20:05:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*special_cd(char *arg)
{
	char	*path;

	if (!arg)
	{
		path = ft_getenv("HOME");
		if (!path)
			path = ft_getloc("HOME");
		return (ft_strdup(path));
	}
	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (arg[0] == '~')
	{
		path = ft_getenv("HOME");
		if (!path)
			path = ft_getloc("HOME");
		if (!path)
			path = ft_getimp("HOME");
		return (create_path(path, arg + 1));
	}
	if (arg[0] == '.')
		return (create_path(ft_getimp("PWD"), arg));
	return ("../");
}

int	ft_cd(char **av)
{
	char		*curpath;

	if (ft_strslen(av) > 2)
		return (ft_perror(-1, ft_strdup("mini: cd: Too many arguments."), 0),
			1);
	curpath = special_cd(av[1]);
	if (!curpath)
		return (ft_perror(-1, ft_strdup("mini: cd: HOME is not set."), 0), 1);
	else if (!ft_strncmp(curpath, "../", 4))
		curpath = get_curpath(av[1]);
	curpath = check_curpath(curpath, av[1]);
	if (!curpath)
		return (1);
	chdir(curpath);
	ft_del(curpath);
	return (0);
}
