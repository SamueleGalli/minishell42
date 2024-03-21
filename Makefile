CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -lreadline -Wpedantic
NAME = minishell

SRC = 	main.c \
		type/type.c \
		type/type2.c \
		ausiliary/helper.c \
		ausiliary/helper2.c \
		path/path.c \
		path/contiue_path.c \
		split/split.c \
		split/split2.c \
		split/split3.c \
		split/split4.c \
		syntax/check_error.c \
		syntax/check_error2.c \
		syntax/check_error3.c \
		other/alloc.c \
		other/check_builtin.c \
		other/env.c \
		other/free.c \
		expand_val/expand_first.c \
		expand_val/cont_expand.c \
		other/quote.c \
		other/size.c \
		libft/ft_atoi.c \
		libft/ft_bzero.c \
		libft/ft_calloc.c \
		libft/ft_isalnum.c \
		libft/ft_isalpha.c \
		libft/ft_isascii.c \
		libft/ft_isdigit.c \
		libft/ft_isprint.c \
		libft/ft_memchr.c \
		libft/ft_memcmp.c \
		libft/ft_memcpy.c \
		libft/ft_memmove.c \
		libft/ft_memset.c \
		libft/ft_putnbr_fd.c \
		libft/ft_putchar_fd.c \
		libft/ft_putstr_fd.c \
		libft/ft_strchr.c \
		libft/ft_strrchr.c \
		libft/ft_strdup.c \
		libft/ft_strlcat.c \
		libft/ft_strlcpy.c \
		libft/ft_strlen.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \
		libft/ft_tolower.c \
		libft/ft_toupper.c \
		libft/ft_strjoin.c \
		libft/ft_itoa.c \
		libft/ft_striteri.c \
		libft/ft_strmapi.c \
		libft/ft_strtrim.c \
		libft/ft_split.c \
		libft/ft_putendl_fd.c \
		libft/ft_substr.c \
		libft/ft_strcpy.c \
		libft/ft_strcat.c \
		di_sistema/signal/signal.c \
		di_sistema/exit/exit.c \
		di_sistema/cd/cd.c \
		di_sistema/cd/cd2.c \
		di_sistema/echo/echo.c \
		di_sistema/echo/echo2.c \
		di_sistema/echo/echo3.c \
		di_sistema/echo/echo4.c \
		di_sistema/export_unset_env/unset_env.c \
		di_sistema/export_unset_env/export.c \
		di_sistema/export_unset_env/export2.c \
		di_sistema/export_unset_env/export3.c \
		di_sistema/export_unset_env/export4.c \
		di_sistema/execve/commands.c \
		di_sistema/execve/flags.c \
		di_sistema/execve/flag2.c \
		di_sistema/execve/flag_env.c \
		pipe_red/redirections/cont_min_red.c \
		pipe_red/redirections/find_file.c \
		pipe_red/redirections/find_red_type.c \
		pipe_red/redirections/help_redirection.c \
		pipe_red/redirections/heredoc2.c \
		pipe_red/redirections/heredoc.c \
		pipe_red/redirections/heredoc3.c \
		pipe_red/redirections/heredoc4.c \
		pipe_red/redirections/major_red.c \
		pipe_red/redirections/major_red2.c \
		pipe_red/redirections/minor_red.c \
		pipe_red/redirections/multiple_file_red.c \
		pipe_red/redirections/multiple_file_red2.c \
		pipe_red/redirections/pipe_and_red_check.c \
		pipe_red/redirections/update_red.c \
		pipe_red/pipe/do_pipe.c \
		pipe_red/pipe/execute_pipe.c \
		pipe_red/pipe/check_pipe.c \
		pipe_red/pipe/in_pipe.c \
		pipe_red/pipe/pipe.c \
		pipe_red/pipe_and_redirection/pipe_and_redirection.c \
		pipe_red/pipe_and_redirection/help_pipe_and_redirect.c \
		pipe_red/pipe_and_redirection/do_red.c \
		pipe_red/pipe_and_redirection/excve_redir.c \
		pipe_red/pipe_and_redirection/cont_min_red_mult.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	@echo Compiling $<...
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): libft $(OBJ)
	@echo Linking... {$(NAME)}...
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) 

clean:
	@echo Cleaning...
	@rm -f $(OBJ)

fclean: clean
	@echo Cleaning...
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
