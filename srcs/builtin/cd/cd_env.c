/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:06:05 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/13 19:56:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	update_pwd(t_list *pwd, t_list *oldpwd, int *present, char *curpath)
{
	if (pwd)
	{
		if (oldpwd)
		{
			ft_del(oldpwd->content);
			oldpwd->content = ft_strjoin("OLDPWD=", pwd->content + 4);
		}
		else if (!oldpwd && *present)
		{
			ft_lstadd_back(&data()->env,
				ft_lstnew(ft_strjoin("OLDPWD=", pwd->content + 4)));
			*present = 0;
		}
		else
			ft_lstadd_back(&data()->loc,
				ft_lstnew(ft_strjoin("OLDPWD=", pwd->content + 4)));
		ft_del(pwd->content);
		pwd->content = ft_strjoin("PWD=", curpath);
	}
	else
	{
		ft_lstadd_back(&data()->loc, ft_lstnew(ft_strjoin("PWD=", curpath)));
		if (oldpwd)
			*present = 1;
	}
}

void	update_env(char *curpath)
{
	static int	present = 0;
	t_list		*temp;
	t_list		*oldpwd;
	t_list		*pwd;

	pwd = ft_getimp_struct("PWD", &temp);
	ft_del(pwd->content);
	pwd->content = ft_strjoin("PWD=", curpath);
	pwd = ft_getenv_struct("PWD", &temp);
	if (!pwd)
		pwd = ft_getloc_struct("PWD", &temp);
	oldpwd = ft_getenv_struct("OLDPWD", &temp);
	if (!oldpwd && !present)
		oldpwd = ft_getloc_struct("OLDPWD", &temp);
	update_pwd(pwd, oldpwd, &present, curpath);
	if (present)
	{
		ft_lstremove_if(&(data()->loc), is_env, ft_del, "OLDPWD");
		ft_lstremove_if(&(data()->env), is_env, ft_del, "OLDPWD");
	}
}
