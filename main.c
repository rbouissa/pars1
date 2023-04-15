#include "minishell.h"

int	ther_are_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	*str_2;
	t_list	*cmd;
	t_mini	*mini;
	t_cmd	*commands;
	int		i;
	int		j;
	int		k;

	//t_cmd	*tmp;
	i = 0;
	(void)argc;
	(void)argv;
	//mini = NULL;
	k = 0;
	j = 0;
	mini = env_iniit(env);
	cmd = NULL;
	commands = NULL;
	str = NULL;
	str_2 = NULL;
	while (1)
	{
		str = readline("minishell>");
		str_2 = handle_quotes(str, mini);
        
        //printf("%s\n",str_2);
        //printf("%s\n",str_2);
		// // add expanding variables
		if (str_2[0])
		{
			// j = check_eroor(str_2);
			// k = check_string(str_2);
			//if (j && k)
			//{
				cmd = ft_split_them(str_2);
				commands = split_to_commands(cmd, str_2);
               
                if(commands->outfile !=-1 && commands->outfile!=-1)
				 	exec_cmd(mini, commands, env);
                
                // while (commands)
				// {
				// 	// 	while (commands->cmd[i])
				// 	// 	{
				// 	// 		printf("%s\n", commands->cmd[i]);
				// 	// 		i++;
				// 	// 	}
				// 	 i = 0;
				// 	 if (commands->cmd[i] == NULL)
				// 		printf("%s\n", commands->cmd[i]);
				// 	while (commands->cmd[i])
				// 	{
				// 		printf("command==");
				// 		printf("%s\n", commands->cmd[i]);
				// 		i++;
				// 	}
				// 	i = 0;
				// 	if (commands->herdoc[i] == NULL)
				// 		printf("%s\n", commands->herdoc[i]);
				// 	else
				// 	{
				// 		while (commands->herdoc[i])
				// 		{
				// 			printf("herdoc==");
				// 			printf("%s\n", commands->herdoc[i]);
				// 			i++;
				// 		}
				// 	}
				// 	 printf("%d\n", commands->infile);
				// 	 printf("%d\n", commands->outfile);
				// 	// printf("%d\n", commands->herdoc_token);
				// 	commands = commands->next;
				// 	//printf("kllko\n");
				// }
				//tmp = commands;
				// 
			//}
		}
		add_history(str);
		free(str);
	}
}
