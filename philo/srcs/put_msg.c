#include "../includes/philo.h"

char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

int	ft_words(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = n * (-1);
		count++;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*word;
	int		i;
	int		count;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_words(n);
	word = malloc(sizeof(char) * count + 1);
	if (!word)
		return (NULL);
	if (n < 0)
	{
		word[0] = '-';
		n = n * -1;
	}
	i = count;
	while (n > 0)
	{
		word[--i] = n % 10 + '0';
		n = n / 10;
	}
	word[count] = '\0';
	return (word);
}

void	put_msg(int i0, int i1, char *s)
{
	char	*s0;
	char	*s1;

	s0 = ft_itoa(i0);
	s1 = ft_itoa(i1);
	write(1, s0, ft_strlen(s0));
	write(1, " ", 1);
	write(1, s1, ft_strlen(s1));
	write(1, s, ft_strlen(s));
}
