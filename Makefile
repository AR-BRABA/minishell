NAME			= minishell

CC			= cc
CFLAGS			= -Wall -Wextra -Werror -ggdb3
RM			= rm -rf
LIBFT_PATH		= includes/libft
LIBFT			= $(LIBFT_PATH)/libft.a

SRC_DIR			= srcs
VALIDATION_DIR		= $(SRC_DIR)/input_validation
ENV_DIR			= $(SRC_DIR)/env
EXECUTOR_DIR	= $(SRC_DIR)/executor
ECHO_DIR		= $(SRC_DIR)/echo
CD_DIR			= $(SRC_DIR)/cd
PARSER_DIR		= $(SRC_DIR)/parser
PWD_DIR			= $(SRC_DIR)/pwd

INCLUDE_DIR		= includes
OBJ_DIR			= objs

SRC_FILES		= $(SRC_DIR)/init_minishell.c
VALIDATION_FILES	= $(VALIDATION_DIR)/validate_input.c \
				      $(VALIDATION_DIR)/validate_input_utils.c
ENV_FILES		= $(ENV_DIR)/env.c
EXECUTOR_FILES	= $(EXECUTOR_DIR)/executor.c \
				  $(EXECUTOR_DIR)/execute_builtins.c \
				  $(EXECUTOR_DIR)/execute_external_commands.c
PARSER_FILES	= $(PARSER_DIR)/free.c \
				  $(PARSER_DIR)/identify_char.c \
				  $(PARSER_DIR)/lexer.c \
				  $(PARSER_DIR)/lexer_utils.c \
				  $(PARSER_DIR)/list_utils.c \
				  $(PARSER_DIR)/print.c \
				  $(PARSER_DIR)/tokenizer.c \
				  $(PARSER_DIR)/tokenizer_utils.c \
				  $(PARSER_DIR)/token_format.c
ECHO_FILES		= $(ECHO_DIR)/echo.c
CD_FILES		= $(ENV_DIR)/cd.c
PWD_FILES		= $(PWD_DIR)/pwd.c

OBJS			= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(VALIDATION_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(ENV_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(EXECUTOR_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(PARSER_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(ECHO_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(CD_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(PWD_FILES:.c=.o))) \

vpath %.c $(SRC_DIR) $(VALIDATION_DIR) $(ENV_DIR) $(EXECUTOR_DIR) $(PARSER_DIR) $(CD_DIR) $(PWD_DIR) $(ECHO_DIR)

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
