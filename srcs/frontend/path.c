/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:54:37 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/27 19:54:37 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//vas : variable environnemnt système

/*char	*get_prompt()
{
	char	*str;
	char	*prompt;

	//prompt = ft_strdup("\033[1;32m");
	prompt = ft_strdup("\r\033[1;35m");
	str = getenv("LOGNAME");
	prompt = ft_strjoin2(prompt, str);
	prompt = ft_strjoin2(prompt, "@");
	str = getenv("NAME");
	prompt = ft_strjoin2(prompt, str);
	prompt = ft_strjoin2(prompt, "\033[1;37m:\033[1;34m");
	str = getenv("PWD");
	prompt = ft_strjoin2(prompt, str);
	if (strncmp(getenv("NAME"), "root", 4) == 0)
		prompt = ft_strjoin2(prompt, "\033[1;37m#");
	else
		prompt = ft_strjoin2(prompt, "\033[1;37m$ ");
	return (ft_strdup("hello"));
}*/

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