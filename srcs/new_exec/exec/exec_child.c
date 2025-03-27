/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:42:34 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/27 18:47:58 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_child(t_icmd *cmds, int nb_cmds, int child)
{
	set_io_cp(child, nb_cmds, cmds);
	close_fd(cmds, nb_cmds, child);
	if (!cmds[child].path)
		ft_perror(cmds[child].rv, NULL, clean_data() + clean_icmds());
	if (execve(cmds[child].path, cmds[child].args, env2env(data()->env)) == -1)
		ft_perror(127, ft_strdup("mini: An error occured during the execution o\
f the command."), clean_icmds() + clean_data());
}
