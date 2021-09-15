#include "../includes/philo.h"

int	ft_init_1(char **argv, int argc, t_philo *s)
{
	s->nr_of_philo = ft_atol(argv[1]);
	s->time_to_die = ft_atol(argv[2]);
	s->time_to_eat = ft_atol(argv[3]);
	s->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		s->times_to_eat = ft_atol(argv[5]);
		s->eat_limit = 1;
	}
	else
	{
		s->times_to_eat = 2;
		s->eat_limit = 0;
	}
	if (s->nr_of_philo < 0 || s->time_to_die < 0
		|| s->time_to_eat < 0 || s->time_to_sleep < 0
		|| s->times_to_eat < 0)
		return (ARGERR);
	s->philo_nr = 1;
	s->death = 0;
	s->end.tv_sec = 0;
	s->end.tv_usec = 0;
	s->all_meals = 0;
	return (0);
}

int	ft_init_2(t_philo *s)
{
	int	i;

	s->forks = malloc(sizeof(pthread_mutex_t) * s->nr_of_philo);
	if (!s->forks)
		return (MALERR);
	s->th = malloc(sizeof(pthread_t) * s->nr_of_philo);
	if (!s->th)
	{
		free(s->forks);
		return (MALERR);
	}
	i = 0;
	while (i < s->nr_of_philo)
		pthread_mutex_init(&s->forks[i++], NULL);
	pthread_mutex_init(&s->msg, NULL);
	return (0);
}

int	ft_init(int argc, char **argv, t_philo *s)
{
	int	i;

	i = 0;
	while (++i < 6)
		if (ft_strlen(argv[i]) > 18)
			return (ARGERR);
	if (ft_init_1(argv, argc, s))
		return (ARGERR);
	if (ft_init_2(s))
		return (MALERR);
	return (0);
}

void	init_birth(t_thread *thrd)
{
	thrd->philo_nr = thrd->s->philo_nr;
	thrd->last_eat = timestamp(thrd->s);
	thrd->times_eaten = 0;
	thrd->max_meals = 0;
	thrd->dead = 0;
}
