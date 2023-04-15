#include "minishell.h"

void	freestack_last(t_list **stack)
{
	t_list	*temp;

	if (!*stack)
		return ;
	temp = *stack;
	while (*stack && (*stack)->next && (*stack)->token != 5)
	{
		(*stack) = (*stack)->next;
		free(temp->data);
		free(temp);
		temp = *stack;
	}
	*stack = (*stack)->next;
	if (temp->data)
		free(temp->data);
	free(temp);
	//     free(temp);
}

int	here_pipe(t_list *ko)
{
	t_list	*lk;

	lk = ko;
	while (lk)
	{
		if (lk->token == 5)
			return (1);
		lk = lk->next;
	}
	return (0);
}

int	file_numb(t_list *comm, char *str)
{
	t_list	*command;
	t_list	*cm;
	int		token;

	token = 0;
	cm = comm;
	(void)str;
	command = comm;
	while (command->next)
	{
		if (command->next->token == 5 || command->next == NULL)
			break ;
		//it gives the same number because we don't limit it int the th pipe
		if (command->token == 2)
		{
			//printf("command->next->data====%s\n", command->next->data);
			token = open(command->next->data, O_CREAT | O_WRONLY, 0644);
			if (token == -1)
			{
				perror("open error");
				exit(1);
			}
		}
		command = command->next;
	}
	return (token);
}
int	file_numb2(t_list *comm, char *str)
{
	t_list	*command;
	t_list	*cm;
	int		token;

	token = 0;
	cm = comm;
	(void)str;
	command = comm;
	while (command->next)
	{
		if (command->next->token == 5 || command->next == NULL)
			break ;
		//it gives the same number because we don't limit it int the th pipe
		if (command->token == 3)
		{
			token = open(command->next->data, O_RDONLY, 0777);
			if (token == -1)
			{
				write(2, "minishell: ", 11);
				perror(command->next->data);
				return (-1);
			}
		}
		command = command->next;
	}
	return (token);
}
t_cmd	*split_to_commands(t_list *comm, char *str)
{
	char *cmd;
	char *hrd;
	t_list *command;
	char **herdoc;
	char **full_cmd;
	int check;
	char *spliter;
	t_cmd *list;
	int token;
	int token2;

	cmd = NULL;
	hrd = NULL;
	herdoc = NULL;
	full_cmd = NULL;
	command = comm;
	check = 0;
	spliter = malloc(2);
	spliter[0] = 19;
	spliter[1] = '\0';
	token = -2;
	token2 = -2;
	if (!ther_are_pipe(str))
	{
		while (command)
		{
			if (command->token == 2 || command->token == 3)
			{
				if (command->token == 2)
					token = file_numb(comm, str);
				else if (command->token == 3)
                {
					token2 = file_numb2(comm, str);
                    // if(token2 == -1)
                    //     break;
                }
				command = command->next->next;
			}
			else if (command->token == 4)
			{
				command = command->next;
				hrd = ft_strjoin(hrd, spliter);
				hrd = ft_strjoin(hrd, command->data);
				command = command->next;
			}
			else
			{
				cmd = ft_strjoin(cmd, spliter);
				cmd = ft_strjoin(cmd, command->data);
				command = command->next;
			}
		}

		if (hrd != NULL)
		{
			if (cmd == NULL)
			{
				full_cmd = malloc(sizeof(char *));
				full_cmd[0] = 0;
				list = ft_lstnew_new(full_cmd, token, token2, ft_split(hrd, 19),
						1);
				//free(full_cmd);
			}
			else
				list = ft_lstnew_new(ft_split(cmd, 19), token, token2,
						ft_split(hrd, 19), 1);	
		}
		else
		{
			herdoc = malloc(sizeof(char *));
			herdoc[0] = 0;
			list = ft_lstnew_new(ft_split(cmd, 19), token, token2, herdoc, -2);
		}
	}
    //for multiple pipe
	else
	{
		while (command != NULL)
		{
			if (command->token == 5)
			{
                //hrd = NULL;
				command = command->next;
				if (check == 0)
				{
					check = 1;
					if (command->token == 2)
						token = file_numb(comm, str);
					else if (command->token == 3)
                    {
						token2 = file_numb2(comm, str);
                        // if(token2==-1)
                        //  break;
                    }
					freestack_last(&comm);
					if (hrd != NULL)
					{
						if (cmd != NULL)
						{
                            
							list = ft_lstnew_new(ft_split(cmd, 19), token,
									token2, ft_split(hrd, 19), 1);
						}
						else
						{
							full_cmd = malloc(sizeof(char *));
							full_cmd[0] = 0;
							list = ft_lstnew_new(full_cmd, token, token2,
									ft_split(hrd, 19), 1);
							free(full_cmd);
						}
					}
					else
					{
						herdoc = malloc(sizeof(char *));
						herdoc[0] = 0;
						list = ft_lstnew_new(ft_split(cmd, 19), token, token2,
								herdoc, -2);
					}
				}
				else
				{
					token = file_numb2(comm, str);
					freestack_last(&comm);
					if (hrd != NULL)
					{
						if (cmd != NULL)
						{
							ft_lstadd_back_new(&list, ft_lstnew_new(ft_split(cmd, 19),
                            token, token2, ft_split(hrd, 19), 1));
						}
						else
						{
							full_cmd = malloc(sizeof(char *));
							full_cmd[0] = 0;
							ft_lstadd_back_new(&list, ft_lstnew_new(full_cmd,
                            token, token2, herdoc, 1));
							free(full_cmd);
						}
					}
					else
					{
						herdoc = malloc(sizeof(char *));
						herdoc[0] = 0;
						ft_lstadd_back_new(&list, ft_lstnew_new(ft_split(cmd, 19),
                            token, token2, herdoc, 1));
					}
				}
				cmd = NULL;
                hrd=NULL;
			}
			else if (command->token == 2 || command->token == 3)
			{
				if (command->token == 2)
					token = file_numb(comm, str);
				else if (command->token == 3)
					token2 = file_numb2(comm, str);
				command = command->next->next;
			}
			else if (command->token == 4)
			{
				command = command->next;
				hrd = ft_strjoin(hrd, spliter);
				hrd = ft_strjoin(hrd, command->data);
				command = command->next;
			}
			//this part make a segfaul in the function of get token file
			else
			{
                
				cmd = ft_strjoin(cmd, spliter);
				cmd = ft_strjoin(cmd, command->data);
				command = command->next;
			}
		}
		if (hrd != NULL)
		{
			if (cmd != NULL)
			{
				ft_lstadd_back_new(&list, ft_lstnew_new(ft_split(cmd, 19),
                            token, token2, ft_split(hrd, 19), 1));
			}
			else
			{
				full_cmd = malloc(sizeof(char *));
				full_cmd[0] = 0;

				 ft_lstadd_back_new(&list, ft_lstnew_new(full_cmd,
                            token, token2, ft_split(hrd, 19), 1));
				free(full_cmd);
			}
		}
		else
		{
			herdoc = malloc(sizeof(char *));
			herdoc[0] = 0;
			ft_lstadd_back_new(&list, ft_lstnew_new(ft_split(cmd, 19),
													token, token2, herdoc, 1));
		}
	}
	return (list);
}

