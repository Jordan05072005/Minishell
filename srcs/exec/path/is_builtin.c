/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:18:25 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/04 16:56:31 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(const char *str)
{
	if (ft_strncmp("cd", str, 3) == 0)
		return (1);
	if (ft_strncmp("pwd", str, 4) == 0)
		return (1);
	if (ft_strncmp("env", str, 4) == 0)
		return (1);
	return (0);
}
