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

void	write_str(char *str, t_icmd *cmd, int i)
{
	size_t	j;
	char	*sub_str;
	int		oct;

	j = 0;
	oct = 0;
	while (j < ft_strlen(str))
	{
		if (str[j] == '$')
		{
			sub_str = ft_substr(str, j + 1, ft_strchr_index(&str[j], ' ') - 1);
			if (ft_getloc(sub_str))
				oct += ft_putstr_fd(ft_getloc(sub_str), cmd->fd_out);
			else if (ft_getenv(sub_str))
				oct += ft_putstr_fd(ft_getenv(sub_str), cmd->fd_out);
			j += (ft_strlen(sub_str) + 1);
			ft_del(sub_str);
		}
		else
			oct += ft_putchar_fd(str[j++], cmd->fd_out);
	}
	if (cmd->args[i + 1] && oct != 0)
		write(1, " ", 1);
}

int	ft_echo(t_icmd *cmd)
{
	int		i;
	char	*str;

	// if (cmd->fd_in) // ?
	// 	return (0);
	i = cmd->args[1] && !ft_strncmp(cmd->args[1], "-n", 3);
	while (cmd->args[1] && cmd->args[++i])
	{
		if (ft_strchr(cmd->args[i], '"') < ft_strchr(cmd->args[i], '\'') || !ft_strchr(cmd->args[i], '\''))
			str = ft_strdelchar(cmd->args[i], '"');
		else if (ft_strchr(cmd->args[i], '"') > ft_strchr(cmd->args[i], '\'') || !ft_strchr(cmd->args[i], '"'))
			str = ft_strdelchar(cmd->args[i], '\'');
		write_str(str, cmd, i);
		ft_del(str);
	}
	if (!cmd->args[1] || ft_strncmp(cmd->args[1], "-n", 3) != 0)
		write(cmd->fd_out, "\n", 1);
	return (1);
}