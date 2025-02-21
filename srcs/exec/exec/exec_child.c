/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:49:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/21 14:08:55 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exit_exec(char *message, int exit_status)
{
	ft_perror(exit_status, message, clean_icmds() + clean_data());
}

void	exec_child(t_icmd *cmds, int nb_cmds, int child)
{
	set_io_cp(child, nb_cmds, cmds);
	close_fd(cmds, nb_cmds, child);
	if (!cmds[child].args)
		exit_exec(NULL, 0);
	if (!cmds[child].args[0])
		exit_exec(NULL, 0);
	if (!cmds[child].path)
	{
		if (ft_getenv("PATH"))
			exit_exec(ft_strsjoin((const char *[]){cmds[child].args[0], ": Com\
mand not found.", NULL}), 127);
		else
			exit_exec(NULL, 127);
	}
	if (access(cmds[child].path, F_OK | X_OK) != 0)
		exit_exec(ft_strsjoin((const char *[]){"mini: ", cmds[child].path, ": \
Permission denied.", NULL}), 127);
	if (execve(cmds[child].path, cmds[child].args, env2env(data()->env)) == -1)
		ft_perror(127, ft_strdup("mini: An error occured during the execution o\
f the command."), clean_icmds() + clean_data());
}
