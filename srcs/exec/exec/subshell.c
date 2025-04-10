/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:00:15 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/10 21:20:25 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_subshell(t_icmd *cmds, int child, int nb_cmds)
{
	char	*sub;
	int		ret;

	cmds[child].pid = fork();
	if (cmds[child].pid == -1)
		ft_perror(1, ft_strdup("mini: Internal error: process."),
			clean_data() + clean_icmds());
	if (cmds[child].pid == 0)
	{
		set_io_cp(child, nb_cmds, cmds);
		close_fd(cmds, nb_cmds, child);
		sub = ft_strdup(cmds[child].args[0]);
		clean_pars(data()->pars);
		data()->pars = NULL;
		clear_tree(data()->ast);
		clean_icmds();
		data()->ast = get_ast(sub);
		ft_del(sub);
		run_ast(data()->ast);
		ret = ft_atoi(ft_getimp("?"));
		if (data()->exit != -1)
			ret = data()->exit;
		clean_data();
		exit(ret);
	}
}
