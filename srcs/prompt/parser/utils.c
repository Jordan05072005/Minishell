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

#include "mini.h"

int	ft_strchri(char *str, char *c)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (c[++j])
		{
			if (str[i] == c[j])
				return (i);
		}
	}
	return (i);
}

int	nbr_sep(char **str, char *sep)
{
	int	i;
	int	compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], sep, ft_strlen(sep)) == 0)
			compt++;
		i++;
	}
	return (compt + 1);
}

int	strlenchar(char *str, char c)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == c)
			len++;
	}
	return (len);
}

char	*ft_strdelquotes(char *str)
{
	int	i;
	int	len;
	char	*str_f;
	int		verr;

	if (!str)
		return (str);
	len = ft_strlen(str) - (strlenchar(str, '"') + strlenchar(str, '\'')) + 1;
	str_f = malloc(sizeof(char) * (len + 1));
	if (!str_f)
		return (NULL);
	i = -1;
	len = 0;
	verr = 0;
	while (str[++i])
	{
		if (!(str[i] == '"' || (str[i] == '\'' && verr % 2 == 0)))
			str_f[len++] = str[i];
		if (str[i] == '"')
			verr++;
	}
	str_f[len] = 0;
	return (str_f);
}

void	shift_left(char **str, size_t i)
{
	if (i > ft_strslen(str) || !str)
		return ;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}	
