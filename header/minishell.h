/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 15:46:01 by kacoulib          #+#    #+#             */
/*   Updated: 2017/06/30 15:46:03 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <stdio.h> // to remove

typedef struct			s_flag_ctrl
{
	char				program_name[256];
	int					has_dash;
	int					show_error;
	int					step_back_on_error;
	int					reset_after_error;
	char				output[256];
	struct s_list		*list;
}						t_flag_ctrl;

typedef struct			s_shell_ctrl
{
	struct s_list		*env;
}						t_shell_ctrl;

int						is_bultin(char *command, char **av, t_list **env);
int						builtin_cd(t_list **env, char **av);
int						builtin_echo(char **av);
int						builtin_env(t_list **env, char **av);
int						builtin_env_extra_unset(t_list **env, char **av,
	char *flags);
int						builtin_setenv(t_list **env, char **av);
int						builtin_unsetenv(t_list **env, char **av);
int						builtin_exit(char *av);
// int						builtin_echo_args_limit(t_flag_ctrl *flag_ctr, char **av);


int						create_env(t_list **env, char *name, char *value);
int						update_env(t_list *env, char *name, char *value);
int						read_env(t_list **env, char *flags);
void					del_env(t_list *env, size_t len);


t_shell_ctrl			*get_shell(void);
t_shell_ctrl			*init_shell(char *envp[]);
int						delete_shell(void);
void					check_term(void);

int						ft_env_exist(t_list **env, char *key);
int						ft_check_env(t_list **env);


int						ft_print_prompt(void);


int						swap_env(t_list **env, char *s1, char *s2);
char					*ft_getenv(t_list **env, char *key);
char					*ft_getenv_val(t_list **env, char *key);
t_list					*copy_env(char *env[]);
t_list					*ft_getenv_from_list(t_list **env, char *key);

t_list					*init_flags(char *flags);
int						get_long_flag_id(t_flag_ctrl *flag_ctrl, char *av);
int						get_single_flag_id(t_flag_ctrl *flag_ctrl, char *av);
int						delete_flag_ctrl(t_flag_ctrl *ctrl);
int						flag_contain(t_flag_ctrl *flag_ctrl, char *str);
int						set_flag_output_and_get_limit(t_flag_ctrl *flag_ctrl,
	char **av);



int						get_args_limit(char **av);

int						set_errors(int id, char *command, char *name);
char					*set_errors_r_char(int id, char *command, char *name);

int						special_char(char *str);
int						free_arr(char **arr);
int						check_access(char *command, char *path);

char					**convert_list_to_array(t_list *list);
int						index_of_array(char **arr, char *key);

t_flag_ctrl				*create_flag_ctrl(char *program_name, int has_dash,
	int has_error);
void 					signal_handler(void);
char					*convert_home_to_tilde(char *path, char *login);
char					*convert_tilde_to_home(char *path, char *login);

# define PATH_MAX 255
# define TRUE 1
# define FALSE 0

#endif
