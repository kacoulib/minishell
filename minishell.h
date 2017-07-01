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

# include "lib/libft/libft.h"
# include <unistd.h>
# include <stdio.h> // to remove

#define		PATH_MAX 255
#define		true 1
#define		false 0

int			builtin_cd(t_list *env, char **av);
int			builtin_echo(char **av);
int			builtin_env(t_list *env, char **av);
int			builtin_env_extra(t_list *env, char **av, char *flags);
int			builtin_env_extra_unset(t_list *env, char **av, char *flags);
int			builtin_exit(int status);
int			builtin_setenv(t_list *env, char **av);
int			builtin_unsetenv(t_list *env, char **av);
int			builtin_unsetenv_extra(t_list *env);
int			launch(char *command, char **av, t_list *env);
int			set_errors(int id, char *command, char *name);
int			special_char_extra(char c);
int			special_char(char *str);

#endif
