/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/11 16:34:21 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_path(t_cmd cmd, t_icmd *cmds, int nb_cmds)
{
	char	**tries;
	char	*paths;
	char	*path;
	int		i;

	if (access(cmd.args[0], F_OK | X_OK) == 0 || is_builtin(cmd.args[0]))
		return (ft_strdup(cmd.args[0]));
	i = -1;
	paths = ft_getenv("PATH");
	if (!paths)
		return (ft_perror(-1, ft_strsjoin((const char *[]){"mini: \
", cmd.args[0], " No such file or directory."}), 0), NULL);
	tries = ft_split(paths, ':');
	if (!tries)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds(cmds, nb_cmds)), NULL);
	while (tries[++i])
	{
		path = create_path(tries[i], cmd.args[0]);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab((void **)tries, count_words(paths, ':')), path);
		ft_del(path);
	}
	return (ft_free_tab((void **)tries, count_words(paths, ':')), NULL);
}
