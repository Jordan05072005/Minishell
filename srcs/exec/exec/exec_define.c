/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_define.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:35:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/28 15:36:42 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_define(char *str)
{
	if (!str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while ((*str != '=' && *str != '+') && *str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	if (!*str)
		return (3);
	if (*str == '+' && *(str + 1) == '=')
		return (2);
	if (*str == '+' && *(str + 1) != '=')
		return (0);
	return (1);
}

void	define_vars(t_icmd *cmds, int child, int i)
{
	t_list	*var;
	char	*var_name;

	while (cmds[child].args[++i])
	{
		var_name = get_var_name(cmds[child].args[i]);
		var = ft_getenv_struct(var_name, &(t_list *){0});
		if (!var)
			var = ft_getloc_struct(var_name, &(t_list *){0});
		ft_del(var_name);
		if (var && is_define(cmds[child].args[i]) == 1)
		{
			ft_del(var->content);
			var->content = create_var(cmds[child].args[i]);
			continue ;
		}
		if (var)
		{
			var_name = create_join_var(cmds[child].args[i], var);
			ft_del(var->content);
			var->content = var_name;
			continue ;
		}
		add_link(&(data()->loc), create_var(cmds[child].args[i]));
	}
}

void	exec_define(t_icmd *cmds, int nb_cmds, int child)
{
	int	i;
	int	is_def;

	i = -1;
	is_def = is_define(cmds[child].args[++i]);
	while (is_def == 1 || is_def == 2)
		is_def = is_define(cmds[child].args[++i]);
	if (cmds[child].args[i])
		return (define2child(cmds, nb_cmds, child, i));
	cmds[child].rv = 0;
	define_vars(cmds, child, -1);
}
