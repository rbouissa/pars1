/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:53:35 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/19 18:53:41 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// if (ft_strcmp(cmd->cmd[0], "export") == 0)
// {
// 	if (cmd->cmd[1] == NULL)
// 	{
// 		ft_export(cmd->cmd[1], mini);
// 	}
// 	while (cmd->cmd[e])
// 	{
// 		ft_export(cmd->cmd[e], mini);
// 		e++;
// 	}
// 	return ;
// }
// else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
// {
// 	while (cmd->cmd[e])
// 	{
// 		ft_unset(cmd->cmd[e], &mini);
// 		e++;
// 	}
// 	return ;
// }
// else if (ft_strcmp(cmd->cmd[0], "env") == 0)
// {
// 	ft_env(mini);
// 	return ;
// }
// else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
// {
// 	echo(cmd->cmd);
// 	return ;
// }
// else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
// {
// 	ft_cd(cmd->cmd[1], mini);
// 	return ;
// }
// else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
// {
// 	ft_pwd();
// 	return ;
// }

char	**cmd_paths(t_mini *mini)
{
	t_mini	*tmp;
	char	*paths;
	char	**spl_path;
	int		i;

	i = 0;
	paths = NULL;
	tmp = mini;
	while (tmp)
	{
		if (ft_strcmp(tmp->data_var, "PATH") == 0)
		{
			paths = ft_strdup(tmp->data_val);
			break ;
		}
		else
			tmp = tmp->next;
	}
	spl_path = ft_split(paths, ':');
	while (spl_path[i])
	{
		spl_path[i] = ft_strjoin(spl_path[i], "/");
		i++;
	}
	return (spl_path);
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("Child process received SIGINT\n");
}
int	count_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		pipe_count;

	tmp = NULL;
	tmp = cmd;
	pipe_count = 0;
	while (tmp)
	{
		pipe_count++;
		tmp = tmp->next;
	}
	return (pipe_count - 1);
}
int	execute_builts(t_mini *mini, char **cmd)
{
	int	e;

	e = 1;
	if (ft_strcmp(cmd[0], "export") == 0)
	{
		if (cmd[1] == NULL)
		{
			ft_export(cmd[1], mini);
		}
		else
		{
			while (cmd[e])
			{
				ft_export(cmd[e], mini);
				e++;
			}
		}
		return (1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		while (cmd[e])
		{
			ft_unset(cmd[e], &mini);
			e++;
		}
		return (1);
	}
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_env(mini);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "echo") == 0)
	{
		echo(cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		ft_cd(cmd[1], mini);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_pwd();
		return (1);
	}
	return (0);
}

