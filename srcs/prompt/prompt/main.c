/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:09 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/27 16:33:09 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//penser a clear l'history

void remove_escape_sequences(char *str)
{
    char *read_ptr = str;
    char *write_ptr = str;

    while (*read_ptr) {
        // Check for escape sequences
        if (*read_ptr == '\033') {
            // Skip the escape sequence
            while (*read_ptr && *read_ptr != 'm') {
                read_ptr++;
            }
            if (*read_ptr) {
                read_ptr++;  // Skip the 'm' at the end of the sequence
            }
        } else {
            // Copy character if not part of an escape sequence
            *write_ptr++ = *read_ptr++;
        }
    }
    *write_ptr = '\0';  // Null-terminate the modified string
}

char	*ft_readline(void)
{
	char	*prompt;
	char	*line;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(0))
		prompt = NULL;
	else
		prompt = get_prompt();
	line = readline(prompt);
	// if (!prompt)
	// 	printf("\n\nPrompt : %s\nWhat readline is reading : %s\n\n", prompt, line);
	ft_del(prompt);
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
	if (isatty(1))
		print_welcome();
	create_env(&d, env, av, ac);
	init_io(d);
	printf("\e[?2004l");
	update_shlvl();
}

int	main(int ac, char **av, char **env)
{
	t_data	*d;
	char	*line;
	char	*before;

	before = NULL;
	d = data();
	init_mini(d, ac, av, env);
	line = ft_readline();
	while (line)
	{
		if (!before || ft_strncmp(before, line, ft_strlen(before) + 1) != 0)
			add_history(line);
		free(before);
		before = ft_strdup(line);
		if (!parseur(line, &d))
		{
			d->cmd->before = before; //Hugo free;
			exec(d->cmd->pipe, d->cmd->exe);
			clean_pars(0);
		}
		line = ft_readline();
	}
	ft_del(before);
	return (ft_exit(), 0);
}
