/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:27:19 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 11:11:30 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKEND_H
# define BACKEND_H

# include "../../libft.h"

typedef struct s_cmd
{
	char	*in;
	char	*out;
	char	**args;
	char	*here_doc;
	int		append;
}	t_cmd;

typedef	struct	s_info_cmd
{
	int		fd_in;
	int		fd_out;
	char	*here_doc;
	char	*path;
	char	**args;
	int		pipe[2];
	int		pid;
}	t_icmd;

#endif