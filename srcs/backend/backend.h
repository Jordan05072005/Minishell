/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:27:19 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/27 17:55:20 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKEND_H
# define BACKEND_H

# include "../../libft.h"

typdef struct s_cmd
{
	char	*in;
	char	*out;
	char	**args;
	int		here_doc;
	int		append;
}	t_cmd;

typdef	struct	s_info_cmd
{
	int		fd_in;
	int		fd_out;
	int		here_doc;
	int		append_out;
	char	*cmd_path;
	char	**cmd_arg;
	int		pipe_fd[2];
}	t_icmd;

#endif