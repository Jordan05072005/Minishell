/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:16:28 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/04 13:14:44 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_builtin(t_icmd *cmds, int nb_cmds, int child, char **env)
{
	(void) env;
	set_io_cp(child, nb_cmds, cmds);
	ft_del(cmds[child].path);
	if (ft_strncmp(cmds[child].args[0], "cd", 3))
		cmds[child].exit = 0;// ft_cd(cmds[child].args, env)
	else if (ft_strncmp(cmds[child].args[0], "pwd", 4))
		cmds[child].exit = ft_pwd(cmds[child].args);
	else
		cmds[child].exit = 1;
}