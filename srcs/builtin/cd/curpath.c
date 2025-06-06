/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:11:09 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/10 18:05:26 by hle-hena         ###   ########.fr       */
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
			ft_perror(1, ft_strdup("mini: Internal error: malloc"), 0), NULL);
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
			ft_perror(1, ft_strdup("mini: Internal error: malloc"), 0), NULL);
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

char	*regen_curpath(char *curpath)
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
	if (is_dot(arg))
		update_env(temp);
	return (ft_del(curpath), ft_del(temp), ft_perror(-1, ft_strdup("cd: error retrieving \
current directory: getcwd: cannot access parent directories: No such file or di\
rectory"), 0), NULL);
}

char	*check_curpath(char *curpath, char *arg, int special_print)
{
	struct stat	path_stat;

	if (!curpath)
		return (ft_perror(-1, ft_strsjoin((char *[]){"mini: cd: ", arg,
					": No such file or directory.", NULL}), 0), NULL);
	if (curpath[0] != '/')
		curpath = regen_curpath(curpath);
	if (stat(ft_getimp("PWD"), &path_stat) != 0)
		curpath = cd_nopwd(curpath, arg);
	if (!curpath)
		return (NULL);
	curpath = clean_curpath(curpath);
	return (cd_error_messages(curpath, arg, special_print));
}
