/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:53:20 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/08 11:53:21 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	s_digit(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if ((s[i] >= 48 && s[i] <= 57))
			i++;
		else
			return (0);
	}
	return (1);
}
// int atoi_pro(char *s)
// {
//     int r = ft_atoi(s);
//     if(s )
// }
void	ft_exit(char *status)
{
	int	s;

	s = ft_atoi(status);
	if (status == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else if (s_digit(status) == 0)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", status);
		exit(255);
	}
	else
	{
        exit(s);
    }
}
// int	main(void)
// {
//     ft_exit("9223372036854775808");
// }