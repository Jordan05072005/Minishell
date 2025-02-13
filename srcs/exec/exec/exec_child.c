/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:49:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/13 11:15:32 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_child(t_icmd *cmds, int nb_cmds, int child)
{
	char	*message;

	set_io_cp(child, nb_cmds, cmds);
	close_fd(cmds, nb_cmds, child);
	if (!cmds[child].path)
	{
		if (ft_getenv("PATH"))
		{
			message = ft_strsjoin((const char *[]){cmds[child].args[0],
					": Command not found.", NULL});
			ft_perror(127, message, clean_icmds(cmds, nb_cmds) + clean_data());
		}
		else
			ft_perror(127, NULL, clean_icmds(cmds, nb_cmds) + clean_data());
	}
	if (access(cmds[child].path, F_OK | X_OK) != 0)
	{
		message = ft_strsjoin((const char *[]){"mini: ",
				cmds[child].path, ": Permission denied.", NULL});
		ft_perror(126, message, clean_icmds(cmds, nb_cmds) + clean_data());
	}
	if (execve(cmds[child].path, cmds[child].args, env2env(data()->env)) == -1)
		ft_perror(127, ft_strdup("mini: An error occured during the execution o\
f the command."), clean_icmds(cmds, nb_cmds) + clean_data());
}
