/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:24:43 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/26 15:58:23 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_cmd(t_icmd *cmds, int child, int nb_cmds)
{
	if (nb_cmds > 1 || (!is_builtin(cmds[child].args[0])
		&& !cmds[child].define))
	{
		cmds[child].pid = fork();
		if (cmds[child].pid == -1)
			ft_perror(1, ft_strdup("mini: Internal error: process."),
				clean_data() + clean_icmds());
		if (cmds[child].pid == 0 && !is_builtin(cmds[child].args[0]))
			exec_child(cmds, nb_cmds, child);
		else if (cmds[child].pid == 0 && cmds[child].define)
			exec_define(cmds, nb_cmds, child);
		else if (cmds[child].pid == 0)
			exec_builtin(cmds, nb_cmds, child);
	}
	else if (cmds[child].define)
		exec_define(cmds, nb_cmds, child);
	else
		exec_builtin(cmds, nb_cmds, child);
}

void	set_exit_val(int ret_val)
{
	t_list	*pipe;
	t_list	*bin;
	char	*temp;

	pipe = ft_getimp_struct("?", &bin);
	temp = ft_itoa(ret_val);
	if (!temp)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds());
	ft_del(pipe->content);
	pipe->content = ft_strsjoin((const char *[]){"?=", temp, NULL});
	ft_del(temp);
	if (!pipe->content)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds());
}

int	exec(int nb_cmds, t_cmd *input)
{
	t_icmd	*cmds;
	int		child;
	int		ret_value;

	write(1, "\033[0m", 5);
	if (!input)
		return (set_exit_val(0), 0);
	else if (!input->args)
		return (set_exit_val(0), 0);
	else if (!input->args[0])
		return (set_exit_val(0), 0);
	if (data()->saved_tty != -1)
		dup2(data()->saved_out, 1);
	cmds = init_icmds(input, nb_cmds);
	child = -1;
	while (++child < nb_cmds)
		exec_cmd(cmds, child, nb_cmds);
	ret_value = exec_parent(cmds, nb_cmds);
	if (data()->saved_tty != -1)
		dup2(data()->saved_tty, 1);
	set_exit_val(ret_value);
	return (ret_value);
}
