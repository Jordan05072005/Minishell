/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_define.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:43:40 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/26 16:00:22 by hle-hena         ###   ########.fr       */
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

void	define_imp(t_icmd *cmds, int child, int i, char *var_name)
{
	t_list	*temp;
	t_list	*var;

	var = ft_getimp_struct(var_name, &temp);
	if (var == ft_getimp_struct("PWD", &temp))
		return ;
	if (var)
	{
		ft_del(var->content);
		var->content = ft_strdup(cmds[child].args[i]);
	}
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
	cmds[child].exit = 0;
	define_vars(cmds, child, -1);
}
