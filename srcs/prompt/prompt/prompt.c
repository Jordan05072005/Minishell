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

#include "mini.h"

void	any(int signum)
{
	(void)signum;
	return ;
}

void	new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*user;
	char	*path;

	user = ft_getimp("USER");
	path = ft_getloc("PWD");
	if (!path)
		path = ft_getenv("PWD");
	if (!path)
		path = ft_getimp("PWD");
	if (strncmp(user, "root", 4) == 0)
		prompt = ft_strsjoin((const char *[]){get_color(0), user, get_color(2), "@", get_color(1), path, get_color(2), "$ \001\033[0;0m\002", get_color(3), NULL});
	else
		prompt = ft_strsjoin((const char *[]){get_color(0), user, get_color(2), "@", get_color(1), path, get_color(2), "$ \001\033[0;0m\002", get_color(3), NULL});
	return (prompt);
}
