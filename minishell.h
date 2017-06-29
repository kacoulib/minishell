#ifndef MINISHELL
#define MINISHELL

# include "lib/libft/libft.h"
# include <unistd.h>
# include <stdio.h> // to remove

int			PATH_MAX = 256;

int			builtin_cd(char **av, char *env[]);
int			builtin_echo(char **av);
int			builtin_env(char *env[], char **av);
int			builtin_env_extra(char *env[], char **av, char *flags);
int			builtin_env_extra_unset(char *env[], char **av, char *flags);
int			builtin_exit(int status);
int			builtin_setenv(char *env[], char *key, char *value, int overwrite);
int			builtin_unsetenv(char *env[], char *name);
int			launch(char *command, char **av, char *env[]);
int         set_errors(int id, char *command, char *name);
int         special_char_extra(char c);
int         special_char(char *str);



// size_t		ft_strlen(const char *str);
// char		*ft_strjoin(char const *s1, char const *s2);

#endif
