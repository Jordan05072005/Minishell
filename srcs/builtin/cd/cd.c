/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/10 15:42:40 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_curpath(char *arg, int *print)
{
	char	*curpath;
	char	*cdpath;
	char	**cdpaths;

	cdpaths = NULL;
	cdpath = ft_getenv("CDPATH");
	if (!cdpath)
		cdpath = ft_getloc("CDPATH");
	if (cdpath)
		cdpaths = ft_split(cdpath, ':');
	curpath = test_cdpath(cdpaths, arg);
	ft_free_tab((void **)cdpaths, ft_strslen(cdpaths));
	if (!curpath)
		curpath = create_path(ft_getimp("PWD"), arg);
	else
		*print = 1;
	return (curpath);
}

char	*cd_previous(char *arg, char *unused, int *print, int option)
{
	char	*path;

	if (!arg)
		return (unused);
	if (arg[0] != '-')
		return (unused);
	if (arg[1] && option)
		return (unused);
	ft_del(unused);
	if (!arg[1])
	{
		path = ft_getenv("OLDPWD");
		if (!path)
			path = ft_getloc("OLDPWD");
		if (!path)
			return (ft_perror(-1, ft_strdup("mini: cd: OLDPWD is not set."), 0),
				NULL);
		*print = 1;
		return (ft_strdup(path));
	}
	else
		return (ft_perror(-1, ft_strsjoin((char *[]){"mini: cd: ", arg, "\
: Invalid option.", NULL}), 0), NULL);
}

char	*find_path(char *arg, int *print)
{
	char	*path;

	if (!arg)
	{
		path = ft_getenv("HOME");
		if (!path)
			path = ft_getloc("HOME");
		if (!path)
			return (ft_perror(-1, ft_strdup("mini: cd: HOME is not set."), 0),
				NULL);
		return (ft_strdup(path));
	}
	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (arg[0] == '.')
		return (create_path(ft_getimp("PWD"), arg));
	return (get_curpath(arg, print));
}

int	ft_cd(char **av)
{
	char	*curpath;
	size_t	option;
	int		print;

	print = 0;
	option = 0;
	if (av[1])
		option = (ft_strncmp(av[1], "--", 3) == 0);
	if (ft_strslen(av) > 2 + option)
		return (ft_perror(-1, ft_strdup("mini: cd: Too many arguments."), 0),
			1);
	curpath = find_path(av[1 + option], &print);
	if (!curpath)
		return (1);
	curpath = cd_previous(av[1 + option], curpath, &print, option);
	if (!curpath)
		return (1);
	curpath = check_curpath(curpath, av[1 + option]);
	if (!curpath)
		return (1);
	if (print)
		ft_putendl_fd(curpath, 1);
	chdir(curpath);
	return (ft_del(curpath), 0);
}
