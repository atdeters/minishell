#include "lexing.h"
#include <stdio.h>
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	size_t	s_len;
	size_t	i;
	char	*ptr;

	if (!s)
		return (NULL);
	sub_len = 0;
	i = 0;
	s_len = ft_strlen(s);
	while (s[sub_len] && sub_len < len && (sub_len + start) < s_len)
		sub_len++;
	ptr = (char *)malloc((sub_len + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	ptr[sub_len] = '\0';
	while (i < sub_len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	int		i;
	int		j;
	char	*ptr;

	if (!s1)
		return (NULL);
	if (!s2)
		return (NULL);
	i = -1;
	j = -1;
	size = ft_strlen ((char *)s1) + ft_strlen ((char *)s2) + 1;
	ptr = (char *)malloc (size * sizeof(char));
	if (ptr == 0)
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}

int	lexing(char *input, t_token **list)
{
	t_token *current;
	int		i;
	int		start;
	char	*word;

	i = 0;
	while (input[i])
	{
		while (input[i] && ft_is_space(input[i]))
			i++;
		if (!input[i])
			return (0);
		if (input[i] == '$')
			current = create_token(DOLAR_SIGN, NULL);
		else if (input[i] == '|')
			current = create_token(PIPE, NULL);
		else if (input[i] == '<')
			current = create_token(REDIR_IN, NULL);
		else if (input[i] == '>')
			current = create_token(REDIR_OUT, NULL);
		else if (input[i] == '\'')
		{
			start = ++i;
			while (input[i] && input[i] != '\'')
				i++;
			if (!input[i])
				return (0); //should handle errors here
			word = ft_substr(input, start, i - start);
			if (!word)
				return (0); //shoud check and free lst in case of error
			current = create_token(WORD, word);
			i++;
		}
		else if (input[i] == '"')
		{
			start = ++i;
			while (input[i] && input[i] != '\"')
				i++;
			if (!input[i])
				return (0);
			word = ft_substr(input, start, i - start);
			if (!word)
				return (0); 
			current = create_token(WORD, word);
			if (!current)
				return (0); 
			i++;
			if (input[i] == '\"')
			{
				start = ++i;
				while (input[i] && input[i] != '\"')
					i++;
				if (!input[i])
					return (0);
				word = ft_substr(input, start, i - start);
				if (!word)
					return (0);
				current->value = ft_strjoin(current->value, word);
				if (!current->value)
					return (0);
				i++;
			}
		}
		else
		{
			start = i;
			while (input[i] && !ft_is_space(input[i]) && input[i] != '\'' && input[i] != '"'
			 && input[i] != '$' && input[i] != '|' && input[i] != '<' && input[i] != '>')
				i++;
			word = ft_substr(input, start, i - start);
			if (!word)
				return (0);
			current = create_token(WORD, word);
		}
		if (!current)
			return (0);
		ft_token_lstadd_back(list, current);
		if (input[i])
			i++;
	}
	return (1);
}

int main (void)
{
	t_token *list;
	list = NULL;
	char *input = "ls -l | grep 'test' > file.txt";
	// char *input = "\"ec\"\"ho\" \"hello world\"";
	if (!lexing(input, &list))
	{
		ft_token_lstclear(&list);
		printf("Error\n");
		return (1);
	}
	while (list)
	{
		printf("type: %d, value: %s\n", list->type, list->value);
		list = list->next;
	}
	return (0);
}