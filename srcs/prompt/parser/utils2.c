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
		if (!ft_isspace(str[i][0]))
			return (str[i]);
	}
	return (NULL);
}

char	*beforec(char **str, int i)
{
	while (str[--i])
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
int	farg2(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
			return (i + 1);
	}
	return (i);
}

int	*quotes(char c, int *tab)
{
	if (!tab)
	{
		tab = malloc(sizeof(int) * 3);
		tab[0] = 0;
		tab[1] = 0;
		tab[2] = 0;
	}
	if (c == '"')
		tab[1]++;
	else if (c == '\'')
		tab[1]++;
	if ((tab[0] + tab[1]) % 2 == 0)
		tab[2] = 1;
	else
		tab[2] = 0;
	return (tab);
}

