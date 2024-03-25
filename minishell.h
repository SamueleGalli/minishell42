/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:42:52 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/21 10:42:52 by sgalli           ###   ########.fr       */
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
	char	**delim;
	char	**mat_flag;
	char	*tmp_pwd;
	char	*s;
	char	*buffer;
	char	*cmd;
	char	*p;
	char	*filename;
	char	*path;
	int		r;
	int		here_pipe;
	int		i;
	int		pwd;
	int		piping;
	int		i2;
	int		c_wait;
	int		count;
	int		j;
	int		is_valid;
	int		sign;
	int		finded_path;
	int		c_path;
	int		word;
	int		indx;
	int		pi_re;
	int		iter;
	int		numb;
	int		q_null;
	int		i_env;
	int		no_print;
	int		flag_i;
	int		lenght;
	int		here;
	int		ex;
	int		check;
	int		input;
	int		count_exp;
	int		i_here;
	int		output;
	int		exit_code;
	int		no_here;
	int		exit;
	int		stdin;
	int		stdout;
	int		i_tmp;
	int		i_copy;
	int		tmp_i;
	int		do_redir;
	int		status;
	int		c_pipe;
	int		check_input;
	int		expand;
	int		builtin;
	int		space;
	int		red;
	int		red_flag;
	int		pipefd[2];
	pid_t	pid;
	pid_t	pid_pipe;
}	t_env;

int		mini_get_var(t_env *e, int i, int j);
int		empty(t_env *e);
int		compare(char *s1, char *s2);
int		path_find(char *str);
int		last_check_val(t_env *e, int j);
int		l(int n);
int		ft_check_digit(char *s, t_env *e);
int		spacer(t_env *e);
int		check_closure(char *s);
int		check_signals_red(t_env *e, char *line);
int		ft_strnum(int i);
int		ft_strlen(const char *s);
int		size(t_env *e);
int		strcom(char *s, int e);
int		size_mat(char **t);
int		is_pipe_red(t_env *e);
int		ft_strlen_red(char *s);
int		next_valid(char *s, t_env *e);
int		update_redir(t_env *e);
int		single_error(t_env *e);
int		check_builtin(t_env *e);
int		check_last_major(t_env *e);
int		index_v_arrows(t_env *e, char *s);
int		split_pipe(t_env *e);
int		prev_minor_red(t_env *e, int fd, char *filename);
int		min_com(t_env *e);
int		init_nuller(t_env *e);
int		search_mult_arrows(t_env *e, char *s);
int		path_valid(char *s, t_env *e);
int		get_var_quote(t_env *e, int j, int iter, int i);
int		cont_print_red(t_env *e, int i, int exist);
int		do_redir(t_env *e);
int		alloc_str(t_env *e, int i, int c);
int		final_here(t_env *e, int i);
int		len_exp(char *str, t_env *e);
int		writer(t_env *e, int j);
int		check_here(t_env *e, char *line);
int		len_tilde(char *s, int i);
int		mutiple_equal(t_env *e);
int		cont_last_check(t_env *e);
int		loop_file(t_env *e, int fd, int type);
int		valid_redp(t_env *e, int i);
int		multi_file(t_env *e);
int		single_red(t_env *e);
int		len_red(t_env *e);
int		exits_pipe(t_env *e);
int		opening_file(t_env *e, int fd, int type);
int		pipe_or_redir(t_env *e);
int		single_file(t_env *e, int fd, int type);
int		which_pipe(t_env *e);
int		size_env(t_env *e);
int		is_empty_variable(t_env *e, int j, int i);
int		is_empty_variable(t_env *e, int j, int i);
int		count_len_exp(t_env *e, int j, int i, int len);
int		short_echo(t_env *e, int i);
int		check_quote_sindoub(t_env *e);
int		if_only_space(t_env *e);
int		invalid_red(t_env *e, int i);
int		while_pwd(t_env *e, int i, char **tmp);
int		close_quote_double(t_env *e, int i, int j);
int		close_quote_single(t_env *e, int i, int j);
int		is_quote(t_env *e, int i);
int		quoting_len(t_env *e);
int		check_truth(t_env *e, int i);

