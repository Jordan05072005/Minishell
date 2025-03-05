/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:11:09 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/27 13:36:05 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

char *regen_curpath(char *curpath)
{
	char	*dest;

	dest = create_path(ft_getimp("PWD"), curpath);
	ft_del(curpath);
	return (dest);
}

char	*cd_nopwd(char *curpath, char *arg)
{
	struct stat	path_stat;
	char		*temp;

	temp = ft_strdup(curpath);
	curpath = clean_curpath(curpath);
	if (stat(curpath, &path_stat) == 0)
		return (ft_del(temp), curpath);
	if (is_dot(arg))//I dont like this, there is probably a better idea.
		update_env(temp);
	return (ft_del(curpath), ft_del(temp), ft_perror(-1, ft_strdup("cd: error retrieving \
current directory: getcwd: cannot access parent directories: No such file or di\
rectory"), 0), NULL);
}

char	*check_curpath(char *curpath, char *arg)
{
	struct stat	path_stat;

	if (!curpath)
		return (ft_perror(-1, ft_strsjoin((const char *[]){"mini: cd: ", arg,
			": No such file or directory.", NULL}), 0), NULL);
	if (curpath[0] != '/')
		curpath = regen_curpath(curpath);
	if (stat(ft_getimp("PWD"), &path_stat) != 0)
		curpath = cd_nopwd(curpath, arg);
	if (!curpath)
		return (NULL);
	curpath = clean_curpath(curpath);
	if (stat(curpath, &path_stat) != 0)
		return (ft_del(curpath), ft_perror(-1, ft_strsjoin((const char *[]){"mi\
ni: cd: ", arg, ": No such file or directory.", NULL}), 0), NULL);
	if (!S_ISDIR(path_stat.st_mode))
		return (ft_del(curpath), ft_perror(-1, ft_strsjoin((const char *[]){"mi\
ni: cd: ", arg, ": Not a directory.", NULL}), 0), NULL);
	update_env(curpath);
	return (curpath);
}

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
