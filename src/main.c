/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:19 by dohanyan          #+#    #+#             */
/*   Updated: 2023/06/25 22:40:56 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_tokl(t_tokl *tokens)
{
	t_tokl	*rem;

	rem = NULL;
	while (tokens)
	{
		rem = tokens->next;
		free(tokens->word->value);
		free(tokens->word);
		free(tokens);
		tokens = rem;
	}
}

static void	switch_case(t_list *var_list, char *str)
{
	char	**split;

	split = ft_split(str, ' ');
	if (ft_strcmp(str, "history") == 0)
		history(var_list);
	if (ft_strcmp(split[0], "cd") == 0)
		cd(split[1], var_list);
	if (ft_strcmp(split[0], "echo") == 0)
		echo(split);
	if (ft_strcmp(split[0], "exit") == 0)
		my_exit(var_list, split[1]);
	if (ft_strcmp(str, "pwd") == 0)
		pwd();
	if (ft_strcmp(split[0], "unset") == 0)
		unset(&var_list, split[1]);
	if (ft_strcmp(str, "env") == 0)
		env(var_list);
	free_2d(split);
}

/**
 * @brief	Readline while loop
 */
void	true_loop(t_list *var_list, int fd)
{
	char	*str;
	t_tokl	*tokens;

	tokens = NULL;
	sig_init();
	while (1)
	{
		str = readline(lst_get_by_key(var_list, "PS1")->value);
		if (!str)
		{
			write (2, "exit", 4);
			break ;
		}
		if (!(*str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		ft_putendl_fd(str, fd);
		tokens = lex(str);
		switch_case(var_list, str);
		free_tokl(tokens);
		free(str);
		system("leaks minishell");
	}
}

int	main(int ac, char **av, char **env)
{
	int		fd;
	t_list	*var_list;
	char	*filename;
	print_logo();
	rl_readline_name = "Minishell";
	rl_instream = stdin;
	if (isatty(STDERR_FILENO))
		rl_outstream = stderr;
	mode_init(ac, av);
	var_list = env_init(env);
	filename = lst_get_by_key(var_list, "HISTFILE")->value;
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	true_loop(var_list, fd);
	lst_clear(&var_list, &free);
	return (0);
}
