NAME			= minishell

CC			= cc
CFLAGS			= -Wall -Wextra -Werror -ggdb3
RM			= rm -rf
LIBFT_PATH		= includes/libft
LIBFT			= $(LIBFT_PATH)/libft.a

SRC_DIR			= srcs
INCLUDE_DIR		= includes
OBJ_DIR			= objs

SRC_FILES		= init_minishell.c validate_input.c validate_input_utils.c \
			  parser/free.c parser/identify_char.c parser/lexer.c parser/lexer_utils.c parser/print.c parser/tokenizer.c parser/tokenizer_utils.c parser/token_format.c \
			  env/env.c
SRCS			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

vpath %.c $(SRC_DIR)
vpath %.h $(INCLUDE_DIR)

all:			 $(NAME)

$(NAME):		$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT_PATH) -lft -lreadline

$(OBJ_DIR)/%.o: 	$(SRC_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_PATH) -c -o $@ $<

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(LIBFT):
			if [ ! -f $(LIBFT) ]; then \
				$(MAKE) -C $(LIBFT_PATH) all; \
			fi

clean:
			$(MAKE) -C $(LIBFT_PATH) clean
			$(RM) $(OBJ_DIR)/*.o $(OBJ_DIR)/*/*.o

fclean:			clean
			$(MAKE) -C $(LIBFT_PATH) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
