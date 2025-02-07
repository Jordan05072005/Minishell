/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:01:55 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/04 13:01:55 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_pwd(char **arg)
{
	// char	buf[4096];
	char	*cwd;

	if (ft_strslen(arg) != 1)
		return (1);
	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	ft_del(cwd);
	return (0);
}