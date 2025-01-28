/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:05:13 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/27 16:05:13 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	in_str(char c, char *sep, int y)
{
	int	i;

	i = -1;
	if (y != -1)
	{
		if (sep[y] == c)
			return (1);
		return (0);
	}
	while (sep[++i])
	{
		if (sep[i] == c)
			return (1);
	}
	return (0);
}


int	fill_struct(t_cmd **cmd, char **arg, int *n_arg, int max)
{
	int	i;

	i = 0;
	while (*n_arg < max && !(ft_strlen(arg[*n_arg]) == 1 && in_str(arg[*n_arg][0], "|", -1)))
	{
		printf("i : %d ; %d %d %d %d\n", i, i > 1 , (*n_arg) + 1 < max , ft_strlen(arg[*n_arg]) == 2 ,ft_strncmp(arg[*n_arg], ">>", 2) == 0);
		if (i == 0)
		{
			if (ft_strlen(arg[*n_arg]) == 1 && ft_strncmp(arg[*n_arg], "<", 1) == 0 && max > 2)
			{
				(*cmd)->in = arg[++(*n_arg)];
				i++;
			}
			else
				(*cmd)->cmd = arg[*n_arg];
		}
		else if ((*cmd)->cmd != NULL && in_str('-', arg[*n_arg], 0))
			(*cmd)->cmd = ft_strjoin((*cmd)->cmd, arg[*n_arg]);
		else if ((*n_arg) + 1 < max && ft_strlen(arg[*n_arg]) == 2 && ft_strncmp(arg[*n_arg], ">>", 2) == 0)
			(*cmd)->out = arg[(*n_arg) + 1];
		else if ((*n_arg) + 1 < max && ft_strlen(arg[*n_arg]) == 2 && ft_strncmp(arg[(*n_arg)], "<<", 2) == 0)
			(*cmd)->limiter = arg[(*n_arg) + 1];
		else
			return (-1);
		i++;
		(*n_arg)++;
		}
		if (*n_arg == max)
			return (0);
		return (1);
}


t_cmd *init_struct(char **split)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));

	cmd->split = split;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->cmd = NULL;
	cmd->here_doc = 0;
	cmd->limiter = NULL;
	cmd->append = 0;
	cmd->sep = 0;
	cmd->next= NULL;
	return (cmd);
}

void	reader(t_cmd *cmd)
{
	//printfcmd->split = split;
	if (cmd->cmd)
		printf("cmd : %s\n",cmd->cmd);
	if (cmd->in)
		printf("in : %s\n",cmd->in);
	if (cmd->out)
		printf("out :%s \n",cmd->out);
	if (cmd->limiter)
		printf("limiter : %s\n",cmd->limiter);
	if (cmd->sep != 0)
		printf("sep :%c\n",cmd->sep);
	if (cmd->next)
		reader(cmd->next);
}

int	parseur(char *line)
{
	char	**arg;
	t_cmd *cmd;
	t_cmd	*temp;
	int		n_arg;
	int	err;

	err = 1;
	arg = ft_split(line, ' ');
	cmd = init_struct(arg);
	n_arg = 0;
	temp = cmd;
	while (err == 1)
	{
		err = fill_struct(&temp, arg, &n_arg, ft_strstrlen(arg));
		if (err == 1)
		{
			temp = temp->next;
			temp = init_struct(arg);
		}
	}
	reader(cmd);
	return (0);
}