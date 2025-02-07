/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:55:19 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/07 13:30:46 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	init_imp(t_list **imp)
{
	char	*user;
	char	*home;
	char	*pwd;

	user = getenv("USER");
	if (!user)
		user = ft_strdup("unknown");
	home = getenv("HOME");
	if (!home && !ft_strncmp(user, "unknown", 8))
		home = ft_strjoin("/home/", user);
	else if (!home && ft_strncmp(user, "unknown", 8))
		home = ft_strdup("/");
	pwd = getenv("PWD");
	if (!pwd)
		pwd = ft_strdup(home);
	ft_lstadd_back(imp, ft_lstnew(ft_strjoin("USER=", user)));
	ft_lstadd_back(imp, ft_lstnew(ft_strjoin("HOME=", home)));
	ft_lstadd_back(imp, ft_lstnew(ft_strjoin("PWD=", pwd)));
}
