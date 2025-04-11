/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_icmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:12:47 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/10 17:20:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_read(char *filename)
{
	if (access(filename, F_OK) == -1)
		return (ft_perror(-1, ft_strsjoin((char *[]){"mini: ", filename, ": No \
such file or directory.", NULL}), 0), 1);
	if (access(filename, R_OK) == -1)
		return (ft_perror(-1, ft_strsjoin((char *[]){"mini: ", filename, ": Per\
mission denied.", NULL}), 0), 1);
	return (0);
}

int	check_dir(char *filename)
{
	struct stat	st;
	char		*dir;
	char		*slash;

	slash = ft_strrchr(filename, '/');
	if (!slash)
		dir = ft_strdup(".");
	else if (slash == filename)
		dir = ft_strdup("/");
	else
		dir = ft_substr(filename, 0, slash - filename);
	if (access(dir, X_OK) == -1)
		return (ft_del(dir), ft_perror(-1, ft_strsjoin((char *[]){"mini: \
", filename, ": Permission denied.", NULL}), 0), 1);
	if (access(dir, F_OK) == -1)
		return (ft_del(dir), ft_perror(-1, ft_strsjoin((char *[]){"mini: \
", filename, ": No such file or directory.", NULL}), 0), 1);
	if (stat(filename, &st) == 0 && S_ISDIR(st.st_mode))
		return (ft_del(dir), ft_perror(-1, ft_strsjoin((char *[]){"mini: \
", filename, ": Is a directory.", NULL}), 0), 1);
	if (access(dir, W_OK) == -1 && access(filename, W_OK) == -1)
		return (ft_del(dir), ft_perror(-1, ft_strsjoin((char *[]){"mini: \
", filename, ": Permission denied.", NULL}), 0), 1);
	ft_del(dir);
	return (0);
}

int	check_write(char *filename, int append)
{
	if (check_dir(filename))
		return (-1);
	if (access(filename, F_OK) == -1)
	{
		if (append)
			return (open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
		else
			return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	}
	if (access(filename, W_OK) == -1)
		return (ft_perror(-1, ft_strsjoin((char *[]){"mini: ", filename, ": Per\
mission denied.", NULL}), 0), -1);
	if (append)
		return (open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

void	open_all_files(t_icmd *cmd, t_cmd input)
{
	while (input.in)
	{
		cmd->fd_in = open(input.in->content, O_RDONLY, 0777);
		if (check_read(input.in->content))
			break ;
		if (input.in->next && cmd->fd_in > 0)
			close(cmd->fd_in);
		input.in = input.in->next;
	}
	if (input.here_doc)
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		cmd->fd_in = here_doc(*cmd);
	}
	while (input.out)
	{
		cmd->fd_out = check_write(input.out->content, input.append);
		if (cmd->fd_out)
			break ;
		if (input.out->next && cmd->fd_out > 1)
			close(cmd->fd_out);
		input.out = input.out->next;
	}
}

void	init_icmd(t_icmd *cmd, t_cmd input)
{
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->here_doc = input.here_doc;
	open_all_files(cmd, input);
	if (input.subshell)
		cmd->type = 4;
	else if (!input.args)
		cmd->type = 0;
	else if (!input.args[0])
		cmd->type = 0;
	else if (is_builtin(input.args[0]))
		cmd->type = 2;
	else if (is_define(input.args[0]) == 1 || is_define(input.args[0]) == 2)
		cmd->type = 3;
	else
		cmd->type = 1;
	cmd->rv = -1;
	cmd->args = input.args;
	cmd->path = get_path(input, cmd);
	cmd->pid = -1;
	if (pipe(cmd->pipe) == -1)
		return (ft_perror(1, ft_strdup("mini: Internal error: pipe."),
				clean_icmds() + clean_data()));
}
