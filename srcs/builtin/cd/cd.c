/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/04 14:16:49 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

char	*get_curpath(char *arg)
{
	char	*curpath;
	char	**cdpath;

	if (!arg)
		return (ft_strdup(ft_getenv("HOME=")));
	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (arg[0] == '~')
		return (create_path(ft_getenv("HOME="), arg + 1));//this aint how this one works bruh, if no HOME, still go HOME I guess ? Do better bro
	if (arg[0] == '.')
		return (create_path(ft_getenv("PWD="), arg));
	cdpath = NULL;
	if (ft_getenv("CDPATH="))
		cdpath = ft_split(ft_getenv("CDPATH="), ':');
	else if (ft_getloc("CDPATH="))
		cdpath = ft_split(ft_getloc("CDPATH="), ':');
	curpath = test_cdpath(cdpath, arg);
	ft_free_tab((void **)cdpath, ft_strslen((const char **)cdpath));
	if (curpath)
		return (curpath);
	return (create_path(ft_getenv("PWD="), arg));
}

char	**get_stack(char *curpath, int *depth)
{
	char	**stack;
	char	**path;
	int		i;

	path = ft_split(curpath, '/');
	stack = ft_calloc(ft_strslen((const char **)path) + 1, sizeof(char *));
	ft_del(curpath);
	if (!path || !stack)
		return (ft_free_tab((void **)path, ft_strslen((const char **)path)),
			ft_del(stack), ft_perror(1, 0, "Malloc error."), NULL);
	*depth = 0;
	i = -1;
	while (path[++i])
	{
		if (!ft_strncmp(path[i], "..", 3) && *depth > 0)
			(*depth)--;
		else if (ft_strncmp(path[i], ".", 2) != 0)
		{
			if (stack[*depth])
				ft_del(stack[*depth]);
			stack[(*depth)++] = ft_strdup(path[i]);
		}
	}
	ft_free_tab((void **)path, ft_strslen((const char **)path));
	return (stack);
}

// i3[0] = depth;
// i3[1] = len / j;
// i3[2] = i;
char	*clean_curpath(char *curpath)
{
	char	*clean;
	char	**path;
	int		i3[3];

	if (!curpath)
		return (curpath);
	path = get_stack(curpath, &i3[0]);
	i3[1] = ft_tern_int(i3[0] == 0, 2, 1);
	i3[2] = -1;
	while (++i3[2] < i3[0])
		i3[1] += ft_strlen(path[i3[2]]) + 1;
	clean = ft_calloc(i3[1], sizeof(char));
	if (!clean)
		return (ft_free_tab((void **)path, ft_strslen((const char **)path)),
			ft_perror(1, 0, "Malloc error."), NULL);
	i3[2] = -1;
	i3[1] = 0;
	clean[0] = '/';
	while (++i3[2] < i3[0])
	{
		clean[i3[1]++] = '/';
		ft_strlcpy(clean + i3[1], path[i3[2]], ft_strlen(path[i3[2]]) + 1);
		i3[1] += ft_strlen(path[i3[2]]);
	}
	return (ft_free_tab((void **)path, ft_strslen((const char **)path)), clean);
}

int	ft_cd(char **av)
{
	struct stat	path_stat;
	char		*curpath;
	t_list		*oldpwd;
	t_list		*pwd;

	if (!av[1])
		curpath = get_curpath(NULL);
	else if (av[2])
		return (ft_perror(-1, 0, "Too many arguments."), 1);
	else
		curpath = get_curpath(av[1]);
	curpath = clean_curpath(curpath);
	if (stat(curpath, &path_stat) != 0)
		return (ft_perror(-1, 0, "Directory does not exist."), 3);
	if (!S_ISDIR(path_stat.st_mode))
		return (ft_perror(-1, 0, "Path is not a directory."), 3);
	oldpwd = ft_getenv_struct("OLDPWD=");
	pwd = ft_getenv_struct("PWD=");
	ft_del(oldpwd->content);
	oldpwd->content = pwd->content;
	pwd->content = curpath;
	chdir(curpath);
	return (0);
}
