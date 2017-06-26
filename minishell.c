#include "minishell.h"
#include "fakelib.c" // to remove
#include "src/settings.c" // to remove
#include "src/builtins.c" // to remove
#include "src/tools.c" // to remove

int         is_bultin(char **av, char *env[])
{
    char    *key_val[2];
    int     r;
    int     overwrite;

    r = 2;
    if (ft_strcmp(av[1], "env") == 0)
        r = builtin_env(env, av);
    if (r)
    {
        if (ft_strcmp(av[1], "cd") == 0)
            builtin_cd(av, env);
        else if (ft_strcmp(av[1], "echo") == 0)
            builtin_echo(av);
        else if (ft_strcmp(av[1], "setenv") == 0)
        {
            key_val[0] = av[2] ? av[2] : NULL;
            key_val[1] = av[3] ? av[3] : NULL;
            overwrite = av[4] ? ft_atoi(av[4]) : 0;
            builtin_setenv(env, key_val[0], key_val[1], overwrite);
        }
        else if (ft_strcmp(av[1], "unsetenv") == 0)
            builtin_unsetenv(env, av[2]);
        else
            return (r == 1 ? r : 0);
    }
    return (1);
}


/**
 * Get the executable path from env path
 *
 */

char         *get_exeutable_path(char *command, char *env[])
{
    int     i;
    char    **env_path;
    char    *tmp;

    env_path = (char **)ft_memalloc(sizeof(char));
    if (!(*env_path = ft_getenv(env, "PATH=")))
        return (NULL);
    *env_path = ft_strsub(*env_path, 5, ft_strlen(*env_path));
    env_path = ft_strsplit(*env_path, ':');
    i = -1;
    while (env_path[++i])
    {
        tmp = ft_strjoin(env_path[i], "/");
        tmp = ft_strjoin(tmp, command);
        if (access(tmp, F_OK & X_OK) == 0)
            return (tmp);
    }
    return (NULL);
}

int         launch(char *env[], char **av)
{
    char    *command;
    char    buf[50];
    
    if (!is_bultin(av, env))
    {
        if ((command = get_exeutable_path(av[1], env)))
        {
            execve(command, &av[1], env);
        }
    }
    return (1);
}

int         main(int ac, char *av[], char *env[])
{
    int     i;
    char    buf[PATH_MAX + 1];
    pid_t   cpid;

    cpid = fork();
    if (cpid == -1)
        printf("Error fork not valid pid\n");
    else if (cpid == 0)
    {
        launch(env, av);
    }
    else
    {
        wait();
        printf("$>");
        while (read(0, buf, 255) > 0)
        {
            printf("buff = %s\n", buf);
            execve("/bin/pwd", ft_strsplit(buf, ' '), env);
        }
    }
    return (0);
}
