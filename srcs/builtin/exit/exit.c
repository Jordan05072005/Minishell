/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:14:49 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/19 16:05:09 by hle-hena         ###   ########.fr       */
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

int	is_overflow(char *arg)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	count;
	char	*min;

	if (!arg)
		return (1);
	i = 0 + (arg[0] == '-' || arg[0] == '+');
	j = 1;
	count = 0;
	min = "-9223372036854775808";
	len = ft_strlen(min);
	while (arg[i] && min[j] && ft_isdigit(arg[i]))
	{
		while (j == 1 && arg[i] == '0')
			i ++;
		if (!arg[i])
			break ;
		if (arg[i] > (min[j] - 1 * (j == len - 1) * (arg[0] != '-')))
			count ++;
		i++;
		j++;
	}
	return (arg[i] || (j == len && count) || !arg[0]);
}

int	ft_exit(char **av)
{
	int	exit_val;

	ft_printf("\001\033[0m\002" "exit\n");
	if (!av[1])
		exit_val = ft_atoi(ft_getimp("?"));
	else
	{
		exit_val = 2;
		if (!str_isnum(av[1]) || is_overflow(av[1]))
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
