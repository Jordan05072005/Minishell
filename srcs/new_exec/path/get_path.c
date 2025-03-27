/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:25:50 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/27 18:24:06 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// char	*get_cmd_path(t_cmd input)
// {
// 	char	**tries;
// 	char	*paths;
// 	char	*path;
// 	int		i;

// 	i = -1;
// 	paths = ft_getenv("PATH");
// 	if (!paths)
// 		return (ft_perror(-1, ft_strsjoin((char *[]){"mini: \ 
// ", input.args[0], " No such file or directory.", NULL}), 0), NULL);
// 	tries = ft_split(paths, ':');
// 	if (!tries)
// 		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
// 			clean_data() + clean_icmds()), NULL);
// 	while (tries[++i])
// 	{
// 		path = create_path(tries[i], input.args[0]);
// 		if (access(path, F_OK | X_OK) == 0)
// 			return (ft_free_tab((void **)tries, count_words(paths, ':')), path);
// 		ft_del(path);
// 	}
// 	return (ft_free_tab((void **)tries, count_words(paths, ':')), NULL);
// }

char	*get_cmd_path(t_cmd input, t_icmd *cmd)
{
	char	**tries;
	char	*env_path;
	char	*path;
	int		i;

	env_path = ft_getenv("PATH");
	if (!env_path)
		return (ft_perror(-1, ft_strsjoin((char *[]){"mini: \
", input.args[0], " No such file or directory.", NULL}), 0),
			cmd->rv = 126, NULL);
	tries = ft_split(env_path, ':');
	if (!tries)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds()), NULL);
	while (tries[++i])
	{
		path = create_path(tries[i], input.args[0]);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab((void **)tries, ft_strslen(tries)), path);
		ft_del(path);
	}
	ft_perror(-1, ft_strsjoin((char *[]){input.args[0], ": Com\
mand not found.", NULL}), 0);
	return (ft_free_tab((void **)tries, ft_strslen(tries)),
		cmd->rv = 127, NULL);
}

char	*get_path(t_cmd input, t_icmd *cmd)
{
	struct	stat st;

	if (cmd->type != 1)
		return (NULL);
	if (ft_strnstr(input.args[0], "/", ft_strlen(input.args[0])))
	{
		if (stat(input.args[0], &st) == 0 && !S_ISREG(st.st_mode))
			return (ft_perror(-1, ft_strsjoin((char *[]){"mini: \
", input.args[0], ": Is a directory.", NULL}), 0),
				cmd->rv = 126, NULL);
		if (access(input.args[0], F_OK | X_OK) == 0)
			return (ft_strdup(input.args[0]));
		if (access(input.args[0], F_OK) == 0)
			return (ft_perror(-1, ft_strsjoin((char *[]){"mini: \
", input.args[0], ": Permission denied.", NULL}), 0),
				cmd->rv = 126, NULL);
		return (ft_perror(-1, ft_strsjoin((char *[]){"mini: \
", input.args[0], ": No such file or directory.", NULL}), 0),
				cmd->rv = 127, NULL);
	}
	return (get_cmd_path(input, cmd));
}