void	split_normal(t_env *e);
void	exp_split(t_env *e);
void	singal_fork(t_env *e);
void	alloc_pwd(t_env *e, int i);
void	cont_pwd(t_env *e);
void	in_major(t_env *e);
void	reset_variable(t_env *e);
void	shoreter_else(t_env *e, char *s);
void	here_while(t_env *e, char *line, int i);
void	check_next_car(t_env *e);
void	write_null(t_env *e);
void	error_perror(t_env *e, int fd);
void	short_write(t_env *e, int j);
void	check_quote(t_env *e, int j);
void	print_no_n(char *s, t_env *e);
void	update_v(t_env *e);
void	print_in_pipe(t_env *e);
void	pipe_error(t_env *e);
void	alloc_all_here(t_env *e);
void	alloc_mat_space(char *d, char *s);
void	execute_pipe(t_env *e);
void	control_pipe(t_env *e);
void	cont_while_mult_file(t_env *e, int fd, char *filename, int i);
void	print_red(t_env *e, int exist);
void	cont_mult_file(t_env *e, int fd, char *filename);
void	dimension_validation(t_env *e);
void	splong_red(t_env *e);
void	check_max_min(t_env *e);
void	check_validation(t_env *e);
void	write_redir(t_env *e);
void	print_no_quote(char *s, int exist);
void	check_red_other(t_env *e);
void	cd_dollar(t_env *e, int i, int j);
void	check_next_redp(t_env *e);
void	do_pipe(t_env *e);
void	copy_env(t_env *e, char **env);
void	what_exit(t_env *e);
void	mult_check_file(t_env *e, int fd, char *filename);
void	cont_espfun(t_env *e);
void	expand(t_env *e, int i);
void	execve_redir(t_env *e);
void	go_root(t_env *e, int i);
void	split_clousure(t_env *e);
void	update_pipe(t_env *e);
void	apice_var_quote(t_env *e, int j, int iter, int i);
void	update_i(t_env *e);
void	tilde_or_not(t_env *e, char *tmp);
void	check_path(t_env *e);
void	while_multiple_file(t_env *e, int fd);
void	pipe_com(t_env *e);
void	cont_what_exit(t_env *e);
void	pipe_and_redirection(t_env *e);
void	single_continuous(t_env *e, int fd);
void	flag_matrix(t_env *e);
void	expand_first(t_env *e);
void	espfun(t_env *e);
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
void	writeme(t_env *e);
void	typing(t_env *e);
void	pathcmd(t_env *e);
void	singals(t_env *e);
void	error(t_env *e);
void	dir_cont(t_env *e);
void	printf_env(t_env *e, int iter);
void	variabletype(t_env *e);
void	directory(t_env *e);
void	splitme(t_env *e);
void	waiting(t_env *e);
void	split(t_env *e);
void	single_export(t_env *e);
void	redirect_mult_double(t_env *e);
void	searchpath(t_env *e);
void	handle_signal(int sig);

void	writing_split(t_env *e);
void	double_minor_redirect(t_env *e);
void	env_variable(t_env *e);
void	env_variable2(t_env *e);
void	check_red_fork(t_env *e);
void	fork_pid_zero(t_env *e);
void	alloc_mat(char *t, char *u);
void	exiting_d(t_env *e);
void	cont_splitme(t_env *e);
void	redirect_mult_single(t_env *e);
void	check_built(char *s, int i, t_env *e);
void	waiting2(t_env *e, pid_t pid);
void	continuing_minor_double(t_env *e, char *buffer, pid_t pid);
void	min_mult_redirect(t_env *e);
void	continue_heredoc(t_env *e, char *s);
void	update_env_v(t_env *e, int k, int i, char **tmp);
void	alloc_mat_esp(char *d, t_env *e);
void	mini_while(t_env *e);

char	**copy_pwd(t_env *e, char **tmp);
char	*convert_line(char *line, t_env *e, int j, int k);
char	*file_loop(t_env *e);
char	*filepath(char *str, int j, t_env *e);
char	*format(char *s);
char	*find_filepath_major(t_env *e);
char	*ft_strjoin_n(char *s1, char *s2);
char	*mini_strcat(char *d, const char *s);
char	*update_buffer_red(char *line, char *buffer, t_env *e);
char	*find_filepath_minor_mult(t_env *e);
char	*alloc_s(char *buf);
char	*find_lasth_filepath(t_env *e);
char	*alloc_file(t_env *e, char s);
char	**new_tmp(t_env *e, char **tmp);
char	**cont_new_tmp(t_env *e, char **tmp, int i);
char	**exclude_env(t_env *e, char **tmp);
#endif