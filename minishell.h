/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouissa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:54:47 by met-tahe          #+#    #+#             */
/*   Updated: 2023/04/09 06:32:12 by rbouissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define no_quotes 0
# define isingle_quotes 1
# define idouble_quotes  2
typedef struct s_mini
{
	int				valid;
	char			*data_var;
	char			*data_val;
	struct s_mini	*next;
}					t_mini;

typedef struct s_list
{
	char			*data;
	int				token;
	struct s_list	*next;
}					t_list;

typedef struct s_cmd
{
	char			**herdoc;
	int				herdoc_token;
	char			**cmd;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

int					ft_strcmp(char *s1, char *s2);
void				ft_pwd(void);
char				*ft_strjoin(char *left_str, char *buff);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strdup(char *src);
t_list				*split_fuul_cmd(char **s);
int					ft_strchr(char *s, int c);
char				**ft_split(char *s, char c);
t_list				*ft_lstnew(char *content, int t);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_last(t_list *a);
int					ft_strncmp(char *s1, char *s2, int len);
void				ft_env(t_mini *lst);
t_list				*sort_list(t_list *lst, int (*cmp)(char *, char *));
void				freestack(t_list **stack);
void				cd_error(char *path);
void				add_back_lst(t_mini **lst, t_mini *new);
t_mini				*ft_add_new(char *var, char *value, int valid);
t_mini				*last_lst(t_mini *a);
t_mini				*env_iniit(char **env);
char				*ft_substr(char *s, int start, int len);
size_t				ft_strlen(char *s);
char				**var_split(char *s, char c);
void				ft_putstr_fd(char *s, int fd);
void				ft_export(char *var, t_mini *exp);
int					ft_atoi(char *str);
int					s_digit(char *s);
void				ft_free(char **str);
int					check_error(char *s);
int					check_eroor(char *str);
void				ft_write(char *s);
int					check_string(char *str);
t_list				*ft_split_them(char *str);
void				exec_cmd(t_mini *mini, t_cmd *cmd, char **env);
void				echo(char **cmd);
void				ft_unset(char *var, t_mini **tmp);
void				ft_cd(char *path, t_mini *lst);
t_cmd				*ft_lstnew_new(char **content, int t, int k, char **her,
						int t_her);
void				ft_lstadd_back_new(t_cmd **lst, t_cmd *new);
t_cmd				*split_to_commands(t_list *comm, char *str);
int					ther_are_pipe(char *str);
char				*heredoc(t_cmd *cmd);
char				*finnd_valeur(t_mini *env, char *str);
int					find_spliter(char s, char *sp);
char				*exp_hoho(char *str, t_mini *expand);
char	*handle_quotes(char *str,t_mini *env);
#endif
