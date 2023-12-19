/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/09/16 09:40:01 by eraccane          #+#    #+#             */
/*   Updated: 2023/09/16 09:40:01 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <sys/ioctl.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_env
{
	char	**env;
	char	**v;
	char	**t;
	char	**mat_flag;
	char	*s;
	char	*cmd;
	char	*p;
	char	*path;
	int		r;
	int		i;
	int		i2;
	int		count;
	int		pipe_flag;
	int		j;
	int		sign;
	int		finded_path;
	int		equal;
	int		c_path;
	int		word;
	int		indx;
	int		iter;
	int		flag;
	int		true_red;
	int		cat_pipe;
	int		define_pipe;
	int		numb;
	int		valid;
	int		pipe;
	int		i_env;
	int		flag_i;
	int		lenght;
	int		ex;
	int		check;
	int		input;
	int		output;
	int		exit_code;
	int		exit;
	int		stdin;
	int		stdout;
	int		in_red;
	int		out_red;
	int		p_i;
	int		tmp_i;
	int		do_redir;
	int		status;
	int		c_pipe;
	int		check_input;
	int		start_red;
	int		expand;
	int		builtin;
	int		space;
	int		red;
	int		red_flag;
	int		pipefd[2];
	pid_t	pid;
	pid_t	child;
	pid_t	pid_pipe;
}	t_env;

int		mini_get_var(t_env *e, int i, int j);
int		empty(t_env *e);
int		compare(char *s1, char *s2);
int		path_find(char *str);
int		valid_pipe(t_env *e);
int		check_validation(t_env *e);
int		l(int n);
int		cont_invalid_cmd(t_env *e, int i);
int		ft_check_digit(char *s, t_env *e);
int		spacer(t_env *e);
int		check_closure(char *s);
int		check_signals_red(t_env *e, char *line);
int		ft_strnum(int i);
int		ft_strlen(const char *s);
int		size(t_env *e);
int		strcom(char *s, int e);
int		size_mat(char **t);
int		search_pipe(t_env *e);
int		ft_strlen_red(char *s);
int		update_redir(t_env *e);
int		control_match(char *s);
int		check_builtin(t_env *e);
int		search_arrows(t_env *e, char *s);
int		index_v_arrows(t_env *e, char *s);
int		invalid_cmd(t_env *e);
int		split_pipe(t_env *e);
int		check_error_red(int pipe_fd[2]);
int		venv(t_env *e, int i, int j);
int		init_nuller(t_env *e);
int		search_mult_arrows(t_env *e, char *s);
int		path_valid(char *s, t_env *e);
int		check_valid_red(t_env *e);
int		check_valid_red2(t_env *e);
int		do_redir(t_env *e);
int		check_validation(t_env *e);
int		short_get_var(t_env *e, int i, int j, int iter);

void	check_file(t_env *e);
void	cd_dollar(t_env *e, int i, int j);
void	single_write(t_env *e, char *fileoutput, int type);
void	flag_env(t_env *e);
void	do_pipe(t_env *e);
void	pipe_loop_redir(t_env *e);
void	last_in(t_env *e);
void	other_redir(t_env	*e);
void	cont_espfun(t_env *e);
void	check_first_input(t_env *e);
void	expand(t_env *e, int i);
void	execve_redir(t_env *e);
void	define_redir(t_env *e);
void	update_in_out(t_env *e);
void	last_file_in(t_env *e);
void	red_pipe_fork(t_env *e);
void	father_com(t_env *e);
void	split_clousure(t_env *e);
void	parent_loop_pipe(t_env *e);
void	update_pipe(t_env *e);
void	apice_var_quote(t_env *e, int j, int iter, int i);
void	update_i(t_env *e);
void	change_value(t_env *e, int i, char **tmp);
void	count_pipe(t_env *e);
void	check_path(t_env *e);
void	other_redir(t_env	*e);
void	pipe_com(t_env *e);
void	cont_what_exit(t_env *e);
void	pipe_and_redirection(t_env *e);
void	single_continuous(t_env *e, int fd);
void	flag_matrix(t_env *e);
void	espfun(t_env *e);
void	multiple_pipe(t_env *e);
void	fork_cotinue(t_env *e, pid_t pid, int fd);
void	quote_check(t_env *e);
void	execve_red(t_env *e, int fd);
void	print_str(char *s, int i);
void	word(t_env *e);
void	split_flag(t_env *e);
void	exiting(t_env *e, int i);
void	free_table(char **s);
void	flag_while(t_env *e);
void	redirect_double_arrows(t_env *e, char *buffer);
void	com(t_env *e);
void	new_export(t_env *e);
void	cont_check_dimension(t_env *e);
void	bridge(t_env *e, int j);
void	alloc_quote(t_env *e);
void	check_env(t_env *e);
void	envionment(t_env *e);
void	piping(t_env *e);
void	writeme(t_env *e);
void	typing(t_env *e);
void	pathcmd(t_env *e);
void	singals(t_env *e);
void	error(t_env *e);
void	dir_cont(t_env *e);
void	flag_env(t_env *e);
void	var_quote(t_env *e, int j, int iter, int i);
void	directory(t_env *e);
void	printf_env(t_env *e, int iter);
void	variabletype(t_env *e);
void	directory(t_env *e);
void	splitme(t_env *e);
void	waiting(t_env *e);
void	split(t_env *e);
void	redirect_mult_double(t_env *e);
void	searchpath(t_env *e);
void	handle_signal(int sig);
void	update_eword(t_env *e, int j);
void	writer(t_env *e, int j);
void	fork_loop(t_env *e);
void	parent2(t_env *e);
void	parent_process(t_env *e);
void	get_var_quote(t_env *e, int j, int iter, int i);
void	writing_split(t_env *e);
void	single_minor_redirect(t_env *e);
void	single_major_redirect(t_env *e);
void	double_minor_redirect(t_env *e);
void	double_major_redirect(t_env *e);
void	parent_pipe_red(t_env *e);
void	redirect_double(t_env *e);
void	redirect_single(t_env *e);
void	env_variable(t_env *e);
void	env_variable2(t_env *e);
void	check_red_fork(t_env *e, char *filename, int type);
void	fork_pid_zero(t_env *e, char *filename, int type);
void	alloc_mat(char *t, char *u);
void	check_export(t_env *e, int i, int j);
void	exiting_d(t_env *e);
void	check_export(t_env *e, int i, int j);
void	shortwhile(t_env *e);
void	last_file(t_env *e);
void	redirect_double_arrows(t_env *e, char *buffer);
void	cont_splitme(t_env *e);
void	redirect_mult_single(t_env *e);
void	check_built(char *s, int i, t_env *e);
void	multiple_redirect(t_env *e);
void	waiting2(t_env *e, pid_t pid);
void	continuing_minor_double(t_env *e, char *buffer, pid_t pid);
void	min_mult_redirect(t_env *e);
void	single_major_mult_redirect(t_env *e);
void	continue_heredoc(t_env *e, char *s);

char	*format(char *s);
char	*find_mult_mult_filepath(t_env *e);
char	*find_mult_filepath(t_env *e);
char	*update_buffer_red(char *line, char *buffer);
char	*ft_strjoin_n(char *s1, char *s2);
char	*mini_strcat(char *d, const char *s);
char	*update_buffer_red(char *line, char *buffer);
char	*find_filepath_minor_mult(t_env *e);
char	*find_lasth_filepath(t_env *e);
char	*find_filepath(t_env *e);
char	*alloc_file(t_env *e, char s);
char	*find_filepath_minor(t_env *e);
char	**new_tmp(t_env *e, char **tmp);
char	**alloc_tmp(t_env *e, char **tmp);
char	**exclude_env(t_env *e, char **tmp);
char	**exclude_env(t_env *e, char **tmp);

#endif