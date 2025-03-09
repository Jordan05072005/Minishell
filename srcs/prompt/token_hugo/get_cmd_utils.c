/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:56:16 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/09 16:56:52 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_lstcpy_one(t_list *lst, int size)
{
	char	*dest;
	int		i;
	
	if (size == 0)
		return (NULL);
	dest = malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = -1;
	while(++i < size)
	{
		while (((char *)lst->content)[0] == 0 && lst->next)
			lst = lst->next;
		dest[i] = ((char *)lst->content)[0];
		lst = lst->next;
	}
	dest[size] = 0;
	return (dest);
}

char	*ft_lstjoin(t_list *lst)
{
	int		size;
	t_list	*temp;

	temp = lst;
	size = 0;
	while (temp)
	{
		while (((char *)(temp->content))[0] == 0 && temp->next)
			temp = temp->next;
		size++;
		temp = temp->next;
	}
	return (ft_lstcpy_one(lst, size));
}

t_list	*get_var_new(char *line, int *forward)
{
	t_list	*head;
	t_list	*var;
	char	*var_name;
	char	*value;
	int		i;

	i = 1;
	head = NULL;
	var = NULL;
	if (ft_isdigit(line[i]))
	{
		add_link(&head, &line[0]);
		add_link(&head, &line[1]);
		return (*forward += 2, head);
	}
	add_link(&var, &line[i++]);
	while (ft_isalnum(line[i]) || line[i] == '_')
		add_link(&var, &line[i++]);
	var_name = ft_lstjoin(var);
	if (!var_name)
		return (*forward += i, ft_lstnew(&line[0]));
	value = ft_getenv(var_name);
	if (!value)
		value = ft_getloc(var_name);
	if (!value)
		return (*forward += i, NULL);
	while (*value)
		add_link(&head, &(*value++));
	return (*forward += i, head);
}

t_list	*get_quote(char *line, int quote_type, int *forward)
{
	t_list	*head;
	int		i;

	i = 0;
	head = NULL;
	while (line[i] != quote_type && line[i])
	{
		if (quote_type == 39)
			add_link(&head, &line[i++]);
		else if (line[i] == '$')
				ft_lstadd_back(&head, get_var_new(&line[i], &i));
		else
			add_link(&head, &line[i++]);
	}
	add_link(&head, "");
	*forward += i + 1 + (line[i] != 0);
	if (line[i] != quote_type)
		return (NULL);//This is an error to print.
	return (head);
}

char	*get_sep(char *line, int *forward)
{
	char	*res;
	int		i;

	i = 1;
	if ((line[0] == line[1]) || (line[0] == '<' && line[0] == '>'))
	{
		res = ft_substr(line, 0, 2);
		i = 2;	
	}
	else
		res = ft_substr(line, 0, 1);
	while (ft_isspace(line[i]))
		i++;
	*forward += i;
	return (res);
}

int	get_change(char *line, int *forward, t_list **head)
{
	t_list	*temp;
	int		rv;

	rv = 0;
	temp = NULL;
	if (line[0] == 39 || line[0] == 34)
	{
		temp = get_quote(&line[1], line[0], forward);
		if (!temp)
			rv = 1;
	}
	else if (line[0] == '$')
	{
		temp = get_var_new(&line[0], forward);
		if (!temp)
			rv = 1;
	}
	if (rv)
		return (ft_lstclear(&temp, ft_del), rv);
	if (!rv && !temp)
		return (rv);
	else
		return (ft_lstadd_back(head, temp), rv);
}

char	*get_next_block(char *line, int *forward, int *err)
{
	t_list	*head;
	int		i;

	i = 0;
	head = NULL;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (*forward += i, *err = 0, NULL);
	if (ft_strchr("><|&", line[i]))
		return (*err = 0, get_sep(line, forward));
	while (line[i] && !ft_isspace(line[i]))
	{
		if (get_change(&line[i], &i, &head))
			return (*forward += i, *err = 1, NULL);
		if ((ft_strchr("><|& ", line[i])))
			break ;
		add_link(&head, &line[i]);
		i++;
	}
	while (ft_isspace(line[i]))
		i++;
	*forward += i;
	return (*err = 0, ft_lstjoin(head));
}

