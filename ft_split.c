#include "libft.h"
// FUNCION EXTRA
static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}
// FUNCION EXTRA
static char	*substr(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(end - start + 1);
	i = 0;
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}
// FUNCION EXTRA
static void	free_all(char **res, int i)
{
	while (--i)
		free (res[i]);
	free (res);
}
// FUNCION PRINCUPAL
static int	fill_split(char **res, const char *s, char c)
{
	int		i;
	int		start;
	int		end;
	int		word_i;

	i = 0;
	word_i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > start)
		{
			res[word_i] = substr(s, start, end);
			if (!res[word_i])
				return (free_all(res, word_i), 0);
			word_i++;
		}
	}
	res[word_i] = NULL;
	return (1);
}
// FUNCION EXTRA
char	**ft_split(char const *s, char c)
{
	char	**res;

	res = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	if (!fill_split(res, s, c))
		return (NULL);
	return (res);
}

int main()
{
    char str[] = "Hola, soy un ejemplo de cadena!";
    char delimiter = ' ';  // Separador en este caso es el espacio
    char **result;
    int i = 0;

    result = ft_split(str, delimiter);
    if (!result)
    {
        printf("Error al dividir la cadena\n");
        return 1;
    }

    // Imprimir las subcadenas resultantes
    while (result[i])
    {
        printf("Subcadena %d: %s\n", i + 1, result[i]);
        i++;
    }

    // Liberar la memoria asignada
    i = 0;
    while (result[i])
    {
        free(result[i]);
        i++;
    }
    free(result);

    return 0;
}
