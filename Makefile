NAME			= minishell

CC			= cc
CFLAGS			= -Wall -Wextra -Werror -g
RM			= rm -rf
LIBFT_PATH		= includes/libft

SRC_DIR			= srcs
INCLUDE_DIR		= includes
OBJ_DIR			= objs

SRC_FILES		= srcs/display_prompt.c srcs/init_minishell.c srcs/validate_input.c\
					srcs/validate_input_utils.c
OBJS			= $(SRC_FILES:.c=.o)

LIBFT			= $(LIBFT_PATH)/libft.a

all			= $(NAME)

$(NAME):		$(OBJS) $(LIBFT)
			@$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_PATH) -lft -lreadline

$(OBJ_DIR)/%.o: 	$(SRC_DIR/%.c)
			mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_PATH) -c -o $@

$(LIBFT):
			@$(MAKE) -C $(LIBFT_PATH)

clean:
			@$(MAKE) -C $(LIBFT_PATH) clean
			$(RM) $(OBJS)

fclean:			clean
			@$(MAKE) -C $(LIBFT_PATH) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
