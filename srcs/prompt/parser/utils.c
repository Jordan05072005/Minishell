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
	char	quote;

	if (!str || (!ft_strchr(str, '"') && !ft_strchr(str, '\'')))
		return (str);
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
	str_f = malloc(sizeof(char) * len + 1);
	i = -1;
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
<<<<<<< HEAD
=======
	// printf("len : e%de\n", len);
>>>>>>> 3239bdb8ce7b48256bb3ab5d380eb0341a81e0e1
	return (ft_del2((void **)&str), str_f);
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
