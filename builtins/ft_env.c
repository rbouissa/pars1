/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:53:11 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/08 11:53:12 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// void	ft_unset(char *var, t_mini **tmp)
// {
// 	t_mini	*exp;
// 	t_mini	*tmp1;

// 	exp = *tmp;
// 	tmp1 = *tmp;
// 	if (var == NULL)
// 		ft_putstr_fd("miissing variiable name\n", 2);
// 	else
// 	{
// 		if (ft_strcmp((*tmp)->data_var, var) == 0)
// 		{
// 			tmp1 = (*tmp)->next;
// 			free((*tmp)->data_var);
		
// 			free((*tmp)->data_val);
// 			free((*tmp));
// 			printf("=====%s===\n", (*tmp)->data_val);
// 			*tmp = tmp1;
// 			return;
// 		}
// 		else
// 		{
// 			while (tmp)
// 			{
// 				if (ft_strcmp((*tmp)->data_var, var) == 0)
// 				{
// 					tmp1->next = (*tmp)->next;
// 					free((*tmp)->data_var);
// 					free((*tmp)->data_val);
// 					free(*tmp);
// 					break;
// 				}
// 				else
// 				{
// 					tmp1 = *tmp;
// 					*tmp = (*tmp)->next;
// 				}
// 			}
// 		}
// 	}
// 	*tmp =exp;
// }
// t_list	*env_init(char **env)
// {
// 	t_list	*new;
// 	t_list	*lst;
// 	t_list	*tmp;
// 	char	*s;
// 	int		i;

// 	i = 0;
// 	lst = 0;
// 	if (*env == NULL)
// 		return(NULL);
// 	while (env[i])
// 	{
// 		s = ft_strdup(env[i]);
// 		new = ft_lstnew(s);
// 		ftt_lstadd_back(&lst, new);
// 		i++;
// 	}
// 	free(s);
// 	tmp = lst;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->data = "_=/usr/bin/env";
// 	return (lst);
// }
void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	**var_split(char *s, char c)
{
	char	**var;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if(ft_strchr(s,'=')!=1)
		return (ft_split(s, '='));
	var = malloc(sizeof(char *) * 3);
	var[0] = ft_substr(s, 0, i);
	var[1] = ft_substr(s, i+1, ft_strlen(s));
	var[2] = NULL;
	return (var);
}
t_mini	*env_iniit(char **env)
{
	t_mini	*new;
	t_mini	*lst;
	t_mini	*tmp;
	char	*s;
	int		i;
	char	**tmp1;

	i = 0;
	lst = 0;
	tmp1 = NULL;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			tmp1 = var_split(env[i], '=');
			new = ft_add_new(tmp1[0], tmp1[1], 0);
			add_back_lst(&lst, new);
			free(tmp1);
		}
		i++;
	}
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	s = ft_strdup("_");
	free(tmp->data_var);
	tmp->data_var = s;
	s = ft_strdup("/usr/bin/env");
	free(tmp->data_val);
	tmp->data_val = s;
	return (lst);
}

void	ft_env(t_mini *lst)
{
	while (lst)
	{
		if (lst->valid == 0)
			printf("%s=%s\n", lst->data_var, lst->data_val);
		lst = lst->next;
	}
}

// int	main(int c, char **v, char **env)
// {
// 	(void)c;
// 	(void)v;
// 	t_mini *eh;
// 	eh = env_iniit(env);
// 	ft_env(eh);
// }