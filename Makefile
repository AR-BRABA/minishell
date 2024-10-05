NAME			= minishell

CC			= cc
CFLAGS			= -Wall -Wextra -Werror -ggdb3
RM			= rm -rf
LIBFT_PATH		= includes/libft
LIBFT			= $(LIBFT_PATH)/libft.a

SRC_DIR			= srcs
VALIDATION_DIR		= $(SRC_DIR)/input_validation
ENV_DIR			= $(SRC_DIR)/env
CD_DIR			= $(SRC_DIR)/cd
PARSER_DIR		= $(SRC_DIR)/parser

INCLUDE_DIR		= includes
OBJ_DIR			= objs

#SRC_FILES		= init_minishell.c validate_input.c validate_input_utils.c \
#			  parser/free.c parser/identify_char.c parser/lexer.c parser/lexer_utils.c parser/print.c parser/tokenizer.c parser/tokenizer_utils.c parser/token_format.c \
#			  env/env.c
#SRCS			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_FILES		= $(SRC_DIR)/init_minishell.c
VALIDATION_FILES	= $(VALIDATION_DIR)/validate_input.c $(VALIDATION_DIR)/validate_input_utils.c
ENV_FILES		= $(ENV_DIR)/env.c
CD_FILES		= $(ENV_DIR)/cd.c
PARSER_FILES		= $(PARSER_DIR)/free.c $(PARSER_DIR)/identify_char.c $(PARSER_DIR)/lexer.c \
				$(PARSER_DIR)/lexer_utils.c $(PARSER_DIR)/print.c $(PARSER_DIR)/tokenizer.c \
				$(PARSER_DIR)/tokenizer_utils.c $(PARSER_DIR)/token_format.c

#OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS			= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(VALIDATION_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(ENV_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(PARSER_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(CD_FILES:.c=.o))) \

vpath %.c $(SRC_DIR) $(VALIDATION_DIR) $(ENV_DIR) $(PARSER_DIR) $(CD_DIR)
vpath %.h $(INCLUDE_DIR)

all:			 $(NAME)

$(NAME):		$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT_PATH) -lft -lreadline

$(OBJ_DIR)/%.o: 	%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_PATH) -c -o $@ $<

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(LIBFT):
			if [ ! -f $(LIBFT) ]; then \
				$(MAKE) -C $(LIBFT_PATH) all; \
			fi

clean:
			$(MAKE) -C $(LIBFT_PATH) clean
			$(RM) $(OBJS)

fclean:			clean
			$(MAKE) -C $(LIBFT_PATH) fclean
			$(RM) $(NAME)
			$(RM) $(OBJ_DIR)

re:			fclean all

.PHONY:	all clean fclean re
