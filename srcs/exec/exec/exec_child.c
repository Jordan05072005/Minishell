/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:42:34 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/06 15:45:08 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_child(t_icmd *cmds, int nb_cmds, int child)
{
	int		rv;
	char	**env;

	set_io_cp(child, nb_cmds, cmds);
	close_fd(cmds, nb_cmds, child);
	if (!cmds[child].path)
	{
		rv = cmds[child].rv;
		ft_perror(rv, NULL, clean_data() + clean_icmds());
	}
	env = env2env(data()->env);
	if (execve(cmds[child].path, cmds[child].args, env) == -1)
	{
		ft_del(env);
		ft_perror(127, ft_strdup("mini: An error occured during the execution o\
f the command."), clean_icmds() + clean_data());
	}
}
