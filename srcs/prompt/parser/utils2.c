/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:33:00 by jguaglio          #+#    #+#             */
/*   Updated: 2025/03/15 13:33:00 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*nextc(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i][0] != ' ' && str[i][0] != '\t')
			return (str[i]);
	}
	return (NULL);
}

int	farg(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i][0]))
			return (i + 1);
	}
	return (i);
}

