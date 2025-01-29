/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:27:19 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/29 14:18:21 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKEND_H
# define BACKEND_H

# include "../../libft/libft.h"
# include <wait.h>
# include <fcntl.h>
// # include <stdio.h>

typedef struct s_cmd
{
	char	*in;
	char	*out;
	char	**args;
	char	*here_doc;
	int		append;
}	t_cmd;

typedef struct s_info_cmd
{
	int		fd_in;
	int		fd_out;
	char	*here_doc;
	char	*path;
	char	**args;
	int		pipe[2];
	int		pid;
	int		exit;
}	t_icmd;

t_icmd	*init_icmds(t_cmd *input, int nb_cmds);
void	zero_out(t_icmd *cmds, int nb_cmds);
void	init_icmd(t_icmd *cmd, t_cmd input, int nb_cmds);
char	*get_path(t_cmd cmd, t_icmd *cmds, int nb_cmds);
void	exec_child(t_icmd *cmds, int nb_cmds, int child, char **env);
void	set_io_cp(int child, int nb_cmds, t_icmd *cmds);
void	here_doc(t_icmd cmd, t_icmd *cmds, int nb_cmds);
void	close_fd(t_icmd *cmds, int nb_cmds);
int		exec_parent(t_icmd *cmds, int nb_cmds);
int		clean_icmds(t_icmd *cmds, int nb_cmds);
int		is_builtin(const char *str);
void	exec_builtin(t_icmd *cmds, int nb_cmds, int child, char **env);

#endif