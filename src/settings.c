#include "../minishell.h"

/*
* get the key and value from the enviroment path depennding on a key
*
* @param  env [an array of key pair vaule]
* @param  key [the key that should be find in the env]
* @return     [return NULL if the key don't exist otherwise return the key and value]
*/

char         *ft_getenv(char *env[], char *key)
{
    int     i;

    i = -1;
    while (env[++i])
        if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
            if (ft_indexof(key, '=') > -1)
                    return (env[i]);
    return (NULL);
}


/*
* Switch two env
*
* @param  env [an array of key pair vaule]
* @param  s1 [the first key in env that should replace]
* @param  s1 [the second key in env that should replace]
* @return     [return 1 on success otherwise return 0]
*/

int         swap_env(char *env[], char *s1, char *s2)
{
    int     i;
    char    *old;
    char    *new;
    char    **r1;
    char    **r2;

    if (!(new = ft_getenv(env, s1)) || !(old = ft_getenv(env, s2)))
        return (0);
    r1 = ft_strsplit(new, '=');
    r2 = ft_strsplit(old, '=');
    i = -1;
    while (env[++i])
    {
        if (ft_strncmp(env[i], s1, ft_strlen(s1)) == 0)
                    env[i] = ft_strjoin(s1, r2[1]);
        else if (ft_strncmp(env[i], s2, ft_strlen(s2)) == 0)
                    env[i] = ft_strjoin(s2, r1[1]);
    }
    return (1);
}

int         get_args_limit(char **av)
{
    int     i;
    int     j;

    i = 1;
    j = 0;
    while (av[++i] && av[i][0] == '-' && av[i][1])
        j++;
    return (j ? ++j : j);
}

int         free_arr(char **arr)
{
    int     i;

    i = -1;
    while (arr[++i])
        free(arr[i]);
    return (1);
}

int     index_of_array(char **arr, char *key)
{
    int i;

    i = -1;
    while (arr[++i])
        if (ft_strcmp(arr[i], key) == 0)
            return (i);
    return (-1);
}

/**
 * if the param is single dash
 * e.g: -en
 *
 * @param  flags [the command flags]
 * @param  av [the argument pass through the program]
 * @param  command [the name of the command]
 * @return         [description]
 */

char        *get_single_flags(char *flags[], char *av, char *command)
{
    int     i;
    char    *r;
    char    *tmp;

    i = 0;
    r = NULL;
    while (av[++i] && (tmp = ft_strsub(av, i, 1)))
    {
        if (index_of_array(flags, tmp) >= 0)
        {
            if (!r)
                r = ft_strdup(tmp);
            else
                r = ft_strjoin(r, tmp);
            r = ft_strjoin(r, " ");
        }
        else
        {
            set_errors(1, command, tmp);
            return (NULL);
        }
        free(tmp);
    }
    return (r);
}

/**
 * set the parm flags with flags
 *
 * @param  flags [the command flags]
 * @param  av [the argument pass through the program]
 * @param  command [the name of the command]
 * @return      [return NULL on error or if no flags are found otherwise return the flags]
 */

char         *get_glags(char *except_flags, char **av, char *command)
{
    int     i;
    char    **flags;
    char    *tmp;
    char    *r;

    i = 1;
    flags = ft_strsplit(except_flags, ' ');
    r = ft_strdup(" ");
    while (av[++i] && av[i][0] == '-' && av[i][1])
	{
        r = ft_strjoin(r, " ");
        if (av[i][1] != '-')
        {
            if (!(tmp = get_single_flags(flags, av[i], command)))
                return (NULL);
            r = ft_strjoin(r, tmp);
            free(tmp);
        }
        else if (index_of_array(flags, av[i]) >= 0)
            r = ft_strjoin(r, av[i]);
        else
        {
            set_errors(1, command, av[i]);
            return (NULL);
        }
	}
    r = ft_strjoin(r, " ");
    free_arr(flags);
    return (r); // free r and retunn null if an error occurred
}

/**
 * set the parm flags even if the key contain an assignation
 *
 * @param  flags [the command flags]
 * @param  av [the argument pass through the program]
 * @param  command [the name of the command]
 * @return      [return NULL on error or if no flags are found otherwise return the flags]
 */

char         *get_compose_glags(char *except_flags, char **av, char *command)
{
    int     i;
    char    **flags;
    char    *tmp;
    char    *r;

    i = 1;
    flags = ft_strsplit(except_flags, ' ');
    r = ft_strdup(" ");
    while (av[++i] && av[i][0] == '-' && av[i][1])
	{
        r = ft_strjoin(r, " ");
        if (av[i][1] != '-')
        {
            if (!(tmp = get_single_flags(flags, av[i], command)))
                return (NULL);
            r = ft_strjoin(r, tmp);
            free(tmp);
        }
        else if (index_of_array(flags, av[i]) >= 0)
            r = ft_strjoin(r, av[i]);
        else
        {
            set_errors(1, command, av[i]);
            return (NULL);
        }
	}
    r = ft_strjoin(r, " ");
    free_arr(flags);
    return (r); // free r and retunn null if an error occurred
}

/*
*
* display errors depennding on an id
* @param  id   [the id for the error]
* @param  command [the name of the command]
* @param  name [the error name]
* @return      [return 0]
*/

int         set_errors(int id, char *command, char *name)
{
    if (id == -2) // name not defined
    {
        ft_putstr("Minishel: ");
        ft_print(command, " << ", name, ">> not defined\n");
    }
    if (id == -1) // to remove
        printf("cd error no path to home\n");
    if (id == 0)
        ft_print("minishel: cd: ", name, ":  No such file or directory", NULL);
    if (id == 1 && ft_strcmp(command, "echo") != 0)
        ft_print(command, ": unrecognized option '", name,
        "'\n Try 'command --help' for more information.");
    if (id == 3)
        ft_putstr("name is NULL, points to a string of length 0, or contains an '=' character.");
    if (id == 4)
        ft_print("minishel: ", command, ": to many args.\n See --help for more information.", NULL);

    return (0);
}

/*
* set_args set the new argument to be pass to the execve function
*
* @param  av      [the main argument value that contain all vargs]
* @param  newargv [the new argument to be set]
* @param  ac      [the number of argument]
*/

void         set_new_args(char **av, char *newargv[], int ac)
{
    int     i;

    i = -1;
    if (ac != 1)
    {
        while (++i < ac)
            newargv[i] = av[i + 1];
        newargv[ac] = NULL;
    }
    else
    {
        while (++i < ac)
            newargv[i] = NULL;
    }
}
