/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:05:10 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/07 12:54:56 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/* -------------------------------------------------------------------------- */
/*                  exec.h                                                    */
/* -------------------------------------------------------------------------- */
// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

/* -------------------------------------------------------------------------- */
/*                  exec.h                                                    */
/* -------------------------------------------------------------------------- */
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

typedef struct s_cmd
{
	char	*in;
	char	*out;
	char	**args;
	char	*here_doc;
	int		append;
	char	**split;
}	t_cmd;

/* -------------------------------------------------------------------------- */
/*                  prompt.h                                                  */
/* -------------------------------------------------------------------------- */
typedef struct s_pars
{
	int		n_sep;
	int		pipe;
	char	*in;
	char	*out;
	char	*cmd;
	char	*limiter;
	char	*append;
	char	sep;
	char	**split;
	char	*line;
	t_cmd *exe;
}		t_pars;

/* -------------------------------------------------------------------------- */
/*                  data.h                                                  */
/* -------------------------------------------------------------------------- */
typedef struct s_data
{
	t_pars	*cmd;
	t_list	*imp;
	t_list	*env;
	t_list	*loc;
}	t_data;

#endif