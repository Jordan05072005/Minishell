/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/13 22:19:11 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*cd_previous(char *arg, char *unused, int *print)
{
	char	*path;

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
	if (arg[1] != '-' || ft_strlen(arg) > 2)
		return (ft_perror(-1, ft_strsjoin((const char *[]){"mini: cd: ", arg, "\
: invalid option.", NULL}), 0), NULL);
	path = ft_getenv("HOME");
	if (!path)
		path = ft_getloc("HOME");
	if (!path)
		return (ft_perror(-1, ft_strdup("mini: cd: HOME is not set."), 0),
			NULL);
	return (ft_strdup(path));
}

char	*special_cd(char *arg)
{
	char	*path;

	if (!arg)
	{
		path = ft_getenv("HOME");
		if (!path)
			path = ft_getloc("HOME");
		if (!path)
			return (ft_perror(-1, ft_strdup("mini: cd: HOME is not set."), 0), NULL);
		return (ft_strdup(path));
	}
	if (arg[0] == '/')
		return (ft_strdup(arg));
	//the following one should not exist, it should be done in parsing.
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
	char	*curpath;
	size_t	option;
	int		print;

	print = 0;
	option = (ft_strncmp(av[1], "--", 3) == 0);
	if (ft_strslen(av) > 2 + option)
		return (ft_perror(-1, ft_strdup("mini: cd: Too many arguments."), 0),
			1);
	curpath = special_cd(av[1 + option]);
	if (!curpath)
		return (1);
	else if (!ft_strncmp(curpath, "../", 4))
		curpath = get_curpath(av[1 + option], &print);
	if (access(curpath, F_OK) != 0 && av[1 + option][0] == '-')
		curpath = cd_previous(av[1 + option], curpath, &print);
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
