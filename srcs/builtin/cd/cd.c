/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/12 18:40:25 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//Create a new func for all the special cases.
char	*get_curpath(char *arg)
{
	char	*curpath;
	char	**cdpath;

	if (!arg)
		return (ft_strdup(ft_getenv("HOME")));
	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (arg[0] == '~')
		return (create_path(ft_getimp("HOME"), arg + 1));
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
		return (ft_free_tab((void **)path, ft_strslen(path)), ft_del(stack),
			ft_perror(1, ft_strdup("mini: Internal error: malloc"), 0), NULL);//Does not free like it should
	*depth = 0;
	i = -1;
	while (path[++i])
	{
		if (!ft_strncmp(path[i], "..", 3) && *depth > 0)
			(*depth)--;
		else if (!ft_strncmp(path[i], "..", 3) && *depth == 0)
			continue ;
		else if (ft_strncmp(path[i], ".", 2) != 0)
		{
			ft_del(stack[*depth]);
			stack[(*depth)++] = ft_strdup(path[i]);
		}
	}
	return (ft_free_tab((void **)path, ft_strslen(path)), stack);
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
			ft_perror(1, ft_strdup("mini: Internal error: malloc"), 0), NULL);//Does not free correctly ?????
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

/*
	If PWD is set in loc or env
	->	update PWD
	->	If OLDPWD is UNSET
	->	->	add OLDPWD to loc
	->	If OLDPWD has been NULLED
	->	->	update OLDPWD in env
	->	If OLDPWD is set in loc or env
	->	->	update OLDPWD
	If PWD is UNSET
	->	add PWD to loc
	->	If OLDPWD is set
	->	->	NULL OLDPWD
*/
void	update_env(char *curpath)
{
	static int	present = 0;
	t_list		*temp;
	t_list		*oldpwd;
	t_list		*pwd;

	pwd = ft_getimp_struct("PWD", &temp);
	ft_del(pwd->content);
	pwd->content = ft_strjoin("PWD=", curpath);
	pwd = ft_getenv_struct("PWD", &temp);
	if (!pwd)
		pwd = ft_getloc_struct("PWD", &temp);
	oldpwd = ft_getenv_struct("OLDPWD", &temp);
	if (!oldpwd && !present)
		oldpwd = ft_getloc_struct("OLDPWD", &temp);
	update_pwd(pwd, oldpwd, &present, curpath);
	if (present)
	{
		ft_lstremove_if(&(data()->loc), is_env, ft_del, "OLDPWD");
		ft_lstremove_if(&(data()->env), is_env, ft_del, "OLDPWD");
	}
}

int	ft_cd(char **av)
{
	struct stat	path_stat;
	char		*curpath;

	if (!av[1])
		curpath = get_curpath(NULL);
	else if (av[2])
		return (ft_perror(-1, ft_strdup("cd: Too many arguments."), 0), 1);
	else
		curpath = get_curpath(av[1]);
	if (is_dot(av[1]))
		update_env(curpath);
	curpath = clean_curpath(curpath);
	if (stat(curpath, &path_stat) != 0)
		return (ft_del(curpath),
			ft_perror(-1, ft_strdup("cd: No such file or directory."), 0), 3);
	if (!S_ISDIR(path_stat.st_mode))
		return (ft_del(curpath), ft_perror(-1, ft_strdup("cd: Not a directory."), 0), 3);
	update_env(curpath);
	chdir(curpath);
	ft_del(curpath);
	return (0);
}
