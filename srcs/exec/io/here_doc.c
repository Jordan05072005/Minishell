/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:02:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/07 10:46:35 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	**get_input_lst(void)
{
	static t_list	*input = NULL;

	return (&input);
}

t_list	**get_text(char *limiter)
{
	char	*temp;
	t_list	**input_list;

	signal(SIGINT, sigint_here_doc);
	input_list = get_input_lst();
	while (1)
	{
		ft_putstr_fd("> ", 1);
		temp = custom_gnl();
		if (!temp)
		{
			ft_perror(-1, ft_strsjoin((char *[]){"\nmini: warning: he\
re-document delimited by end-of-file (wanted `", limiter, "')", NULL}), 0);
			break ;
		}
		if (ft_strncmp(temp, limiter, ft_strlen(limiter)) == 0
			&& temp[ft_strlen(limiter)] == '\n')
		{
			free(temp);
			break ;
		}
		add_link(input_list, temp);
	}
	write(1, "---\n", 4);
	return (input_list);
}

void	write_text(int p_fd[2], t_list *input)
{
	t_list	*temp;

	temp = input;
	while (input)
	{
		ft_putstr_fd(input->content, p_fd[1]);
		input = input->next;
	}
	ft_lstclear(&temp, ft_del);
}

void	get_here_doc(t_icmd cmd)
{
	int		p_fd[2];
	pid_t	f_id;
	t_list	**input;

	input = NULL;
	if (pipe(p_fd) == -1)
		ft_perror(1, ft_strdup("mini: Internal error: pipe."),
			clean_icmds() + clean_data());
	f_id = fork();
	if (f_id == -1)
		ft_perror(1, ft_strdup("mini: Internal error: process."),
			clean_icmds() + clean_data());
	if (f_id == 0)
	{
		close(p_fd[0]);
		ft_lstclear(get_input_lst(), ft_del);
		input = get_text((char *)cmd.here_doc->content);
		write_text(p_fd, *input);
		close(p_fd[1]);
		return ((void)(clean_data() + clean_icmds()), exit(0));
	}
	waitpid(f_id, NULL, 0);
	close(p_fd[1]);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
}

void	here_doc(t_icmd cmd)
{
	int	saved;

	saved = dup(0);
	while (cmd.here_doc)
	{
		get_here_doc(cmd);
		cmd.here_doc = cmd.here_doc->next;
		if (cmd.here_doc)
			dup2(saved, 0);
	}
}
