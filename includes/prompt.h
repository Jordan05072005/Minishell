/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:05 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 13:00:05 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/* -------------------------------------------------------------------------- */
/*                  parser.c                                                  */
/* -------------------------------------------------------------------------- */
int	parseur(char *line, t_data **d);

/* -------------------------------------------------------------------------- */
/*                  prompt.c                                                  */
/* -------------------------------------------------------------------------- */
void	new_prompt(int signum);
char	*get_prompt();
void	any(int signum);

/* -------------------------------------------------------------------------- */
/*                  utils.c                                                   */
/* -------------------------------------------------------------------------- */
int	in_str(char c, char *sep, int y);
int	nbr_sep(char **str, char *sep);
int	is_var(char *str);
void	free_tpars(t_pars **pars);
void	shift_left(char **str, size_t i);

/* -------------------------------------------------------------------------- */
/*                  utils_lst.c                                               */
/* -------------------------------------------------------------------------- */
t_pars *init_struct_pars(char **split, int nbr);
void	init_struct_cmd(t_pars **pars, int nbr, char **arg);
char	**ft_split2(char *s, char *c);

#endif