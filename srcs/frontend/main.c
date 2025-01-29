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
int	main()
{
	char	*line;
	char	*before;
	char	*prompt;
	t_cmd	*cmd;

	before = NULL;
	signal(SIGINT, new_prompt);
	prompt = get_prompt();
	line = readline(prompt);
	while (line)
	{
		if (!before || ft_strncmp(before, line, ft_strlen(before)) != 0)
			add_history(line);
		if (before)
			free(before);
		before = line;
		cmd = parseur(line);
		(void)cmd;
		//envoyer au back (cmd)
		line = readline(prompt);
	}
	free(prompt);
	return (1);
}
