# include <stdlib.h> //to remove

int		ft_indexof(char *s, char c)
{
	int	i;

	if (!s || !c)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_strcmp(char *s1, char *s2)
{
	int				i;
	unsigned char	r1;
	unsigned char	r2;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		r1 = s1[i];
		r2 = s2[i];
		if (r1 != r2)
			return (r1 - r2);
		if (r1 == '\0')
			return (-r2);
		if (r2 == '\0')
			return (r1);
		i++;
	}
	return (0);
}

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*r;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	r = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r)
		return (NULL);
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		r[i] = s2[j];
		i++;
		j++;
	}
	r[i] = '\0';
	return (r);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	while (s[i])
		ft_putchar(s[i++]);
}

int			ft_print(char *s1, char *s2, char *s3, char *s4)
{
	char	*tmp;

	tmp = NULL;
	if (s1 && s2)
		tmp = ft_strjoin(s1, s2);
	if (s3)
		tmp = ft_strjoin(tmp, s3);
	if (s4)
		tmp = ft_strjoin(tmp, s4);
	if (tmp)
	{
		ft_putstr(tmp);
		ft_putchar('\n');
		free(tmp);
	}
	return (1);
}

int					ft_memcmp(const void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;

	i = ft_strlen(s2);
	if (*s2 == '\0')
		return ((char *)s1);
	while (*s1)
	{
		if (!ft_memcmp(s1++, s2, i))
			return ((char *)(s1 - 1));
	}
	return (NULL);
}


void		*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}


void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}


void		*ft_memalloc(size_t size)
{
	void	*r;

	r = malloc(size);
	if (r == NULL)
		return (NULL);
	ft_memset(r, 0, size);
	return (r);
}

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*r;

	i = 0;
	if (!s)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (r == NULL)
		return (r);
	while (s[start] && len > 0)
	{
		r[i] = s[start];
		i++;
		len--;
		start++;
	}
	r[i] = '\0';
	return (r);
}

static size_t	ft_wordcount(char const *s, char c)
{
	int		in_word;
	size_t	n_word;
	size_t	i;

	in_word = 0;
	n_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!in_word)
				n_word++;
			in_word = 1;
		}
		else
			in_word = 0;
		i++;
	}
	return (n_word);
}

static char		*ft_wordpicker(char *str, char **ptr, char c)
{
	size_t	word_begin;
	size_t	word_end;
	char	*word;

	word_begin = 0;
	word_end = 0;
	while (str[word_begin] == c)
		word_begin++;
	word_end = word_begin;
	while (str[word_end] && str[word_end] != c)
		word_end++;
	word = ft_strsub(str, word_begin, word_end - word_begin);
	*ptr = word;
	return (str + word_end);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	n_word;
	char	**ptr;
	char	*str;
	size_t	i;

	ptr = NULL;
	i = 0;
	if (s)
	{
		str = (char*)s;
		n_word = ft_wordcount(s, c);
		ptr = (char**)ft_memalloc((n_word + 1) * sizeof(char*));
		if (!ptr)
			return (NULL);
		while (i < n_word)
			str = ft_wordpicker(str, ptr + i++, c);
		ptr[n_word] = 0;
	}
	return (ptr);
}

int			ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((*s1 || *s2) && i < n)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}


char		*ft_strdup(const char *str)
{
	int		i;
	char	*r;

	i = ft_strlen(str);
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (!r)
		return (NULL);
	r[i] = '\0';
	while (i-- > 0)
		r[i] = str[i];
	return (r);
}


void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char const *s, int fd)
{
	int i;

	i = 0;
	while (s[i])
		ft_putchar_fd(s[i++], fd);
}

void	ft_putendl_fd(char const *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putendl(char const *s)
{
	ft_putendl_fd(s, 1);
}

int	ft_isspace(int c)
{
	return ((9 <= c && c <= 13) || c == 32);
}

int		ft_isdigit(int c)
{
	return ((c > 47 && c < 58) ? 1 : 0);
}

int			ft_atoi(const char *str)
{
	int n;
	int isneg;

	isneg = 0;
	n = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		isneg = 1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str))
	{
		n = n * 10 + (*str++ - '0');
	}
	return (isneg ? (-n) : (n));
}


char		*ft_strtrim(char const *s)
{
	int		j;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	if (*s == '\0')
		return (ft_strdup(""));
	j = ft_strlen(s);
	if (j == 0)
		return (ft_strdup(""));
	while (s[j - 1] == ' ' || s[j - 1] == '\n' || s[j - 1] == '\t')
		j--;
	return (ft_strsub(s, 0, j));
}

char	*ft_strcpy(char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

void		ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	*alst = new;
	new->next = tmp;
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = (void *)malloc(content_size);
		if (!new->content)
			return (NULL);
		new->content = ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}

void		*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s1)[i] = ((char *)s2)[i];
		i++;
	}
	return (s1);
}

void	ft_lstpush(t_list *list, t_list *new)
{
	while (list->next)
		list = list->next;
	list->next = new;
}

void		ft_lstdel(t_list **alts, void (*del)(void *, size_t))
{
	t_list	*next;

	while (*alts)
	{
		next = (*alts)->next;
		ft_lstdelone(alts, del);
		*alts = next;
	}
}

