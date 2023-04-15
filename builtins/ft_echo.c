/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:53:00 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/08 11:53:02 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **cmd)
{
	int	n;
	int	nb_arg;
	size_t	i;

	i = 1;
	n = 0;
	nb_arg = 1;
	if (cmd[1])
	{
		while (cmd[1][i])
		{
			
			if (cmd[1][i] == 'n')
				i++;
			else
				break ;
		}
		if (ft_strlen(cmd[1]) == i)
		{
			n = 1;
			nb_arg = 2;
		}
	}
	while (cmd[nb_arg])
	{
		printf("%s", cmd[nb_arg]);
		nb_arg++;
		if (cmd[nb_arg])
			printf(" ");
	}
	if (n == 0)
		printf("\n");
}
// int	main(int c, char **v)
// {
// 	(void)c;
// 	echo(v);
// }