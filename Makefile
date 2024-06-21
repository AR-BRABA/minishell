NAME		= minishell

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g
SRCS		= display_prompt.c init.c
OBJS		= $(SRCS:.c=.o)
RM		= rm -rf

all		= $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
