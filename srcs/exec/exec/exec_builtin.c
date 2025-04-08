/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:48:24 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/08 14:39:15 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	switch_cmd(t_icmd *cmds, int child)
{
	if (!ft_strncmp(cmds[child].args[0], "cd", 3))
		cmds[child].rv = ft_cd(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "pwd", 4))
		cmds[child].rv = ft_pwd(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "export", 7))
		cmds[child].rv = ft_export(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "unset", 6))
		cmds[child].rv = ft_unset(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "env", 4))
		cmds[child].rv = ft_env(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "exit", 5))
		cmds[child].rv = ft_exit(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "echo", 5))
		cmds[child].rv = ft_echo(&cmds[child]);
	else
		cmds[child].rv = ft_color(cmds[child].args);
	return (cmds[child].rv);
}

void	exec_builtin(t_icmd *cmds, int nb_cmds, int child)
{
	int	saved[2];
	int	exit_status;

	saved[0] = dup(0);
	saved[1] = dup(1);
	if (nb_cmds > 1)
		set_io_cp(child, nb_cmds, cmds);
	else if (set_io_p(child, nb_cmds, cmds))
		return ;
	close_fd(cmds, nb_cmds, child);
	exit_status = switch_cmd(cmds, child);
	dup2(saved[0], 0);
	dup2(saved[1], 1);
	if (nb_cmds > 1)
		return (clean_data(), clean_icmds(), exit(exit_status));
}


//((exit 1) && ls)