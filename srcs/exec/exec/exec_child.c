/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:49:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/11 17:01:51 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_child(t_icmd *cmds, int nb_cmds, int child)
{
	set_io_cp(child, nb_cmds, cmds);
	close_fd(cmds, nb_cmds, child);
	if (!cmds[child].path)
	{
		(void) (clean_icmds(cmds, nb_cmds) + clean_data());
		// ft_printf("I went here\n");
		// if (ft_getenv("PATH"))
		// 	ft_perror(127, ft_strsjoin((const char *[]){cmds[child].args[0],
		// 			": Command not found.", NULL}), clean_icmds(cmds, nb_cmds)
		// 		+ clean_data());
		exit(127);
	}
	if (execve(cmds[child].path, cmds[child].args, env2env(data()->env)) == -1)
		ft_perror(127, ft_strdup("mini: An error occured during the execution o\
f the command."), clean_icmds(cmds, nb_cmds) + clean_data());
}
