/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/30 14:44:14 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

	// if (!cmd.args)
	// 	return (exit(clean_icmds(cmds, nb_cmds)), NULL);
	// if (!cmd.args[0])
	// 	return (NULL);
char	*get_path(t_cmd cmd, t_icmd *cmds, int nb_cmds)
{
	char	**tries;
	char	*paths;
	char	*path;
	char	*temp;
	int		i;

	(void) cmds;
	(void) nb_cmds;
	if (ft_strncmp(cmd.args[0], "./", 2) == 0)
		return (ft_strdup(cmd.args[0]));
	i = -1;
	paths = getenv("PATH"); //should not be using this env
	tries = ft_split(paths, ':');
	while (tries && tries[++i])
	{
		temp = ft_strjoin(tries[i], "/");
		path = ft_strjoin(temp, cmd.args[0]);
		ft_del(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab((void **)tries, count_words(paths, ':')), path);
		ft_del(path);
	}
	ft_free_tab((void **)tries, count_words(paths, ':'));
	return (NULL);
}
