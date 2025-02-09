/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:49:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 12:57:46 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void print_list(void *arg)
{
	ft_printf("%s\n", arg);
}


void	exec_child(t_icmd *cmds, int nb_cmds, int child)
{
	// ft_lstiter(data()->env, &print_list);
	set_io_cp(child, nb_cmds, cmds);
	close_fd(cmds, nb_cmds);
	if (!cmds[child].path)
		ft_perror(127, clean_icmds(cmds, nb_cmds) + clean_data(),
			"Command not found.");
	if (execve(cmds[child].path, cmds[child].args, env2env(data()->env)) == -1)
		ft_perror(127, clean_icmds(cmds, nb_cmds) + clean_data(),
			"An error occured during the execution of the command.");
}