// t_cmd	*split_to_commands(t_list *comm, char *str)
// {
// 	char *cmd;
// 	char *hrd;
// 	t_list *command;
//     char **herdoc;
// 	int check;
// 	char *spliter;
// 	t_cmd *list;
// 	int token;
// 	int token2;

// 	cmd = NULL;
// 	hrd = NULL;
//     herdoc =NULL;
// 	command = comm;
// 	check = 0;
// 	spliter = malloc(2);
// 	spliter[0] = 19;
// 	spliter[1] = '\0';
// 	token = -2;
// 	token2 = -2;
// 	if (!ther_are_pipe(str))
// 	{
// 		while (command)
// 		{
// 			if (command->token == 2 || command->token == 3)
// 			{
// 				if (command->token == 2)
// 					token = file_numb(comm, str);
// 				else if (command->token == 3)
// 					token2 = file_numb2(comm, str);
// 				command = command->next->next;
// 			}
// 			else if (command->token == 1)
// 			{
// 				command = command->next;
// 				hrd = ft_strjoin(hrd, spliter);
// 				hrd = ft_strjoin(hrd, command->data);
// 				command = command->next;
// 			}
// 			else
// 			{
// 				cmd = ft_strjoin(cmd, spliter);
// 				cmd = ft_strjoin(cmd, command->data);
// 				command = command->next;
// 			}
// 		}
// 		if (hrd != NULL)
// 			list = ft_lstnew_new(ft_split(cmd, 19), token, token2, ft_split(hrd,
// 						19), 1);
// 		else
// 		{
//             herdoc = malloc(sizeof(char *));
//             herdoc[0] = 0;
// 			list = ft_lstnew_new(ft_split(cmd, 19), token, token2, herdoc, -2);
//             //printf("%s\n",list->herdoc[0]);
// 		}
// 	}
// 	else
// 	{
// 		while (command)
// 		{
// 			if (command->token == 5)
// 			{

// 				command = command->next;
// 				if (check == 0)
// 				{
// 					if (command->token == 2)
// 						token = file_numb(comm, str);
// 					else if (command->token == 3)
// 						token2 = file_numb2(comm, str);

// 					freestack_last(&comm);
// 					list = ft_lstnew_new(ft_split(cmd, 19), token, token2,
// 							ft_split(hrd, 19), 1);
// 					check = 1;
// 				}
// 				else
// 				{
// 					token = file_numb2(comm, str);
// 					freestack_last(&comm);
// 					ft_lstadd_back_new(&list, ft_lstnew_new(ft_split(cmd, 19),
// 								token, token2, ft_split(hrd, 19), 1));
// 				}
// 				cmd = NULL;
// 			}
// 			else if (command->token == 2 || command->token == 3)
// 			{
// 				if (command->token == 2)
// 					token = file_numb(comm, str);
// 				else if (command->token == 3)
// 					token2 = file_numb2(comm, str);
// 				command = command->next->next;
// 			}
// 			else if (command)
// 			{

// 				if (command->token == 1)
// 				{
// 					command = command->next;
// 					hrd = ft_strjoin(hrd, spliter);
// 					hrd = ft_strjoin(hrd, command->data);
// 					command = command->next;
// 				}
// 				else
// 				{

// 					cmd = ft_strjoin(cmd, spliter);
// 					cmd = ft_strjoin(cmd, command->data);
// 					command = command->next;

// 				}

// 			}
// 			//this part make a segfaul in the function of get token file
// 			if (command == NULL)
// 			{
// 				//token = file_numb(comm, str);
// 				ft_lstadd_back_new(&list, ft_lstnew_new(ft_split(cmd, 19),
// 							token, token2, ft_split(hrd, 19), 1));
// 			}
// 		}
// 	}
// 	return (list);
// }
