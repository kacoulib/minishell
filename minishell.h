#ifndef MINISHELL
#define MINISHELL

# include "lib/libft/libft.h"
# include <unistd.h>
# include <stdio.h> // to remove

PATH_MAX = 256;

int         builtin_env_extra(char *env[], char **av);

// size_t		ft_strlen(const char *str);
// char		*ft_strjoin(char const *s1, char const *s2);

#endif
