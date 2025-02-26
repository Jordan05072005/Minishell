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
	int		etat;
	char	*trunc;

	etat = 0;
	i = 0;
	//printf("%s", cmd->args[1]);
	while (cmd->args[1] && cmd->args[++i])
	{
		trunc = ft_strtrim(cmd->args[i], "n");
		if (!etat && !(!ft_strncmp(cmd->args[i], "-n", 2) && !ft_strncmp(trunc, "-", 2)))
			etat = 1;
		write_str(cmd->args[i], cmd, etat, i);
		ft_del(trunc);
	}
	trunc = ft_strtrim(cmd->args[1], "n");
	if (!cmd->args[1] || !(!ft_strncmp(cmd->args[1], "-n", 2) && !ft_strncmp(trunc, "-", 2)))
		write(cmd->fd_out, "\n", 1);
	return (ft_del(trunc), 0);
}