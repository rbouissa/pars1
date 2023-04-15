

#include "minishell.h"

int	find_spliter(char s, char *sp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (sp[i])
	{
		if (s == sp[i])
			return (1);
		i++;
	}
	return (0);
}
int	my_token(char *s)
{
	int	token;
	token = 0;
	if (!ft_strcmp(s, "|"))
		token = 5;
	else if (!ft_strcmp(s, ">"))
		token = 2;
	else if (!ft_strcmp(s, "<"))
		token = 3;
	else if (!ft_strcmp(s, "<<"))
		token = 4;
	else if (!ft_strcmp(s, ">>"))
		token = 1;
	else if (!ft_strcmp(s, "||"))
		token = 6;
	return (token);
}
t_list	*ft_split_them(char *str)
{
	t_list	*s;
	int		i;
	char	*node;
	char	*st;
	int		j;
	int		k;
	int		check;
	int		token;
	int		quotes;

	check = 0;
	quotes = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		k = i;
		if (str[i] == 34 || str[i] == 39)
		{
			quotes = str[i];
			i++;
			while (str[i] && (str[i] != quotes))
				i++;
		}
		else
		{
			//for alocation
			while (str[i] && !find_spliter(str[i], "|<> "))
				i++;
		}
		//if don't find the spliter in the front
		if (i - k != 0)
		{
			//the alocate
			node = malloc(i - k + 1);
			i = k;
			j = 0;
			if (str[i] == 34 || str[i] == 39)
			{
				quotes = str[i];
			//node[j] = str[i];
				while (str[++i] && (str[i] != quotes))
				{
					node[j] = str[i];
					
					j++;
				}
				i++;
			}
			//fill our node
			while (str[i] && !find_spliter(str[i], "|<> "))
			{
				node[j] = str[i];
				j++;
				i++;
			}
			node[j] = 0;
			//to be here just on time for creat the frist node
			if (check == 0)
			{
				s = ft_lstnew(node, 0);
				check = 1;
			}
			//her for the rest
			else
				ft_lstadd_back(&s, ft_lstnew(node, 0));
		}
		else
		{
			k = i;
			j = 0;
			while (str[i] && find_spliter(str[i], "|<> "))
			{
				if (find_spliter(str[i], "|<>"))
					j++;
				i++;
			}
			if (j != 0)
			{
				st = malloc(j + 1);
				j = 0;
				i = k;
				while (str[i] && find_spliter(str[i], "|<> "))
				{
					if (find_spliter(str[i], "|<>"))
					{
						st[j] = str[i];
						j++;
					}
					i++;
				}
				st[j] = 0;
				if (check == 0)
				{
					token = my_token(st);
					s = ft_lstnew(st, token);
					check = 1;
				}
				else
				{
					token = my_token(st);
					ft_lstadd_back(&s, ft_lstnew(st, token));
				}
			}
		}
	}
	return (s);
}

// int	main(int argc, char **argv)
// {
// 	t_list	*s;
// 	int		i;

// 	s = ft_split_them(argv[1]);
// 	i = 0;
// 	while (s)
// 	{
// 		printf("%s->>>>   ", s->data);
//         printf("%d\n", s->token);
// 		s = s->next;
// 	}
// }
