/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:05:10 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/09 14:33:54 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <dirent.h>

typedef struct s_info_cmd
{
	t_list	*here_doc;
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

typedef struct s_wildcard
{
	DIR		*dir;
	char	*path_temp;
	char	*after;
	char	*before;
	int		val;
	int		i;
}	t_wildcard;

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
	t_cmd	*exe;
}		t_pars;

/* -------------------------------------------------------------------------- */
/*                  data.h                                                  */
/* -------------------------------------------------------------------------- */
typedef struct s_data
{
	t_bt	*ast;
	t_icmd	*cmds;
	t_pars	*pars;
	t_list	*imp;
	t_list	*env;
	t_list	*loc;
	int		nb_cmds;
	int		saved_out;
	int		saved_tty;
}	t_data;

#endif