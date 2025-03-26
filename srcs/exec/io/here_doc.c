/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:02:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/26 13:39:51 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*custom_gnl(int fd)
{
	char	*buffer;
	ssize_t	bytes_read;
	size_t	i;
	size_t	buff_size;

	buff_size = 1024;
	buffer = malloc(buff_size * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (1)
	{
		bytes_read = read(fd, &buffer[i], buff_size);
		if (bytes_read <= 0)
		{
			if (i == 0 || bytes_read < 0)
				return (free(buffer), NULL);
			continue ;
		}
		if (buffer[bytes_read + i - 1] == '\n')
			break ;
		i += bytes_read;
		if (i >= buff_size - 1) 
		{
			buff_size += buff_size;
			buffer = ft_realloc(buffer, buff_size * sizeof(char));
			if (!buffer)
				return (NULL);
		}
	}
	return (buffer);
}

void sigint_here_doc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	(void)(clean_data() + clean_icmds());
	exit(0);
}

t_list	*get_text(t_icmd cmd)
{
	char	*temp;
	t_list	*input_list;

	signal(SIGINT, sigint_here_doc);
	signal(SIGQUIT, SIG_IGN);
	input_list = NULL;
	while (1)
	{
		ft_putstr_fd("> ", 1);
		temp = custom_gnl(0);
		if (!temp)
		{
			ft_perror(-1, ft_strsjoin((const char *[]){"\nmini: warning: he\
re-document delimited by EOF (wanted `", cmd.here_doc, "')", NULL}), 0);
			break;
		}
		if (ft_strncmp(temp, cmd.here_doc, ft_strlen(cmd.here_doc)) == 0
			&& temp[ft_strlen(cmd.here_doc)] == '\n')
		{
			free(temp);
			break;
		}
		add_link(&input_list, temp);
	}
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

void here_doc(t_icmd cmd)
{
	int		p_fd[2];
	pid_t	f_id;
	t_list	*input;

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
		input = get_text(cmd);
		write_text(p_fd, input);
		close(p_fd[1]);
		return ((void)(clean_data() + clean_icmds()), exit(0));
	}
	close(p_fd[1]);
	dup2(p_fd[0], 0);
}
