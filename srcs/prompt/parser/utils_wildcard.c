/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:01:07 by jguaglio          #+#    #+#             */
/*   Updated: 2025/03/04 00:01:07 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	accessv(char *start, char *file, char *end)
{
	char	*path;
	char	*ende;

	if (strchr(end, '*'))
		ende = ft_strdup("");
	else
		ende = ft_strdup(end);
	path = ft_strsjoin((const char *[]){start, file, ende, NULL});
	if (access(path, F_OK) == -1)
		return (ft_del(path), ft_del(ende), 1);
	return (ft_del(path), ft_del(ende), 0);
}

// int	valid(char *str)
// {
// 	char	*path;
// 	int	i;

// 	i = 0;
// 	while (i < strlen(str))
// 	{
// 		path = ft_strjoin(path, ft_substr(&str[i], 0, ft_strchri(str, "*")));
// 		if (strchr(&str[i], '/'))
			
// 		i = ft_strchri(str, "*") + 1;
// 		if (access(path, F_OK) == -1)
// 			return (1);
// 	}
// }