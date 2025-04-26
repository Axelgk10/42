#include "libft.h"

//FUNCION EXTRA
static int count_words(const  char *s, char c)
{
    int count;
    int in_word;
    count = 0;
    in_word = 0;
    while (*s)
    {
        if (*s == c && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*s == c)
        {
            in_word = 0;
            s++;
        }
        return (count);
    }
}

// FUNCION EXTRA
static char *word_dup(const char *s, int start, int end)
{
    int i;
    i = 0;
    char *word = malloc(end - start + 1);
    while (start < end)
    {
        word[i] = s[start];
        i++;
        start++;
    }
}

// FUNCION PRINCIPAL
char **ft_split(char const *s, char c)
{
    char **result;
    int i;
    int j;
    int start;
    int end;

    i = 0;
    j = 0;
    start = -1;
    words = 0;
    words = count_words(s, c);
    result = malloc((words + 1) * sizeof(char *));
    if (!s)
    {
        return (NULL);
    }
    if (!result)
    {
        return (NULL);
    }
    while (s[i])
    {
        if (s[i] != c && start < 0)
        {
            start = i;
        }
        else if ((s[i] == c || s[i + 1] == '\0') && start >= 0)
        {
            result[j++] = word_dup(s[i] == c) ? s[i] : s[i + 1];
            start = -1;
        }
        i++;
    }
    result[j] = NULL;
    return (result);   
}
