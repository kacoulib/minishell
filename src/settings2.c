#include "../minishell.h"

t_list		*copy_env(char *env[])
{
	int		i;
	t_list	*tmp;
	t_list	*r;

	if (!env[0])
		return (ft_lstnew(NULL, sizeof(t_list) + 1));
	r = ft_lstnew(env[0], ft_strlen(env[0]) + 1);

	i = 0;
	while (env[++i])
	{
		tmp = ft_lstnew(env[i], ft_strlen(env[i]) + 1);
		ft_lstadd(&r, tmp);
	}
	return (r);
}

int			list_length(t_list *list)
{
	int		i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char		**convert_list_to_array(t_list *list)
{
	int		i;
	char	**r;

	i = 0;
	r = (char **)malloc(sizeof(char) * (list_length(list) + 1));
	while (list)
	{
		r[i] = list->content;
		list = list->next;
		i++;
	}
	return (r);
}

void	del(void *content, size_t len)
{
	if (content)
		free(content);
	if (len)
		;
}