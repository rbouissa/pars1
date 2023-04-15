
#include "minishell.h"

t_mini	*ft_add_new(char *var, char *value, int valid)
{
	t_mini	*node;

	node = malloc(sizeof(t_mini));
	if (!node)
		return (NULL);
	node->data_var = var;
	node->data_val = value;
	node->valid = valid;
	node->next = NULL;
	return (node);
}


void	add_back_lst(t_mini **lst, t_mini *new)
{
	t_mini	*ptr;

	if (lst)
	{
		if (*lst)
		{
			ptr = last_lst(*lst);
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

t_list	*sort_list(t_list *lst, int (*cmp)(char *, char *))
{
	char	*swap;
	t_list	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (((*cmp)(lst->data, lst->next->data)) > 0)
		{
			swap = lst->data;
			lst->data = lst->next->data;
			lst->next->data = swap;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

void	freestack(t_list **stack)
{
	t_list	*temp;

	if (!*stack)
		return ;
	temp = *stack;
	while ((*stack)->next)
	{
		(*stack) = (*stack)->next;
		free(temp);
		temp = *stack;
	}
}

t_mini	*last_lst(t_mini *a)
{
	while (a->next)
		a = a->next;
	return (a);
}

t_list	*ft_lstnew(char *content,int t)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->data = content;
    node->token = t;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_front(t_list *lst, t_list *new)
{
	new->next = lst;
	lst = new;
}

t_list	*ft_last(t_list *a)
{
	while (a->next)
		a = a->next;
	return (a);
}
void    ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *ptr;

    if (lst)
    {
        if (*lst)
        {
            ptr = ft_last(*lst);
            ptr->next = new;
        }
        else
            *lst = new;
    }
}

// void	ft_lstadd_back(t_list *lst, t_list *new)
// {
// 	t_list	*node;

// 	node = lst;
// 	if (!new)
// 		return ;
// 	if (lst)
// 	{
// 		while (node->next)
// 			node = node->next;
// 		node->next = new;
// 	}
// 	else
// 		lst = new;
// }
t_cmd	*ft_last_new(void *tmp)
{
	t_cmd	*a;

	a = NULL;
	a = (t_cmd *)tmp;
	while (a->next)
		a = a->next;
	return (a);
}

void	ft_lstadd_back_new(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	ptr = NULL;
	if (lst)
	{
		if (*lst)
		{
			ptr = ft_last_new(*lst);
			ptr->next = new;
		}
		else
			*lst = new;
	}
}
t_cmd	*ft_lstnew_new(char **content, int t ,int k, char **her,int t_her)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
    
	node->cmd = content;
	node->infile = t;
    node->outfile = k;
    node->herdoc = her;
    node->herdoc_token=t_her;
	node->next = NULL;
	return (node);
}
// void	ft_lstadd_back_new(t_list *lst, t_list *new)
// {
// 	t_list	*node;

// 	node = lst;
// 	if (!new)
// 		return ;
// 	if (lst)
// 	{
// 		while (node->next)
// 			node = node->next;
// 		node->next = new;
// 	}
// 	else
// 		lst = new;
// }

int	size_list(t_list *a)
{
	if (a)
		return (1 + size_list(a->next));
	else
		return (0);
}