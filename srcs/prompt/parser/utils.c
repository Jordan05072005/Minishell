/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 02:50:33 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/28 02:50:33 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_str(char c, char *sep, int y)
{
	int	i;

	i = -1;
	if (y != -1)
	{
		if (sep[y] == c)
			return (1);
		return (0);
	}
	while (sep[++i])
	{
		if (sep[i] == c)
			return (1);
	}
	return (0);
}