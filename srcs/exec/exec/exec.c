/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:24:43 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/07 09:54:07 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	exec(int nb_cmds, t_cmd *input)
{
	t_icmd	*cmds;
	int		child;

	if (!input || !input->args)
		return (0);
	cmds = init_icmds(input, nb_cmds);
	child = -1;
	while (++child < nb_cmds)
	{
		if (!is_builtin(cmds[child].args[0]))
		{
			cmds[child].pid = fork();
			if (cmds[child].pid == -1)
				ft_perror(1, clean_icmds(cmds, nb_cmds), "A subprocess was not \
started.");
			if (cmds[child].pid == 0)
				exec_child(cmds, nb_cmds, child);
		}
		else
			exec_builtin(cmds, nb_cmds, child);
	}
	return (exec_parent(cmds, nb_cmds));
}