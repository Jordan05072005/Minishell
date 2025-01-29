/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:10:32 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/28 18:10:32 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*get_prompt()
{
	char	*str;
	char	*prompt;

	prompt = ft_strdup("");
	str = getenv("LOGNAME");
	prompt = ft_strjoin2(prompt, str);
	prompt = ft_strjoin2(prompt, "@");
	str = getenv("NAME");
	prompt = ft_strjoin2(prompt, str);
	prompt = ft_strjoin2(prompt, ":");
	str = getenv("PWD");
	prompt = ft_strjoin2(prompt, str);
	if (strncmp(getenv("NAME"), "root", 4) == 0)
		prompt = ft_strjoin2(prompt, "# ");
	else
		prompt = ft_strjoin2(prompt, "$ ");
	return (prompt);
}