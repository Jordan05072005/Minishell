/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:04:33 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/09 11:04:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//penser a clear l'history

char	*ft_readline(void)
{
	char	*prompt;
	char	*temp;
	char	*line;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(0))
		prompt = NULL;
	else
		prompt = get_prompt();
	if (isatty(0))
		temp = readline(prompt);
	else
		temp = readline(prompt);
	ft_del(prompt);
	line = ft_strtrim(temp, " \t\r\n\f\v");
	ft_del(temp);
	signal(SIGINT, any);
	return (line);
}

void	create_env(t_data **d, char **env, char **av, int ac)
{
	(void)av;
	(void)ac;
	(*d)->loc = NULL;
	(*d)->env = NULL;
	(*d)->imp = NULL;
	while (*env)
	{
		ft_lstadd_back(&(*d)->env, ft_lstnew(ft_strdup(*env)));
		env++;
	}
	init_imp(&((*d)->imp));
}

void	init_mini(t_data *d, int ac, char **av, char **env)
{
	char	*temp;

	if (av[1])
		ft_color(av);
	if (isatty(1))
		print_welcome();
	d->pars = NULL;
	d->exit = -1;
	create_env(&d, env, av, ac);
	init_io(d);
	printf("\e[?2004l");
	update_shlvl();
	temp = ft_getenv("PWD");
	if (!temp)
		add_link(&(data()->env), ft_strdup(ft_getimp("PWD")));
	temp = ft_getenv("_");
	if (!temp)
		add_link(&(data()->env), ft_strdup("_=/usr/bin/env"));
}

char	*update_history(char *line)
{
	char	*last;
	t_list	*before;
	t_list	*bin;

	last = ft_getimp("BEFORE");
	if (!last)
		add_history(line);
	else if (ft_strncmp(last, line, ft_strlen(last) + 1))
		add_history(line);
	before = ft_getimp_struct("BEFORE", &bin);
	if (!before)
		ft_perror(1, ft_strdup("mini: Internal error: missing struct."),
			clean_icmds() + clean_data());
	ft_del(before->content);
	before->content = ft_strsjoin((char *[]){"BEFORE=", line, NULL});
	if (!before->content)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_icmds() + clean_data());
	return (ft_getimp("BEFORE"));
}

int	main(int ac, char **av, char **env)
{
	t_data	*d;
	char	*line;
	char	*before;
	int		ret;

	before = NULL;
	d = data();
	init_mini(d, ac, av, env);
	line = ft_readline();
	while (line && d->exit == -1)
	{
		before = update_history(line);
		(void)before;
		data()->ast = get_ast(line);
		(ft_del(line), write(1, "\033[0m", 5));
		run_ast(data()->ast);
		clear_tree(data()->ast);
		data()->ast = NULL;
		if (d->exit == -1)
			line = ft_readline();
	}
	ret = d->exit;
	if (d->exit == -1)
		ret = ft_atoi(ft_getimp("?"));
	return (ft_putendl_fd("\001\033[0m\002" "exit", 1), clean_data(), ret);
}
		// printf("Exit is : %d\n", ft_atoi(ft_getimp("?")));
