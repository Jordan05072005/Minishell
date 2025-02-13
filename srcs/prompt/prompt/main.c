/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:09 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/27 16:33:09 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//penser a clear l'history

char	*ft_readline(void)
{
	char	*prompt;
	char	*line;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	prompt = get_prompt();
	line = readline(prompt);
	signal(SIGINT, any);
	free(prompt);
	return (line);
}

void	create_env(t_data **d, char **env, char **av, int ac)
{
	(void)av;
	(void)ac;
	
	(*d)->loc = NULL;
	(*d)->env = NULL;
	(*d)->imp = NULL;
	while (*env)
	{
		ft_lstadd_back(&(*d)->env, ft_lstnew(ft_strdup(*env)));
		env++;
	}
	init_imp(&((*d)->imp));
}

int	main(int ac, char **av, char **env)
{
	char	*before;
	t_data	*d;
	char	*line;

	before = NULL;
	d = data();
	create_env(&d, env, av, ac);
	line = ft_readline();
	while (line)
	{
		if (!before || ft_strncmp(before, line, ft_strlen(before) + 1) != 0)
			add_history(line);
		free(before);
		before = ft_strdup(line);
		if (!parseur(line, &d))
		{
			d->cmd->before = before; //Hugo free;
			exec(d->cmd->pipe, d->cmd->exe);
			clean_pars(0);
		}
		line = ft_readline();
	}
	ft_del(before);
	return (ft_exit(), 0);
}
