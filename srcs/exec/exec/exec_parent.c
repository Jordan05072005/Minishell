/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:32:34 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/09 14:00:57 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_exit(int status)
{
	int	sig;
	int	exit_code;

	exit_code = -1;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(2, "\n", 1);
		else if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (sig == SIGSEGV)
			write(2, "Segmentation fault (core dumped)\n", 33);
		else if (sig == SIGABRT)
			write(2, "Aborted (core dumped)\n", 22);
		else if (sig == SIGBUS)
			write(2, "Bus error (core dumped)\n", 24);
		else if (sig == SIGFPE)
			write(2, "Floating point exception\n", 25);
		exit_code = 128 + sig;
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}

int	exec_parent(t_icmd *cmds, int nb_cmds)
{
	pid_t	wpid;
	int		child;
	int		status;
	int		exit_code;

	close_fd(cmds, nb_cmds, -2);
	child = nb_cmds;
	exit_code = -1;
	while (--child >= 0)
	{
		if (cmds[child].type != 1 && cmds[child].type != 4 && nb_cmds == 1)
		{
			if (child == nb_cmds - 1)
				exit_code = cmds[child].rv;
			break ;
		}
		wpid = waitpid(cmds[child].pid, &status, 0);
		if (wpid == cmds[nb_cmds - 1].pid)
			exit_code = check_exit(status);
	}
	return (clean_icmds(), exit_code);
}
