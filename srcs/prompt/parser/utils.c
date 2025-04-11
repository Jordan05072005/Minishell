/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:26:53 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/06 13:26:53 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

size_t	ft_strchri(char *str, char *c)
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

int	ft_strdelquotes2(char *str)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	quote = 0;
	len = 0;
	while (str[++i])
	{
		if (str[i] == quote)
			quote = 0;
		else if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else
			len++;
	}
	return (len);
}

char	*ft_strdelquotes(char *str)
{
	char	quote;
	int		len;
	int		i;
	char	*str_f;

	if (!str || (!ft_strchr(str, '"') && !ft_strchr(str, '\'')))
		return (ft_strdup(str));
	len = ft_strdelquotes2(str);
	str_f = malloc(sizeof(char) * len + 1);
	i = -1;
	quote = 0;
	len = 0;
	while (str[++i])
	{
		if (str[i] == quote)
			quote = 0;
		else if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else
			str_f[len++] = str[i];
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
