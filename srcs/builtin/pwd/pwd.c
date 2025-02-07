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
	char	*cwd;

	if (ft_strslen(arg) != 1)
		return (1);
	cwd = ft_getimp("PWD");
	ft_printf("%s\n", cwd);
	return (0);
}