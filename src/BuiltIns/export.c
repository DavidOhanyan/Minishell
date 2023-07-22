/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:52:07 by dohanyan          #+#    #+#             */
/*   Updated: 2023/07/22 16:46:07 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lex.h"

static void	ft_sort(char **env);
static void	estat_set(t_control *ctl, int fail);
static int	ft_default(char **env, t_list *var_list);

int	export(t_wordl *args, t_control *ctl)
{
	char	**split;
	char	**env;
	t_wordl	*temp;
	int		fail;

	fail = FALSE;
	temp = args->next;
	env = get_env_key(ctl->var_list);
	if (!temp)
		return (ft_default(env, ctl->var_list));
	while (temp)
	{
		split = ft_split(temp->word->value, EQUALS);
		if (!is_name(split[0]))
		{
			ft_dprintf(STDERR_FILENO, ERR_EXPORT, temp->word->value);
			fail = TRUE;
		}
		lst_set_by_word(ctl->var_list, EXPORT, temp->word->value);
		free_2d(split);
		temp = temp->next;
	}
	free(env);
	estat_set(ctl, fail);
	return (ft_atoi(lst_get_by_key(ctl->var_list, ECODE)->value));
}

static void	estat_set(t_control *ctl, int fail)
{
	if (fail)
		lst_set(ctl->var_list, SHELL, ECODE, FAIL);
	else
		lst_set(ctl->var_list, SHELL, ECODE, SUCCESS);
}

static int	ft_default(char **env, t_list *var_list)
{
	int		i;
	t_list	*tmp;

	i = 0;
	ft_sort(env);
	while (env[i])
	{
		tmp = lst_get_by_key(var_list, *(env + i));
		printf("%s %s", DL, *(env + i));
		if (ft_strchr(tmp->joined, EQUALS))
		{
			printf("=\"");
			if (tmp->value)
				printf("%s", tmp->value);
			printf("\"");
		}
		printf("\n");
		i ++;
	}
	return (EXIT_SUCCESS);
}

static void	ft_sort(char **env)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen_2d((const char **)env);
	i = 0;
	while (i < len -1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				ft_swap((void **)&env[i], (void **)&env[j]);
			j++;
		}
		i++;
	}
}
