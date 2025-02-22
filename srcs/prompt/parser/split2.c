/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:43:16 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/03 16:43:16 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	in_cote(char *str, int j)
{
	int	i;
	int	one;
	int	two;

	i = -1;
	one = 0;
	two = 0;
	while (++i <= j)
	{
		if (str[i] == '\'')
			one++;
		if (str[i] == '"')
			two++;
	}
	if (one % 2 == 0 && two % 2 == 0)
		return (0);
	return (1);
}

static int	is_charset(char *charset, char ch)
{
	int	i;

	i = -1;
	while (charset[++i])
	{
		if (charset[i] == ch)
			return (1);
	}
	return (0);
}

static int	strlen_char(char *charset, char *str, int j)
{
	int	i;

	i = 0;
	while (str[i + j])
	{
		if (!in_cote(str, i + j) && is_charset(charset, str[i + j]))
			return (i);
		i++;
	}
	return (i);
}

static int	ft_nbr_word(char *str, char *charset)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (!in_cote(str, i) && (!is_charset(charset, str[i]))
			&& (is_charset(charset, str[i + 1]) || str[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

char	**ft_split2(char *s, char *c)
{
	char	**str_final;
	int		i;
	int		i_m;

	i = 0;
	i_m = 0;

	str_final = malloc((ft_nbr_word(s, c) + 1) * sizeof(char *));
	if (str_final == NULL)
		return (NULL);
	while (s[i])
	{
		if (in_cote(s, i) || !is_charset(c, s[i]))
		{
			str_final[i_m] = malloc((strlen_char(c, s, i) + 1) * sizeof(char));
			if (str_final[i_m] == NULL)
				return (ft_free_tab((void *)str_final, ft_strslen(str_final)),
					NULL);
			ft_strlcpy(str_final[i_m++], &s[i], strlen_char(c, s, i) + 1);
			i += strlen_char(c, s, i);
		}
		else
			i++;
	}
	str_final[i_m] = 0;
	return (str_final);
}
