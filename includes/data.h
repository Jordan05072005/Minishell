/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:03:47 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/18 16:31:40 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

int		clean_data(void);
int		clean_pars(int full);
int		clean_env(void);
t_data	*data(void);
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

#endif