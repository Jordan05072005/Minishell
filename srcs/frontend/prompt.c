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
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_exit()
{
	ft_printf("exit\n");
}
char	*get_prompt()
{
	char	*str;
	char	*prompt;

	prompt = ft_strdup("\033[0;32m");
	str = getenv("LOGNAME");
	prompt = ft_strjoin_free(prompt, str);
	prompt = ft_strjoin_free(prompt, "@");
	str = getenv("USER");
	prompt = ft_strjoin_free(prompt, str);
	prompt = ft_strjoin_free(prompt, "\033[0;0m:\033[0;34m");
	str = getenv("PWD");
	prompt = ft_strjoin_free(prompt, str);
	if (strncmp(getenv("USER"), "root", 4) == 0)
		prompt = ft_strjoin_free(prompt, "\033[0;0m# ");
	else
		prompt = ft_strjoin_free(prompt, "\033[0;0m$ ");
	return (prompt);
}