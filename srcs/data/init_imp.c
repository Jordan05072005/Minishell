/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:55:19 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/19 09:22:59 by hle-hena         ###   ########.fr       */
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
	if (!home && ft_strncmp(user, "unknown", 8))
		home = ft_strjoin("/home/", user);
	else if (!home)
		home = ft_strdup("/");
	pwd = getenv("PWD");
	if (!pwd)
		pwd = getcwd(NULL, 0);
	ft_lstadd_back(imp, ft_lstnew(ft_strjoin("USER=", user)));
	ft_lstadd_back(imp, ft_lstnew(ft_strjoin("HOME=", home)));
	ft_lstadd_back(imp, ft_lstnew(ft_strjoin("PWD=", pwd)));
}

void	init_io(t_data *d)
{
	int	tty;

	d->saved_out = -1;
	d->saved_tty = -1;
	if (!isatty(1))
	{
		d->saved_out = dup(1);
		tty = open("/dev/tty", O_WRONLY);
		if (tty == -1)
			ft_perror(1, ft_strdup("mini: error opening a terminal.\n"),
					clean_data());
		d->saved_tty = dup(tty);
		if (d->saved_tty == -1)
			ft_perror(1, ft_strdup("mini: error redirecting stdout to a termina\
l.\n"), clean_data());
		if (dup2(tty, 1) == -1)
			ft_perror(1, ft_strdup("mini: error redirecting stdout to a termina\
l.\n"), clean_data());
	}
}