/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:50:18 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/07 13:34:50 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_readline(void)
{
	char	*prompt;
	char	*temp;
	char	*line;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(0))
		prompt = NULL;
	else
		prompt = get_prompt();
	if (isatty(0))
		temp = readline(prompt);
	else
		temp = readline(prompt);
	ft_del(prompt);
	line = ft_strtrim(temp, " \t\r\n\f\v");
	ft_del(temp);
	signal(SIGINT, any);
	return (line);
}
