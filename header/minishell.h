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

#ifndef	MINISHELL
#define	MINISHELL

# include "../libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h> // to remove

#define		PATH_MAX 255
#define		true 1
#define		false 0

int			builtin_cd(t_list **env, char **av);
int			builtin_echo(char **av);
int			builtin_env(t_list **env, char **av);
// int			builtin_env_extra(t_list **env, char **av);
int			builtin_env_extra_unset(t_list **env, char **av, char *flags);
// int			builtin_exit(int status);
int			builtin_setenv(t_list **env, char **av);
int			builtin_unsetenv(t_list **env, char **av);
// int			builtin_unsetenv_extra(t_list **env, char **av);
int			launch(char *command, char **av, t_list **env);
int			print_env(t_list **env, char *flags);
int			set_errors(int id, char *command, char *name);
int			special_char(char *str);
int			swap_env(t_list **env, char *s1, char *s2);
char		*ft_getenv(t_list **env, char *key);
char		*get_glags(char *except_flags, char **av, char *command);
int			free_arr(char **arr);
int			get_args_limit(char **av);
t_list		*ft_getenv_from_list(t_list **env, char *key);
void		del(void *content, size_t len);
char		**convert_list_to_array(t_list *list);
int			index_of_array(char **arr, char *key);
char		*check_and_get_flag(char *builtin, char **av);

t_list		*copy_env(char *env[]);


#endif
