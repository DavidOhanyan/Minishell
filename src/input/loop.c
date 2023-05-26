/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:57:14 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/26 21:49:57 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	@param fd is a file discriptor of .History file
*/

void	true_loop(void)
{
	int		fd;
	char	*str;

	fd = open("src/input/.History", O_CREAT | O_RDWR | O_APPEND);
	while (1)
	{
		str = readline("minishell-3.2$ ");
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			ft_putendl_fd(str, fd);
		}
	}
}
