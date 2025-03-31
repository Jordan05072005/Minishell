/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_icmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:12:47 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/28 16:47:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_read(char *filename)
{
	char	*mess;

	if (access(filename, F_OK) == -1)
	{
		mess = ft_strsjoin((char *[]){"mini: ", filename, ": No such file or di\
rectory.", NULL});
		ft_putendl_fd(mess, 2);
		ft_del(mess);
		return (0);
	}
	if (access(filename, R_OK) == -1)
	{
		mess = ft_strsjoin((char *[]){"mini: ", filename, ": Permission denied.\
", NULL});
		ft_putendl_fd(mess, 2);
		ft_del(mess);
		return (0);
	}
	return (1);
}

int	check_write(char *filename)
{
	char	*mess;

	if (access(filename, F_OK) == -1)
		return (1);
	if (access(filename, W_OK) == -1)
	{
		mess = ft_strsjoin((char *[]){"mini: ", filename, ": Permission denied.\
", NULL});
		ft_putendl_fd(mess, 2);
		ft_del(mess);
		return (0);
	}
	return (1);
}

void	open_all_files(t_icmd *cmd, t_cmd input)
{
	while (input.in)
	{
		if (check_read(input.in->content) || !input.in->next)
			cmd->fd_in = open(input.in->content, O_RDONLY, 0777);
		if (input.in->next && cmd->fd_in >= 0)
			close(cmd->fd_in);
		input.in = input.in->next;
	}
	while (input.out)
	{
		if (check_write(input.out->content) || !input.out->next)
		{
			if (input.append)
				cmd->fd_out = open(input.out->content,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				cmd->fd_out = open(input.out->content,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (input.out->next && cmd->fd_out >= 0)
			close(cmd->fd_out);
		input.out = input.out->next;
	}
}

void	init_icmd(t_icmd *cmd, t_cmd input)
{
	open_all_files(cmd, input);
	if (!input.args)
		cmd->type = 0;
	else if (is_builtin(input.args[0]))
		cmd->type = 2;
	else if (is_define(input.args[1]))
		cmd->type = 3;
	else
		cmd->type = 1;
	cmd->rv = -1;
	cmd->here_doc = input.here_doc;
	cmd->args = input.args;
	cmd->path = get_path(input, cmd);
	if (!cmd->path)
	cmd->pid = -1;
	if (pipe(cmd->pipe) == -1)
		return (ft_perror(1, ft_strdup("mini: Internal error: pipe."),
			clean_icmds() + clean_data()));
}
