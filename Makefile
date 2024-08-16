NAME = minishell
FLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

RL_FLAGS = -lreadline

SRCS = minishell.c \
		input_validation.c \
		split_func.c \
		command.c \
		builtins_util.c \
		export.c \
		cd.c \
		export_utils.c \
		heredoc.c \
		space_manipulation.c \
		quotes_handle.c \
		pipex.c \
		open_fd.c \
		free.c \
		expand.c \
		redirect.c \
		utils_functions.c \
		piping.c \
		signals.c \
		exit.c \
		parse_line.c \
		initialize.c \
		builtins.c \
		cd_utils.c \
		pwd.c \
		free_all.c \
		redirect_with_builtins.c \
		child.c \
		unset_var.c \
		expand_utils.c \
		redirect_utils.c \
		heredoc_utils.c \
		utils.c \
		running_commands.c \
		error_msg.c
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	cc $(FLAGS) $(OBJS) $(LIBFT_LIB) $(RL_FLAGS) -o $(NAME)

$(LIBFT_LIB): $(LIBFT_DIR)
	make -C $(LIBFT_DIR)
 
%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re