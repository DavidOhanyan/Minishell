/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:45:51 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/22 19:11:33 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

static char	*get_file_path(char **path, char *file);
static char	**get_path(t_list *var_list);

char	*cmd_search(t_wordl *cmd, t_list *var_list)
{
	char	**path;
	char	*cmd_loc;

	path = get_path(var_list);
	cmd_loc = get_file_path(path, cmd->word->value);
	free_2d(path);
	return (cmd_loc);
}

int	is_assignment(t_word *word)
{
	char	**split;
	int		rv;

	rv = 0;
	split = NULL;
	if (word)
	{
		if (word->value)
		{
			if (ft_strchr(word->value, EQUALS))
			{
				split = ft_split(word->value, EQUALS);
				if (is_name(split[0]))
					rv = 1;
			}
		}
	}
	if (split)
		free_2d(split);
	return (rv);
}

void	execute_and_check(char *cmd, char **args, char **env)
{
	if (cmd == NULL)
	{
		ft_dprintf(2, "%s%s\n", EPERROR, ENOCMD);
		exit(127);
	}
	execve(cmd, args, env);
	ft_dprintf(2, "%s%s: %s\n", EPERROR, cmd, strerror(errno));
	if (errno == EACCES)
		exit(126);
	exit(errno);
}

static char	*get_file_path(char **path, char *file)
{
	char	*file_w_slash;
	char	*join;

	if (access(file, X_OK) == 0 || ft_strchr(file, '/'))
		return (ft_strdup(file));
	join = NULL;
	if (file)
	{
		file_w_slash = ft_strjoin("/", file);
		while (*path)
		{
			join = ft_strjoin(*path, file_w_slash);
			if (access(join, X_OK) == 0 || !join)
				break ;
			path ++;
			free(join);
			join = NULL;
		}
		free(file_w_slash);
	}
	return (join);
}

static char	**get_path(t_list *var_list)
{
	t_list	*path;
	char	*value;
	char	**split;

	split = NULL;
	path = lst_get_by_key(var_list, PATH);
	if (path)
	{
		value = path->value;
		if (value)
			split = ft_split(value, PATH_DELIM);
	}
	return (split);
}
