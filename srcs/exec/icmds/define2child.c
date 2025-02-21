/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define2child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:01:32 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/21 15:30:37 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**copy_args(char **src)
{
	char	**dest;
	int		len;

	len = ft_strslen(src);
	dest = ft_calloc(len + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	dest[len--] = NULL;
	while (len >= 0)
	{
		dest[len] = src[len];
		len--;
	}
	return (dest);
}

char	*get_env_path(t_icmd cmd)
{
	char	**tries;
	char	*paths;
	char	*path;
	int		i;

	i = -1;
	paths = ft_getenv("PATH");
	if (!paths)
		return (ft_perror(-1, ft_strsjoin((const char *[]){"mini: \
", cmd.args[0], " No such file or directory.", NULL}), 0), NULL);
	tries = ft_split(paths, ':');
	if (!tries)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds()), NULL);
	while (tries[++i])
	{
		path = create_path(tries[i], cmd.args[0]);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab((void **)tries, count_words(paths, ':')), path);
		ft_del(path);
	}
	return (ft_free_tab((void **)tries, count_words(paths, ':')), NULL);
}

char	*re_get_path(t_icmd cmd)
{
	if (is_builtin(cmd.args[0]) || (access(cmd.args[0], F_OK) == 0
			&& ft_strnstr(cmd.args[0], "/", ft_strlen(cmd.args[0]))))
		return (ft_strdup(cmd.args[0]));
	return (get_env_path(cmd));
}

void	define2child(t_icmd *cmds, int nb_cmds, int child, int start)
{
	char	**temp;

	temp = copy_args(&(cmds[child].args[start]));
	if (!temp)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."),
				clean_data() + clean_icmds());
	cmds[child].define = 2;
	cmds[child].args = temp;
	cmds[child].path = re_get_path(cmds[child]);
	if (!is_builtin(cmds[child].args[0]) && nb_cmds == 1)
	{
		cmds[child].pid = fork();
		if (cmds[child].pid == -1)
			ft_perror(1, ft_strdup("mini: Internal error: process."),
				clean_data() + clean_icmds());
		if (cmds[child].pid != 0)
			return ;
	}
	if (!is_builtin(cmds[child].args[0]))
		return (exec_child(cmds, nb_cmds, child));
	exec_builtin(cmds, nb_cmds, child);
}
