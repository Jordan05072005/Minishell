/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:16:28 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/04 17:19:56 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_builtin(t_icmd *cmds, int nb_cmds, int child)
{
	int	saved_i;
	int	saved_o;

	saved_i = dup(0);
	saved_o = dup(1);
	set_io_cp(child, nb_cmds, cmds);
	// ft_del(cmds[child].path);
	if (!ft_strncmp(cmds[child].args[0], "cd", 3))
		cmds[child].exit = ft_cd(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "pwd", 4))
		cmds[child].exit = ft_pwd(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "unset", 6))
		cmds[child].exit = ft_unset(cmds[child].args);
	else if (!ft_strncmp(cmds[child].args[0], "env", 4))
		cmds[child].exit = ft_env(cmds[child].args);
	else
		cmds[child].exit = 1;
	dup2(saved_i, 0);
	dup2(saved_o, 1);
}
