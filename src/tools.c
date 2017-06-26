#include "../minishell.h"

int         special_char_extra(char c)
{
    if (c == 'a')
        putchar('\a');
    else if (c == 'b')
        putchar('\b');
    else if (c == 'f')
        putchar('\f');
    else if (c == 'n')
        putchar('\n');
    else if (c == 'r')
        putchar('\r');
    else if (c == 't')
        putchar('\t');
    else if (c == 'v')
        putchar('\v');
    else if (c == '\\')
        putchar('\\');
    // else if (c == "nnn")
    return (1);
}

int         special_char(char *str)
{
    int     i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '\\' && str[i + 1])
        {
            i++;
            if (ft_indexof("abcfnrtv", str[i]))
                special_char_extra(str[i]);
            else
                ft_putchar(str[i]);
        }
        else
            ft_putchar(str[i]);
    }
    return (1);
}
// putchar("nnn");
