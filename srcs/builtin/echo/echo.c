/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:33:22 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/05 19:33:22 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_strdelchar(const char *str, char del)
{
	int	i;
	int	len;
	char	*str_f;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != del)
			len++;
	}
	str_f = malloc(sizeof(char) * (len + 1));
	if (!str_f)
		return (NULL);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != del)
			str_f[len++] = str[i];
	}
	str_f[len] = 0;
	return (str_f);
}

char	*ft_delcot(char *str, int i)
{
	char	*str2;

	if (!ft_strchr(str, '\'') && ft_strchr(str, '"'))
		str2 = ft_strdelchar(str, '"');
	else if (ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		str2 = ft_strdelchar(str, '\'');
	else if (ft_strchr(str, '"') < ft_strchr(str, '\'') || !ft_strchr(str, '\''))
		str2 = ft_strdelchar(str, '"');
	else
		str2 = ft_strdelchar(str, '\'');
	if (i)
		ft_del(str);
	return (str2);
}

char	ft_strchr_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (i);
}

void	write_str(char *str, t_icmd *cmd, int etat, int i)
{
	size_t	j;
	int		oct;

	j = -1;
	oct = 0;
	if (!etat)
		return ;
	while (++j < ft_strlen(str))
			oct += ft_putchar_fd(str[j], cmd->fd_out);
	if (cmd->args[i + 1] && oct != 0)
				write(1, " ", 1);
}

int	ft_echo(t_icmd *cmd)
{
	int		i;
	char	*str;
	int		etat;
	char	*trunc;

	etat = 0;
	i = 0;
	//printf("%s", cmd->args[1]);
	while (cmd->args[1] && cmd->args[++i])
	{
		str = ft_delcot(cmd->args[i], 0);
		trunc = ft_strtrim(str, "n");
		if (!etat && !(!ft_strncmp(str, "-n", 2) && !ft_strncmp(trunc, "-", 2)))
			etat = 1;
		write_str(str, cmd, etat, i);
		ft_del(str);
		ft_del(trunc);
	}
	trunc = ft_strtrim(cmd->args[1], "n");
	if (!cmd->args[1] || !(!ft_strncmp(cmd->args[1], "-n", 2) && !ft_strncmp(trunc, "-", 2)))
		write(cmd->fd_out, "\n", 1);
	return (ft_del(trunc), 1);
}