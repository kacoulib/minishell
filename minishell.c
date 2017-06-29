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
			key_val[0] = av[0] ? av[0] : NULL;
			key_val[1] = av[1] ? av[1] : NULL;
			overwrite = av[2] ? ft_atoi(av[4]) : 0;
			builtin_setenv(env, key_val[0], key_val[1], overwrite);
		}
		else if (ft_strcmp(command, "unsetenv") == 0)
			builtin_unsetenv(env, av[0]);
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
	else if (access(command, F_OK & X_OK) != -1)
		return (command);
	else if (command[0] == '.' && command[1] == '/' &&
		(ft_print("misihell: no such file or directory: ", command, NULL, NULL)))
		return (NULL);
	*env_path = ft_strsub(*env_path, 5, ft_strlen(*env_path));
	env_path = ft_strsplit(*env_path, ':');
	i = -1;
	while (env_path[++i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		tmp = ft_strjoin(tmp, command);
		if (access(tmp, F_OK & X_OK) != -1)
			return (tmp);
	}
	return (NULL);
}

int			launch(char *command, char **av, char *env[])
{
	pid_t	cpid;
	char	*command_path;
	char	**builtin_args;

	if (ft_strcmp(command, "exit") == 0)
		builtin_exit(1);
	cpid = fork();
	if (cpid == -1)
		printf("Error fork not valid pid\n");

	else if (cpid == 0)
	{
		builtin_args = av[1] ? &av[1] : NULL;
		if (!is_bultin(command, &av[1], env))
		{
			if ((command_path = get_exeutable_path(command, env)))
				execve(command_path, av, env);
			else
				ft_print("misihell: no such file or directory: ",
					command, NULL, NULL);
		}
	}
	else
		wait(&cpid);
	return (1);
}

int			main(int ac, char *av[], char *env[])
{
	int		i;
	char	*tmp;
	char	**args;
	char	buff[100];

	ft_putstr("$> ");
	while (read(0, buff, 255) > 0)
	{
		if ((i = ft_indexof(buff, '\n')) > -1)
		{
			tmp = ft_strsub(buff, 0, i);
			args = ft_strsplit(tmp, ' ');
			tmp = args[0] ? args[0] : ft_strtrim(buff);
			if (launch(tmp, args, env) && free_arr(args))
				ft_putstr("\n$> ");
		}
	}
	return (ac && av);
}
