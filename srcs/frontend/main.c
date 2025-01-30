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

#include "minishell.h"

//penser a clear l'history
int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*before;
	char	*prompt;
	t_pars	*cmd;	

	before = NULL;
	(void)av;
	(void)ac;
	signal(SIGINT, new_prompt);
	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
	while (line)
	{
		if (!before || ft_strncmp(before, line, ft_strlen(line)) != 0 || ft_strncmp(before, line, ft_strlen(before)) != 0)
			add_history(line);
		before = line;
		cmd = parseur(line);
		if (cmd != NULL)
		{
			exec(cmd->pipe, cmd->exe, env, cmd);
			clean_temp(cmd);
		}
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
	}
	ft_exit();
	return (1);
}
