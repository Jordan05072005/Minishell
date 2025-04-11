/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:00:15 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/11 08:17:15 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	redirect_subshell_fd(t_icmd *cmds, int nb_cmds, int child, int *ret)
{
	char	*sub;

	*ret = 0;
	sub = ft_strtrim(cmds[child].args[0], " \t");
	printf("sub is [%s]\n", sub);
	if (sub[0] == '(' && sub[ft_strlen(sub) - 1] == ')')
	{
		*ret = 1;
		if (cmds[child].fd_out > 1)
			close(cmds[child].fd_out);
		cmds[child].fd_out = open("/dev/null", O_WRONLY);
	}
	ft_del(sub);
	set_io_cp(child, nb_cmds, cmds);
	close_fd(cmds, nb_cmds, child);
}

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
		redirect_subshell_fd(cmds, nb_cmds, child, &ret);
		sub = ft_strdup(cmds[child].args[0]);
		clean_pars(data()->pars);
		data()->pars = NULL;
		clear_tree(data()->ast);
		clean_icmds();
		data()->ast = get_ast(sub);
		ft_del(sub);
		run_ast(data()->ast);
		if (ret == 0)
			ret = ft_atoi(ft_getimp("?"));
		if (data()->exit != -1)
			ret = data()->exit;
		clean_data();
		exit(ret);
	}
}
