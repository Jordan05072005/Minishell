/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:14:49 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/27 17:22:27 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	str_isnum(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	if (*str)
		return (0);
	return (1);
}

int	ft_exit(char **av)
{
	int	exit_val;

	ft_printf("exit\n");
	if (!av[1])
		exit_val = ft_atoi(ft_getimp("?"));
	else
	{
		exit_val = 2;
		if (!str_isnum(av[1]))
			ft_perror(-1, ft_strsjoin((const char *[]){"mini: exit: ", av[1], "\
: numeric argument required.", NULL}), 0);
		else if (ft_strslen(av) > 2)
			return (ft_perror(-1, ft_strdup("mini: exit: Too many arguments."),
					0), 1);
		else
			exit_val = ft_atoi(av[1]) % 256;
	}
	clean_data();
	clean_icmds();
	exit(exit_val);
}