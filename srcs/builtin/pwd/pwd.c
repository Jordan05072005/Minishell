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

#include "exec.h"

int	ft_pwd(char **arg)
{
	char	buf[4096];

	if (ft_strstrlen(arg) > 1)
		return (1);
	getcwd(buf, 4096);
	ft_printf("%s", buf);
	return (0);
}