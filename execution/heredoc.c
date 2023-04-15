/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:15:40 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/31 18:15:42 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc(t_cmd *cmd)
{
	char	*s;
	int		i;
	char	*reading;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	reading = NULL;
	while (tmp->herdoc[i])
	{
		s = readline("> ");
		while (s)
		{
			if (ft_strcmp(s, tmp->herdoc[i]) == 0)
			{
				free(s);
				break ;
			}
			reading = ft_strjoin(reading, s);
			free(s);
			reading = ft_strjoin(reading, "\n");
			s = readline("> ");
		}
        
        i++;
    }//printf("%s\n",reading);
	return (reading);
}
