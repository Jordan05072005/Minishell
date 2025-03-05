/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:43:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/27 10:19:10 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	export_non_existant(char *str)
{
	char	*temp;
	t_list	*var;

	if (!ft_strchr(str, '='))
		return (0);
	temp = create_var(str);
	if (!temp)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds()), 0);
	var = ft_lstnew(temp);
	if (!var)
		return (ft_del(temp), ft_perror(1, ft_strdup("mini: Internal error: mal\
loc."), clean_data() + clean_icmds()), 0);
	return (ft_lstadd_back(&(data()->env), var), 0);
}

int	export_existant(t_list *loc, char *str, char *name)
{
	char	*temp;
	t_list	*var;

	if (ft_strchr(str, '='))
	{
		ft_lstremove_if(&(data()->loc), is_env, ft_del, name);
		temp = create_var(str);
	}
	else
	{
		temp = ft_strdup(loc->content);
		ft_lstremove_if(&(data()->loc), is_env, ft_del, name);
	}
	ft_del(name);
	if (!temp)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds()), 1);
	var = ft_lstnew(temp);
	if (!var)
		return (ft_del(temp), ft_perror(1, ft_strdup("mini: Internal error: mal\
loc."), clean_data() + clean_icmds()), 1);
	ft_lstadd_back(&(data()->env), var);
	return (0);
}

int	export_update(t_list *env, char *str)
{
	ft_del(env->content);
	env->content = create_var(str);
	if (!env->content)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
				clean_data() + clean_icmds()), 1);
	return (0);
}

int	export_var(char *str)
{
	char	*name;
	char	*temp;
	t_list	*var;
	t_list	*bin;

	name = get_var_name(str);
	if (!is_define(name))
	{
		temp = ft_strsjoin((const char *[]){"bash: export: `", str, "': not a \
valid identifier.", NULL});
		return (ft_del(name), ft_perror(-1, temp, 0), 1);
	}
	var = ft_getenv_struct(name, &bin);
	if (var)
		return (ft_del(name), export_update(var, str));
	var = ft_getloc_struct(name, &bin);
	if (!var)
		return (ft_del(name), export_non_existant(str));
	return (export_existant(var, str, name));
}
