#include "../minishell.h"

/*
 * Move into a specific folder.
 * If the path == "--" or is not specify the path will be the home path.
 * Otherwise it will try to move into it.
 *
 * @param  av  [an array of argument passed to the program]
 * @param  env [an array of key pair vaule]
 * @return     [if sucess return 1 else print error and return 0]
 */

int			builtin_cd(char **av, char *env[])
{
	int		error_id;
	char	*path;

	error_id = -1;
	if (av[2] && ft_strcmp(av[2], "--") != 0)
	{
		if (ft_strcmp(av[2], "-") == 0)
		{
			if (swap_env(env, "OLDPWD=", "_="))
				error_id = 2;
			path = ft_strsplit(ft_getenv(env, "_="), '=')[1];
		}
		else
			path = av[2];
	}
	else
	{
		path = ft_strsplit(ft_getenv(env, "HOME="), '=')[1];
		builtin_setenv(env, "_=", path, 1);
	}
	if (!path)
		return (set_errors(error_id, NULL, NULL));
	if (chdir(path) < 0 && (error_id = 0))
		set_errors(error_id, NULL, path);
	return (1);
}

int         builtin_echo(char **av)
{
	int		i;
	char	*flags[2];

	if (!av || !av[0])
		return (1);
	flags[0] = ft_strdup(" n e E --help --version ");
	flags[1] = get_glags(flags[0], av, "echo");
	printf("ok %s %d \n", flags[1], 0);
	i = ft_strlen(ft_strtrim(flags[1])) ? get_args_limit(av) : 1;
	while (av[++i])
	{
		if (ft_indexof(av[i], '\\') > -1)
			special_char(av[i]);
		else
			ft_putstr(av[i]);
		av[i + 1] ? ft_putchar(' ') : ' ';
	}
	if (ft_strlen(flags[1]) == 0 || ft_strstr(flags[1], " n ") == 0)
		ft_putchar('\n');
	free(flags[0]);
	free(flags[1]);
	return (1);
}

int         builtin_exit(int status, int pid)
{
	if (!status || !pid)
		return (0);
	return (1);
}

/*
 * Execute any process with the set environment except builtins.
 * the only builtin that's allow is env it self
 *
 * @param	env [description]
 * @return	[1 if another command has to be execute otherwise return 0]
 */

int         builtin_env(char *env[], char **av)
{
	char	*flags[2];

	flags[0] = ft_strdup(" i 0 u --ignore-environment --null --unset --help --version ");
	flags[1] = get_glags(flags[0], av, "env");
	if (ft_strlen(ft_strtrim(flags[1])) == 0)
		return (0);
	if (ft_strstr(flags[1], " --help "))
	{
		ft_putendl("Usage: env [OPTION]... [-] [NAME=VALUE]... [COMMAND [ARG]...]");
		ft_putendl("Set each NAME to VALUE in the env and run COMMAND.\n");
		ft_putendl("-i, --ignore-environment\nstart with empty environment");
		ft_putendl("-0, --null\nend each output line with 0 not newline");
		ft_putendl("-u, --unset=NAME\nremove variable from the environment.");
	}
	else if (ft_strstr(flags[1], " --version "))
		ft_putstr("\nenv (GNU coreutils) 8.21\nCopyright © 2017 kacoulib.\n\n");
	else if (ft_strstr(flags[1], " --ignore-environment ") ||
		ft_strstr(flags[1], " i "))
		env[0] = NULL;
	else
		builtin_env_extra(env, av, flags[1]);
	return (0);
}

int         builtin_env_extra(char *env[], char **av, char *flags)
{
	int		i;

	i = -1;

	// if (ft_strstr(flags, " --help "))
	printf("____%s, %s, %s\n", flags, av[0], env[0]);

	// while (env[++i])
	// {
	//     if (ft_strcmp(env[i], "") != 0)
	//     {
	//
	//         if (ft_strstr(flags, " 0 ") || ft_strstr(flags, " --null "))
	//             ft_putstr(env[i]);
	//         else
	//             ft_putendl(env[i]);
	//     }
	// }
	free(flags);
	return (1);
}

int         builtin_env_extra_unset(char *env[], char **av, char *flags)
{
	int		i;

	i = -1;
	while (av[++i] && av[i][0] == '-' && av[i][1])
	{
		if (ft_strstr(av[i], "--ignore-environment=") || ft_strstr(av[i], "-u="))
		{
			if (flags || env) // to remove
				;
		}
	}
	return (1);
}

/*
 * [builtin_setenv description]
 *
 * @param  env [an array of key pair vaule]
 * @param  key      [the key to set]
 * @param  value     [the value to set]
 * @param  overwrite [== 0 ? and the value is set then the valus will beunchange
 *  else the value is overwrite]
 * @return           [if the key dont exist the create else overwrite it if the
 * overwrite is != 0]
 */

int         builtin_setenv(char *env[], char *key, char *value,
	int overwrite)
{
	int		i;

	i = -1;
	if (key && ft_strcmp(key, "") != 0)
	{
		while (env[++i])
		{
			if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
			{
				if (value && overwrite)
				{
					env[i] = ft_strjoin(key, "=");
					env[i] = ft_strjoin(env[i], value);
				}
				return (1);
			}
		}
	}
	key = (key) ? key : "";
	env[i] = ft_strjoin(key, "=");
	if (value)
		env[i] = ft_strjoin(env[i], value);
	return (1);
}

/*
 * Deletes the variable name and value from the environment.
 *
 * @param  name [description]
 * @return      [return 1 on sucess an 0 on error]
 *
 * @@todo   look for empty env
 */

int         builtin_unsetenv(char *env[], char *name)
{
	int		i;
	int		j;

	i = -1;
	if (!name)
		return (set_errors(-2, "setenv", "NAME"));
	while (env[++i])
	{
		j = ft_strlen(name);
		if (ft_strncmp(env[i], name, j) == 0)
		{
			if (env[i][j] == '=')
			{
				while (env[++i])
					if (env[i - 1])
						env[i - 1] = env[i];
				if (env[--i])
					env[i] = NULL;
				return (1);
			}
		}
	}
	return (0);
}
