/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:43:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/27 18:02:03 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	export_non_existant(char *str)
{
	if (ft_strchr(str, '='))
		add_link(&(data()->env), create_var(str));
	else
		add_link(&data()->env, ft_strdup(str));
	return (0);
}

int	export_existant(t_list *loc, char *str, char *name, int type)
{
	char	*content;

	if (type == 1 || type == 3)
	{
		if (ft_strchr(str, '='))
		{
			ft_lstremove_if(&(data()->loc), is_env, ft_del, name);
			content = create_var(str);
		}
		else
		{
			content = ft_strdup(loc->content);
			ft_lstremove_if(&(data()->loc), is_env, ft_del, name);
		}
		return (ft_del(name), add_link(&(data()->env), content), 0);
	}
	content = create_join_var(str, loc);
	add_link(&(data()->env), content);
	return (0);
}

int	export_update(t_list *env, char *str, int type)
{
	char	*content;

	if (type == 1)
	{
		ft_del(env->content);
		env->content = create_var(str);
		if (!env->content)
			return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
					clean_data() + clean_icmds()), 1);
		return (0);
	}
	content = create_join_var(str, env);
	ft_del(env->content);
	env->content = content;
	return (0);
}

int	export_var(char *str)
{
	char	*name;
	char	*temp;
	t_list	*var;
	t_list	*bin;
	int		type;

	type = is_define(str);
	name = get_var_name(str);
	if (!type)
	{
		temp = ft_strsjoin((char *[]){"bash: export: `", str, "': not a \
valid identifier.", NULL});
		return (ft_del(name), ft_perror(-1, temp, 0), 1);
	}
	var = ft_getenv_struct(name, &bin);
	if (var)
		return (ft_del(name), export_update(var, str, type));
	var = ft_getloc_struct(name, &bin);
	if (!var)
		return (ft_del(name), export_non_existant(str));
	return (export_existant(var, str, name, type));
}
