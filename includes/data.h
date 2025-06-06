/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:03:47 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/19 13:51:28 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

int		clean_data(void);
int		clean_pars(t_pars *cmd);
int		clean_env(void);
t_data	*data(void);
void	add_link(t_list **imp, char *content);
void	init_imp(t_list **imp);
void	init_io(t_data *d);
t_list	*ft_getimp_struct(const char *str, t_list **placeholder);
char	*ft_getimp(const char *str);
t_list	*ft_getenv_struct(const char *str, t_list **placeholder);
char	*ft_getenv(const char *str);
t_list	*ft_getloc_struct(const char *str, t_list **placeholder);
char	*ft_getloc(const char *str);
char	**env2env(t_list *env);
int		is_env(void *str, void *to_find);
void	update_shlvl(void);
char	*get_var_name(char *str);
char	*get_var_body(char *str);
char	*create_var(char *str);
char	*create_join_var(char *str, t_list *var);

#endif