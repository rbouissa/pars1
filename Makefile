CFLAGS	= -Wall -Wextra -Werror #-g -fsanitize=address
LIBC	= ar -rc
RM		= rm -f
NAME	= minishell
SRC		= main.c \
			ft_split.c \
			libft_helpers.c \
			builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_env.c \
			builtins/ft_pwd.c \
			builtins/ft_unset.c \
			list_utils.c \
			builtins/ft_export.c \
			builtins/ft_error.c \
			builtins/ft_exit.c \
			execution/pipes.c \
			execution/heredoc.c \
			add_to_list.c \
			test_split.c \
			creat_list_command.c \
			env.c\
			


OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME) 

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME) 

re:	fclean all

b: all clean