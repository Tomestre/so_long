// lib/libft/ft_strstr.c
#include "libft.h"

static int check_substr(const char *haystack, const char *needle, size_t i)
{
    size_t j;

    j = 0;
    while (needle[j] && haystack[i + j] == needle[j])
        j++;
    if (!needle[j])
        return (1);
    return (0);
}

char *ft_strstr(const char *haystack, const char *needle)
{
    size_t i;

    if (!*needle)
        return ((char *)haystack);
    i = 0;
    while (haystack[i])
    {
        if (haystack[i] == needle[0] && check_substr(haystack, needle, i))
            return ((char *)(haystack + i));
        i++;
    }
    return (NULL);
}
