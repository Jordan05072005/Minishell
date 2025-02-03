/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/03 15:07:26 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

char	*test_cdpath(char **cdpath, char *arg)
{
	int			i;
	char		*dir_path;
	struct stat	path_stat;

	i = -1;
	while (cdpath[++i])
	{
		dir_path = create_path(cdpath[i], arg);
		if (stat(dir_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
			return (dir_path);
		ft_del(dir_path);
	}
	return (NULL);
}

char	*get_curpath(char *arg)
{
	char	*curpath;

	if (!arg)
		return (ft_strdup(ft_getenv("HOME=")));
	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (arg[0] == '~')
		return (create_path(ft_getenv("HOME="), arg + 1));//this aint how this one works bruh, if no HOME, still go HOME I guess ? Do better bro
	if (arg[0] == '.')
		return (create_path(ft_getenv("PWD="), arg));
	if (ft_getenv("CDPATH="))
		cdpath = ft_split(ft_getenv("CDPATH="), ':');
	else if (ft_getloc("CDPATH="))
		cdpath = ft_split(ft_getloc("CDPATH="), ':');
	curpath = test_cdpath(cdpath, arg);
	ft_free_tab(cdpath, ft_strslen(cdpath));
	if (curpath)
		return (curpath);
	return (create_path(ft_getenv("PWD="), arg));
}

char	**get_stack(char *curpath)
{
	char	**stack;
	char	**path;
	int		depth;
	int		i;

	path = ft_split(curpath, '/');
	stack = ft_calloc(ft_strslen(path) + 1, sizeof(char *));
	ft_del(curpath);
	if (!path || !stack)
		return (ft_free_tab(path, ft_strslen(path)), ft_del(stack),
			ft_perror(1, 0, "Malloc error."));
	depth = 0;
	i = -1;
	while (path[++i])
	{
		if (!ft_strncmp(path[i], "..", 3) && depth > 0)
			depth--;
		else if (ft_strncmp(path[i], "..", 3) != 0)
			stack[depth++] = ft_strdup(path[i]);
	}
	stack[depth] = NULL;
	ft_del(path);
	return (stack);
}

char	*clean_curpath(char *curpath)
{
	char	*clean;
	char	**stack;
	int		len;
	int		i;

	if (!curpath)
		return (curpath);
	stack = get_stack(curpath);
	len = 1;
	i = -1;
	while (stack[++i])
		len += ft_strlen(stack[i]) + 1;
	clean = ft_calloc(len, sizeof(char));
	if (!clean)
		return (ft_del(stack), ft_perror(1, 0, "Malloc error."));
	i = -1;
	clean[0] = '/';
	len = 1;
	while (stack[++i])
	{
		ft_strlcpy(clean + len, stack[i], ft_strlen(stack[i]) + 1);
		len += ft_strlen(stack[i]);
		if (stack[i + 1])
			clean[len++] = '/';
	}
	return (ft_del(stack), clean);
}

char	*clean_curpath(char *curpath)
{
	char	*clean;
	char	**stack;
	int		len;
	int		i;

	if (!curpath)
		return (curpath);
	stack = get_stack(curpath);
	len = 1;
	i = -1;
	while (stack[++i])
		len += ft_strlen(stack[i]) + 1;
	clean = ft_calloc(len, sizeof(char));
	if (!clean)
	{
		ft_del(stack);
		return (ft_perror(1, 0, "Malloc error."));
	}
	i = -1;
	clean[0] = '/';
	len = 1;
	while (stack[++i])
	{
		ft_strlcpy(clean + len, stack[i], ft_strlen(stack[i]) + 1);
		len += ft_strlen(stack[i]);
		if (stack[i + 1])
			clean[len++] = '/';
	}
	ft_del(stack);
	return (clean);
}


int	ft_cd(char **av)
{
	struct stat	path_stat;
	char		*curpath;
	char		*oldpwd;
	char		*pwd;

	if (!av[1])
		curpath = get_curpath(NULL)
	else if (av[2])
		return (ft_perror(-1, 0, "Too many arguments."), 1);
	else
		curpath = get_curpath(av[1]);
	curpath = clean_curpath(curpath);
	if (stat(dir_path, &path_stat) != 0)
		return (ft_perror(-1, 0, "Directory does not exist."), 3);
	if (!S_ISDIR(path_stat.st_mode))
		return (ft_perror(-1, 0, "Path is not a directory."), 3);
	oldpwd = ft_getenv_struct("OLDPWD=");
	pwd = ft_getenv_struct("PWD=");
	ft_del(oldpwd.content);
	oldpwd.content = pwd.content;
	pwd.content = curpath;
	chdir(curpath);
}
