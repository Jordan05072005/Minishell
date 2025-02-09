/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:18:25 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/10 12:29:18 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_builtin(const char *str)
{
	if (ft_strncmp("cd", str, 3) == 0)
		return (1);
	if (ft_strncmp("pwd", str, 4) == 0)
		return (1);
	if (ft_strncmp("env", str, 4) == 0)
		return (1);
	if (ft_strncmp("exit", str, 5) == 0)
		return (1);
	if (ft_strncmp("export", str, 7) == 0)
		return (1);
	if (ft_strncmp("unset", str, 6) == 0)
		return (1);
	if (ft_strncmp("echo", str, 5) == 0)
		return (1);
	if (ft_strncmp("color", str, 6) == 0)
		return (1);
	return (0);
}
