NAME			= minishell

CC			= cc
CFLAGS			= -Wall -Wextra -Werror -ggdb3
RM			= rm -rf
LIBFT_PATH		= includes/libft
LIBFT			= $(LIBFT_PATH)/libft.a

SRC_DIR			= srcs
VALIDATION_DIR		= $(SRC_DIR)/input_validation
EXECUTOR_DIR	= $(SRC_DIR)/executor
PARSER_DIR		= $(SRC_DIR)/parser
BUILTINS_DIR			= $(SRC_DIR)/builtins
UTILS_DIR			= $(SRC_DIR)/utils
INCLUDE_DIR		= includes
OBJ_DIR			= objs

SRC_FILES		= $(SRC_DIR)/init_minishell.c
VALIDATION_FILES	= $(VALIDATION_DIR)/validate_input.c \
					  $(VALIDATION_DIR)/validate_input_utils.c \
					  $(VALIDATION_DIR)/special_chars_validation.c \
					  $(VALIDATION_DIR)/special_chars_validation_utils.c 
EXECUTOR_FILES	= $(EXECUTOR_DIR)/command_path_utils.c \
				  $(EXECUTOR_DIR)/command_utils.c \
				  $(EXECUTOR_DIR)/executor.c \
				  $(EXECUTOR_DIR)/execute_builtins.c \
				  $(EXECUTOR_DIR)/execute_external_commands.c \
				  $(EXECUTOR_DIR)/fd_management.c \
				  $(EXECUTOR_DIR)/process_control.c \
					$(EXECUTOR_DIR)/redirect.c \
					$(EXECUTOR_DIR)/pre_exec.c 
PARSER_FILES	= $(PARSER_DIR)/env_search.c \
				  $(PARSER_DIR)/expansion_utils.c \
				  $(PARSER_DIR)/format.c \
				  $(PARSER_DIR)/identify_char.c \
				  $(PARSER_DIR)/lexer.c \
				  $(PARSER_DIR)/lexer_utils.c \
				  $(PARSER_DIR)/quote_utils.c \
				  $(PARSER_DIR)/token_split_utils.c \
				  $(PARSER_DIR)/tokenizer.c \
				  $(PARSER_DIR)/tokenizer_utils.c \
				  
BUILTINS_FILES		= $(BUILTINS_DIR)/pwd.c \
					  $(BUILTINS_DIR)/env.c \
					  $(BUILTINS_DIR)/cd.c \
					  $(BUILTINS_DIR)/echo.c \
					  $(BUILTINS_DIR)/exit.c \
					  $(BUILTINS_DIR)/unset.c \
					  $(BUILTINS_DIR)/export.c \
					  $(BUILTINS_DIR)/utils.c
UTILS_FILES		= $(UTILS_DIR)/free.c \
				  $(UTILS_DIR)/convertions.c \

OBJS			= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(VALIDATION_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(BUILTINS_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(EXECUTOR_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(PARSER_FILES:.c=.o))) \
				$(addprefix $(OBJ_DIR)/, $(notdir $(UTILS_FILES:.c=.o))) \

vpath %.c $(SRC_DIR) $(VALIDATION_DIR) $(BUILTINS_DIR) $(EXECUTOR_DIR) $(PARSER_DIR) $(UTILS_DIR)

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

val: $(NAME)
			valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s --suppressions=tests/valgrind.supp ./minishell

clean:
			$(MAKE) -C $(LIBFT_PATH) clean
			$(RM) $(OBJS)

fclean:			clean
			$(MAKE) -C $(LIBFT_PATH) fclean
			$(RM) $(NAME)
			$(RM) $(OBJ_DIR)

re:			fclean all

.PHONY:	all clean fclean re
