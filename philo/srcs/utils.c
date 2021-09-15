#include "../includes/philo.h"

int	timestamp(t_philo *s)
{
	int	ts;

	gettimeofday(&s->end, NULL);
	ts = (s->end.tv_sec * 1000 + s->end.tv_usec * 0.001)
		- (s->start.tv_sec * 1000 + s->start.tv_usec * 0.001);
	return (ts);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

long	ft_atol(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (!str)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - 48;
	if (str[i] || res > INT_MAX)
		return (-1);
	return (res);
}
