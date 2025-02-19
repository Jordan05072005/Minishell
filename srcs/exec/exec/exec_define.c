/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_define.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:43:40 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/19 17:31:00 by hle-hena         ###   ########.fr       */
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
		return (0);
	return (1);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	while (str[i] != '=')
		i++;
	dest = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(dest, str, i + 1);
	return (dest);
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
	t_list	*temp;
	t_list	*var;
	char	*var_name;

	i = -1;
	while (cmds[child].args[++i])
	{
		var_name = get_var_name(cmds[child].args[i]);
		var = ft_getenv_struct(var_name, &temp);
		if (!var)
			var = ft_getloc_struct(var_name, &temp);
		if (var)
		{
			ft_del(var->content);
			var->content = ft_strdup(cmds[child].args[i]);
			continue ;
		}
		ft_lstadd_back(&data()->loc, ft_lstnew(ft_strdup(cmds[child].args[i])));
		ft_del(var_name);
	}
}

//run through every args, and if it contains anything that makes the arg not a
//define of a local var, consider this arg as the start of the command, and act
//like it is one.
void	exec_define(t_icmd *cmds, int nb_cmds, int child)
{
	int	i;

	i = 0;
	while (is_define(cmds[child].args[i]))
		i++;
	if (cmds[child].args[i])
		return (define2child(cmds, nb_cmds, child, i));
	define_vars(cmds, child);
}
