/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:49:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 11:00:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

void	exec_child(t_icmd *cmds, int nb_cmds, int child, char **env)
{
	set_io_cp(child, nb_cmds, cmds);
	close_fd(data);
	if (!cmds[child].cmd_path)
		exit(127); //Should clean I think
	if (execve(cmds[child].path, cmds[child].args, env) == -1)
		ft_perror(127, 0/* clean_data(data) */, "An error occured during the execution of \
the command.");
}
