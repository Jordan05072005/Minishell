/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/10 17:01:04 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_curpath(char *arg)
{
	char	*curpath;
	char	**cdpath;

	if (!arg)
		return (ft_strdup(ft_getimp("HOME")));
	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (arg[0] == '~')
		return (create_path(ft_getimp("HOME"), arg + 1));//this aint how this one works bruh, if no HOME, still go HOME I guess ? Do better bro
	if (arg[0] == '.')
		return (create_path(ft_getimp("PWD"), arg));
	cdpath = NULL;
	if (ft_getenv("CDPATH"))
		cdpath = ft_split(ft_getenv("CDPATH"), ':');
	else if (ft_getloc("CDPATH"))
		cdpath = ft_split(ft_getloc("CDPATH"), ':');
	curpath = test_cdpath(cdpath, arg);
	ft_free_tab((void **)cdpath, ft_strslen(cdpath));
	if (curpath)
		return (curpath);
	return (create_path(ft_getimp("PWD"), arg));
}

char	**get_stack(char *curpath, int *depth)
{
	char	**stack;
	char	**path;
	int		i;

	path = ft_split(curpath, '/');
	stack = ft_calloc(ft_strslen(path) + 1, sizeof(char *));
	ft_del(curpath);
	if (!path || !stack)
		return (ft_free_tab((void **)path, ft_strslen(path)),
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
	ft_free_tab((void **)path, ft_strslen(path));
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
		return (ft_free_tab((void **)path, ft_strslen(path)),
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
	return (ft_free_tab((void **)path, ft_strslen(path)), clean);
}

void	update_env(char *curpath, int mode)
{
	t_list		*temp;
	t_list		*oldpwd;
	t_list		*pwd;

	pwd = ft_getimp_struct("PWD", &temp);
	ft_del(pwd->content);
	pwd->content = ft_strjoin("PWD=", curpath);
	if (mode == 0)
		return ;
	pwd = ft_getenv_struct("PWD", &temp);
	oldpwd = ft_getenv_struct("OLDPWD", &temp);
	if (oldpwd && pwd)
	{
		ft_del(oldpwd->content);
		oldpwd->content = ft_strjoin("OLDPWD=", pwd->content + 4);
	}
	if (oldpwd && !pwd)
		ft_lstdelink(&temp, &oldpwd, ft_del);
	if (pwd)
	{
		ft_del(pwd->content);
		pwd->content = ft_strjoin("PWD=", curpath);
	}
}

int	ft_cd(char **av)
{
	struct stat	path_stat;
	char		*curpath;

	if (!av[1])
		curpath = get_curpath(NULL);
	else if (av[2])
		return (ft_perror(-1, 0, "Too many arguments."), 1);
	else
		curpath = get_curpath(av[1]);
	if (is_dot(av[1]))
		update_env(curpath, 0);
	curpath = clean_curpath(curpath);
	if (stat(curpath, &path_stat) != 0)
		return (ft_del(curpath), ft_perror(-1, 0, "Directory does not exist."), 3);
	if (!S_ISDIR(path_stat.st_mode))
		return (ft_del(curpath), ft_perror(-1, 0, "Path is not a directory."), 3);
	update_env(curpath, 1);
	chdir(curpath);
	ft_del(curpath);
	return (0);
}
