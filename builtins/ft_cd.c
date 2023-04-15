/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:52:51 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/08 11:52:52 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//cette fonction change OLDPWD dans mon env;
char	*oldpwd_change(char *path, t_mini *tmp)
{
	char	*pwd;
	t_mini	*tmp1;

	tmp1 = tmp;
	while (tmp1)
	{
		if (ft_strncmp(tmp1->data_var, "OLDPWD", 6) == 0)
		{
			pwd = getcwd(NULL, 0);
			path = ft_strdup(tmp1->data_val);
			free(tmp1->data_val);
			tmp1->data_val = ft_strdup(pwd);
			free(pwd);
			break ;
		}
		tmp1 = tmp1->next;
	}
	// path = getenv("OLDPWD");
	return (path);
}

// cette fonction change PWD dans mon env;
void	new_pwd_change(t_mini *tmp, char *s1, int size)
{
	char	*pwd;

	while (tmp)
	{
		if (ft_strncmp(tmp->data_var, s1, size) == 0)
		{
			pwd = getcwd(NULL, 0);
			free(tmp->data_val);
			tmp->data_val = ft_strdup(pwd);
			free(pwd);
			break ;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_cd(char *path, t_mini *lst)
{
	t_mini	*tmp;
	char	*pwd;

	tmp = lst;
	pwd = getcwd(NULL, 0);
	// la fonction access verifie si le chemin existe ou non;
	

	
	if (path == NULL)
	{
		new_pwd_change(tmp, "OLDPWD", 6);
		chdir(getenv("HOME"));
	}
	else if (ft_strcmp(path, "") == 0)
	{
		chdir(pwd);
	}
	else if (path == NULL || ft_strcmp(path, "~") == 0)
	{
		new_pwd_change(tmp, "OLDPWD", 6);
		chdir(getenv("HOME"));
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		path = oldpwd_change(path,tmp);
		chdir(path);
		printf("%s\n", path);
	}
	else if (access(path, R_OK) != 0)
		cd_error(path);
	else
	{
		new_pwd_change(tmp, "OLDPWD", 6);
		chdir(path);
	}
	tmp = lst;
	new_pwd_change(tmp, "PWD", 3);
	free(pwd);
}

// int	main(int c, char **v, char **env)
// {
// 	t_mini	*lst;
// 	int		i;

// 	i = 0;
// 	(void)v;
// 	(void)c;
// 	(void)env;
// 	lst = env_iniit(env);
// 	ft_env(lst);
// 	printf("------------------------------\n");
// 	ft_cd("builtins", lst);
// 	printf("------------------------------\n");
// 	ft_env(lst);
// 	system("leaks minishell");
// 	//ft_cd("-", lst);
// }
