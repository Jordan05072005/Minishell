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

//29 is the number of char for color
char	*get_prompt()
{
	char	*str;
	char	*prompt;
	char	*curseur;
	char	*len;

	prompt = ft_strdup("\033[0;32m");
	str = ft_getenv("LOGNAME");
	prompt = ft_strjoin_free(prompt, str);
	prompt = ft_strjoin_free(prompt, "@");
	str = ft_getenv("USER");
	prompt = ft_strjoin_free(prompt, str);
	prompt = ft_strjoin_free(prompt, "\033[0;0m:\033[0;34m");
	str = ft_getenv("PWD");
	prompt = ft_strjoin_free(prompt, str);
	if (strncmp(ft_getenv("USER"), "root", 4) == 0)
		prompt = ft_strjoin_free(prompt, "\033[0;0m# \033[G");
	else
		prompt = ft_strjoin_free(prompt, "\033[0;0m$ \033[G");
	len = ft_itoa(ft_strlen(prompt) - 29);
	curseur = ft_strjoin("\033[", len);
	curseur = ft_strjoin(curseur, "C");
	prompt = ft_strjoin_free(prompt, curseur);
	return (free(len), free(curseur), prompt);
}
