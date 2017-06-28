#include "minishell.h"
#include "fakelib.c" // to remove
#include "src/settings.c" // to remove
#include "src/builtins.c" // to remove
#include "src/tools.c" // to remove


/*
* Check if the command is an builtin. If then, execute it
*
* @param	{ command } The name of the command that should be check
* @param	{ av }
* @param	{ env }
*
* @return	NULL if no path found. Otherwize return the path
*/

int			is_bultin(char *command, char **av, char *env[])
{
	char	*key_val[2];
	int		r;
	int		overwrite;

	r = 2;
	if (ft_strcmp(command, "env") == 0)
		r = builtin_env(env, av);
	if (r)
	{
		if (ft_strcmp(command, "cd") == 0)
			builtin_cd(av, env);
		else if (ft_strcmp(command, "echo") == 0)
			builtin_echo(av);
		else if (ft_strcmp(command, "setenv") == 0)
		{
			key_val[0] = av[2] ? av[2] : NULL;
			key_val[1] = av[3] ? av[3] : NULL;
			overwrite = av[4] ? ft_atoi(av[4]) : 0;
			builtin_setenv(env, key_val[0], key_val[1], overwrite);
		}
		else if (ft_strcmp(command, "unsetenv") == 0)
			builtin_unsetenv(env, av[2]);
		else
			return (r == 1 ? r : 0);
	}
	return (1);
}

/*
* Get the executable path from env path
*
* @return	NULL if no path found. Otherwise the path is returned
*/

char		*get_exeutable_path(char *command, char *env[])
{
	int		i;
	char	**env_path;
	char	*tmp;

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

char		*get_args(char *env[])
{
	char	*r;
	char	*command;
	char	**args;
	char	buff[100];

	r = NULL;
	while (read(0, buff, 255) > 0)
	{
		if ((args = ft_strsplit(ft_strtrim(buff), ' ')))
		{
			command = args[0];
			args = args[1] ? &args[1] : NULL;
			is_bultin(command, args, env);
			// printf("%s\n\n", args[0]);
		}
	}

	return (r);
}

int			launch(char *command, char **av, char *env[])
{
	char	*command_path;

	if (!is_bultin(command, av, env))
	{
		if ((command_path = get_exeutable_path(av[1], env)))
		{
			execve(command_path, &av[1], env);
		}
	}
	return (1);
}

int			main(int ac, char *av[], char *env[])
{
	char	buf[PATH_MAX + 1];
	pid_t	cpid;

	get_args(env);
	return (0);

	cpid = fork();

	if (ac && av)
	{
		if (cpid == -1)
			printf("Error fork not valid pid\n");
		else if (cpid == 0)
		{
			// launch(av, env);
		}
		else
		{
			printf("$>");
			while (read(0, buf, 255) > 0)
			{
				printf("buff = %s\n", buf);
				execve("/bin/pwd", ft_strsplit(buf, ' '), env);
			}
		}
	}
	return (0);
}
