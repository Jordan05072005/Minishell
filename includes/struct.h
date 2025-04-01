	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:05:10 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/21 14:25:44 by hle-hena         ###   ########.fr       */
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
// typedef struct s_info_cmd
// {
// 	int		fd_in;
// 	int		fd_out;
// 	char	*here_doc;
// 	char	*path;
// 	char	**args;
// 	int		define;
// 	int		pipe[2];
// 	int		pid;
// 	int		exit;
// }	t_icmd;

typedef struct s_info_cmd
{
	char	*here_doc;
	char	*path;
	char	**args;
	int		fd_in;
	int		fd_out;
	int		type;
	int		pipe[2];
	int		pid;
	int		rv;
}	t_icmd;

typedef struct s_cmd
{
	t_list	*in;
	t_list	*out;
	char	**args;
	t_list	*here_doc;
	int		append;
	int		subshell;
	char	**split;
}	t_cmd;

typedef struct s_bt
{
	void		*content;
	int			value;
	struct s_bt	*parent;
	struct s_bt	*left;
	struct s_bt	*right;
}	t_bt;

/* -------------------------------------------------------------------------- */
/*                  prompt.h                                                  */
/* -------------------------------------------------------------------------- */
typedef struct s_pars
{
	int		n_sep;
	int		pipe;
	t_list	*in;
	t_list	*out;
	char	*cmd;
	t_list	*limiter;
	char	*append;
	char	sep;
	char	*line;
	char	*before;
	t_cmd *exe;
}		t_pars;

/* -------------------------------------------------------------------------- */
/*                  data.h                                                  */
/* -------------------------------------------------------------------------- */
typedef struct s_data
{
	t_bt	*ast;
	t_icmd	*cmds;
	t_list	*imp;
	t_list	*env;
	t_list	*loc;
	int		nb_cmds;
	int		saved_out;
	int		saved_tty;
}	t_data;

#endif