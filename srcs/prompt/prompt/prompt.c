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
	char	*temp1;
	char	*temp2;
	char	*user;
	char	*path;

	user = ft_getimp("USER");
	path = ft_getimp("PWD");
	temp1 = ft_strjoin(get_color(0), user);
	temp2 = ft_strjoin(get_color(2), "@");
	prompt = ft_strjoin(temp1, temp2);
	ft_del(temp1);
	ft_del(temp2);
	temp2 = ft_strjoin(get_color(1), path);
	temp1 = ft_strjoin(temp2, get_color(2));
	ft_del(temp2);
	if (strncmp(user, "root", 4) == 0)
		temp2 = ft_strjoin(temp1, "#\001\033[0;0m\002 ");
	else
		temp2 = ft_strjoin(temp1, "$\001\033[0;0m\002 ");
	ft_del(temp1);
	temp1 = prompt;
	prompt = ft_strjoin(temp1, temp2);
	return (ft_del(temp1), ft_del(temp2), prompt);
}
