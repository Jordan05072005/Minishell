/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:58:25 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/22 21:58:25 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*find_var(char *name, int lock)
{
	if (ft_getenv(name))
		return (ft_getenv(name));
	else if (ft_getloc(name))
		return (ft_getloc(name));
	else if (ft_getimp(name) && lock)
		return (ft_getimp(name));
	return (NULL);
}

char	end_var(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
	}
	return (i);
}

char	*get_var2(char *var, char *str, int quote, int *i)
{
	char	*temp;

	if (str[*i] == '$' && str[*i + 1]
		&& ft_isdigit(str[*i + 1]) && quote % 2 == 0)
		(*i)++;
	else if (str[*i] == '$' && str[*i + 1] == '?' && quote % 2 == 0)
	{
		(*i)++;
		var = ft_strjoin_free(var, ft_getimp("?"));
	}
	else if (str[*i] == '$' && str[*i + 1]
		&& (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
		&& quote % 2 == 0)
	{
		temp = ft_substr(str, *i, end_var(&str[*i]));
		(*i) += (ft_strlen(temp) - 1);
		var = ft_strjoin_free(var, find_var(&temp[1], 0));
		ft_del2((void **)&temp);
	}
	else if (str[*i] == '$')
		var = ft_strjoin_free(var, "$");
	return (var);
}

int	nbr_quote(char *str)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (str[++i] && str[i] != '$')
	{
		if (str[i] == '\'')
			quote++;
	}
	return (quote);
}

char	*get_var(char *str)
{
	int		i;
	char	*var;
	char	*temp;
	int		quote;

	i = -1;
	quote = 0;
	var = ft_strdup("");
	if (str[0] == '~' && (!str[1] || str[1] == '/'))
	{
		i++;
		var = ft_strjoin_free(var, find_var("HOME", 1));
	}
	while (++i < (int)ft_strlen(str))
	{
		quote = nbr_quote(&str[i]);
		temp = ft_substr(&str[i], 0, ft_strchri(&str[i], "$"));
		i += ft_strlen(temp);
		var = ft_strjoin_free(var, temp);
		ft_del2((void **)&temp);
		var = get_var2(var, str, quote, &i);
	}
	return (var);
}