void	exec_cmd(t_mini *mini, t_cmd *cmd, char **env)
{
	int		pip_count;
	int		fd[count_pipes(cmd)][2];
	t_mini	*tmp;
	char	**paths;
	int		j;
	int		i;
	int		check;
	pid_t	id[count_pipes(cmd)];
	int		fd_hrdoc[2];
	int		e;
	int		id_hrd;
	char	*line;

	paths = NULL;
	check = 0;
	j = 0;
	e = 0;
	pip_count = count_pipes(cmd);
	i = 0;
	paths = cmd_paths(mini);
	tmp = mini;
	e = 1;
	while (i <= pip_count)
	{
		if (pipe(fd[i]) < 0)
		{
			perror("pipes");
			exit(1);
		}
		i++;
	}
	i = 0;
	if (pip_count == 0)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		if (cmd->herdoc[0] != NULL)
		{
			if (pipe(fd_hrdoc) == -1)
			{
				perror("pipe");
				exit(1);
			}
			id_hrd = fork();
			if (id_hrd == 0)
			{
				line = heredoc(cmd);
				ft_putstr_fd(line, fd_hrdoc[1]);
				close(fd_hrdoc[0]);
				close(fd_hrdoc[1]);
				exit(0);
			}
			else
			{
				waitpid(id_hrd, NULL, 0);
				close(fd_hrdoc[1]);
			}
		}
		if (execute_builts(mini, cmd->cmd) == 1)
			return ;
		id[i] = fork();
		if (id[i] < 0)
		{
			perror("fork");
			exit(1);
		}
		else if (id[i] == 0)
		{
			if (cmd->herdoc[0] != NULL)
			{
				dup2(fd_hrdoc[0], STDIN_FILENO);
				close(fd_hrdoc[1]);
				close(fd_hrdoc[0]);
			}
			if (cmd->infile != -2 && cmd->infile != 0 && cmd->infile != -1)
			{
				if (dup2(cmd->infile, STDOUT_FILENO) == -1)
				{
					perror("dup2");
					exit(1);
				}
				close(cmd->infile);
			}
			if (cmd->outfile != -2 && cmd->outfile != 0 && cmd->outfile != -1)
			{
				printf("hhhhhhhh\n");
				if (dup2(cmd->outfile, STDIN_FILENO) == -1)
				{
					perror("dup2");
					exit(1);
				}
				close(cmd->outfile);
			}
			if ((cmd->cmd[0][0] == '/' || cmd->cmd[0][0] == '.')
				&& access(cmd->cmd[0], F_OK) == 0)
			{
				if (execve(cmd->cmd[0], cmd->cmd, env) == -1)
				{
					perror("execve error");
					exit(1);
				}
			}
			else
			{
				while (paths[j])
				{
					paths[j] = ft_strjoin(paths[j], cmd->cmd[0]);
					if (access(paths[j], F_OK) == 0)
					{
						if (execve(paths[j], cmd->cmd, env) == -1)
						{
							perror("execve error");
							exit(1);
						}
						ft_free(paths);
					}
					else
						j++;
				}
				if (paths[j] == NULL)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmd->cmd[0], 2);
					ft_putstr_fd(": command not found\n", 2);
					exit(1);
				}
			}
		}
		else
		{
			waitpid(id[i], NULL, 0);
			close(fd[i][0]);
			close(fd[i][1]);
			//close(cmd->infile);
		}
	}
	else
	{
		j = 0;
		e = 1;
		while (cmd && i <= pip_count)
		{
			check = 1;
			// creation des child process;
			id[i] = fork();
			if (id[i] < 0)
			{
				perror("error with fork");
				exit(1);
			}
			// child process;
			else if (id[i] == 0)
			{
				if (execute_builts(mini, cmd->cmd) == 1)
					exit(0);
				if (i == 0)
				{
					//printf("ok1\n");
					close(fd[i][0]);
					dup2(fd[i][1], STDOUT_FILENO);
					while (j < pip_count)
					{
						close(fd[j][1]);
						close(fd[j][0]);
						j++;
					}
					j = 0;
				}
				else if (i == pip_count)
				{
					//printf("ok2\n");
					close(fd[i - 1][1]);
					dup2(fd[i - 1][0], STDIN_FILENO);
					while (j < pip_count)
					{
						close(fd[j][1]);
						close(fd[j][0]);
						j++;
					}
					j = 0;
				}
				else
				{
					close(fd[i - 1][1]);
					close(fd[i][0]);
					dup2(fd[i - 1][0], STDIN_FILENO);
					dup2(fd[i][1], STDOUT_FILENO);
					while (j < pip_count)
					{
						close(fd[j][1]);
						close(fd[j][0]);
						j++;
					}
					j = 0;
				}
				//printf("infile====%d----outfile====%d\n", cmd->outfile,
				//cmd->infile);
				if (cmd->infile != -2 && cmd->infile != 0 && cmd->infile != -1)
				{
					if (dup2(cmd->infile, STDOUT_FILENO) == -1)
					{
						perror("dup2 error");
						exit(1);
					}
					close(cmd->infile);
				}
				while (paths[j])
				{
					paths[j] = ft_strjoin(paths[j], cmd->cmd[0]);
					if (access(paths[j], F_OK) == 0)
					{
						if (execve(paths[j], cmd->cmd, env) == -1)
						{
							perror("error with execve");
							exit(1);
						}
					}
					else
						j++;
				}
				if (paths[j] == NULL)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmd->cmd[0], 2);
					ft_putstr_fd(": command not found\n", 2);
					exit(1);
				}
			}
			// incrementer a la commande suivante;
			else
			{
				// close the fd;
				if (i == 0)
					close(fd[i][1]);
				else if (i == pip_count)
				{
					close(fd[i - 1][0]);
					close(fd[i - 1][1]);
				}
				else
				{
					close(fd[i][1]);
					close(fd[i - 1][0]);
					close(fd[i - 1][1]);
				}
				i++;
				cmd = cmd->next;
			}
			j = 0;
		}
		// wait pour tous les child process;
		if (check == 1)
		{
			i = 0;
			while (i <= pip_count)
			{
				waitpid(id[i], NULL, 0);
				close(fd[i][0]);
				close(fd[i][1]);
				i++;
			}
		}
	}
}
