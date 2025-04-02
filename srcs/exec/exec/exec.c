/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:49:11 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/02 11:00:56 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_cmd(t_icmd *cmds, int child, int nb_cmds)
{
	int	i = -1;
	if (cmds[child].args)
	{
		if (cmds->type == 4)
			printf("Subshell : ");
		else
			printf("Nooormal : ");
		while (cmds[child].args[++i])
			printf("[%s] - ", cmds[child].args[i]);
		printf("[%s]\n", cmds[child].args[i]);
	}
	if (cmds[child].type == 4)
		subshell(cmds[child]);
	if (cmds[child].type == 1 || nb_cmds > 1)
	{
		cmds[child].pid = fork();
		if (cmds[child].pid == -1)
			ft_perror(1, ft_strdup("mini: Internal error: process."),
				clean_data() + clean_icmds());
		if (cmds[child].type == 1 && cmds[child].pid == 0)
			exec_child(cmds, nb_cmds, child);
		else if (cmds[child].type == 2 && cmds[child].pid == 0)
			exec_builtin(cmds, nb_cmds, child);
		else if (cmds[child].type == 3 && cmds[child].pid == 0)
			exec_define(cmds, nb_cmds, child);
	}
	else if (cmds[child].type == 2)
		exec_define(cmds, nb_cmds, child);
	else if (cmds[child].type == 3)
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
			clean_data());
	ft_del(pipe->content);
	pipe->content = ft_strsjoin((char *[]){"?=", temp, NULL});
	ft_del(temp);
	if (!pipe->content)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data());
}


int	exec(int nb_cmds, t_cmd *input)
{
	t_icmd	*cmds;
	int		child;
	int		ret_value;

	write(1, "\033[0m", 5);
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