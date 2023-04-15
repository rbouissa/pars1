#include "minishell.h"

int	check_string(char *str)
{
	int	i;
	int	k;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			k = str[i];
			i++;
			while (str[i] != k && str[i])
				i++;
			if (str[i] != k)
			{
				ft_write("syntax error exepected quote");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_eroor(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && !str[i + 1])
		{
			ft_write("syntax error near unexpected token `|'");
			return (0);
		}
		else if (str[i] == '|' && !str[i - 1])
		{
			ft_write("syntax error near unexpected token `|'");
			return (0);
		}
		else if ((str[i] == '>' || str[i] == '<') && !str[i + 1])
		{
			ft_write("syntax error near unexpected token `newline'");
			return (0);
		}
		else
			i++;
	}
	return (1);
}
