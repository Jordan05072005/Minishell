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
	while (*str != '=' && *str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	if (!*str)
		return (2);
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

void	define_vars(t_icmd *cmds, int child)
{
	int		i;
	t_list	*var;
	char	*var_name;

	i = -1;
	while (cmds[child].args[++i])
	{
		var_name = get_var_name(cmds[child].args[i]);
		var = ft_getenv_struct(var_name, &(t_list *){0});
		if (!var)
			var = ft_getloc_struct(var_name, &(t_list *){0});
		if (var)
		{
			ft_del(var->content);
			var->content = create_var(cmds[child].args[i]);
			continue ;
		}
		ft_del(var_name);
		var_name = create_var(cmds[child].args[i]);
		var = ft_lstnew(var_name);
		if (!var)
			return (ft_del(var_name), ft_perror(1, ft_strdup("mini: Internal er\
ror: malloc."), clean_data() + clean_icmds()));
		ft_lstadd_back(&data()->loc, var);
	}
}

//run through every args, and if it contains anything that makes the arg not a
//define of a local var, consider this arg as the start of the command, and act
//like it is one.
void	exec_define(t_icmd *cmds, int nb_cmds, int child)
{
	//Current version doesnt strip the char.
	int	i;

	i = 0;
	while (is_define(cmds[child].args[i]) == 1)
		i++;
	if (cmds[child].args[i])
		return (define2child(cmds, nb_cmds, child, i));
	cmds[child].exit = 0;
	define_vars(cmds, child);
}
