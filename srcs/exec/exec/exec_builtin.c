/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:16:28 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/12 15:16:11 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_builtin(t_icmd *cmds, int nb_cmds, int child)
{
	int	saved[2];

	saved[0] = dup(0);
	saved[1] = dup(1);
	set_io_cp(child, nb_cmds, cmds);
	if (!ft_strncmp(cmds[child].args[0], "cd", 3))
		cmds[child].exit = ft_cd(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "pwd", 4))
		cmds[child].exit = ft_pwd(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "export", 7))
		cmds[child].exit = ft_export(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "unset", 6))
		cmds[child].exit = ft_unset(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "env", 4))
		cmds[child].exit = ft_env(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "exit", 5))
		cmds[child].exit = ft_exit();
	else if (!ft_strncmp(cmds[child].args[0], "echo", 5))
		cmds[child].exit = ft_echo(&cmds[child]);
	else
		cmds[child].exit = ft_color(cmds[child].args);
	dup2(saved[0], 0);
	dup2(saved[1], 1);
	if (nb_cmds > 1)
		return (clean_data(), clean_icmds(cmds, nb_cmds), exit(cmds[child].exit));//This is stupid, access a var after freeing it .............
}
