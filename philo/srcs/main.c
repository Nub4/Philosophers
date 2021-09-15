#include "../includes/philo.h"

int	free_exit(t_philo *s, int ret)
{
	int	a;

	a = 0;
	if (ret != ARGERR)
	{
		while (a < s->nr_of_philo)
			pthread_mutex_destroy(&s->forks[a++]);
		free(s->forks);
		free(s->th);
	}
	return (ret);
}

static void	philo_life(t_thread *thrd)
{
	while (!thrd->s->death)
	{
		if (!thrd->s->death)
			to_fork(thrd);
		if (!thrd->s->death)
			to_eat(thrd);
		if (thrd->s->eat_limit && thrd->times_eaten == thrd->s->times_to_eat)
		{
			thrd->s->all_meals++;
			thrd->max_meals = 1;
			break ;
		}
		if (!thrd->s->death)
			to_sleep(thrd);
		if (!thrd->s->death)
			to_think(thrd);
	}
}

void	*philo_birth(void *s)
{
	t_thread	thrd;
	pthread_t	reaper;
	int			ts;

	thrd.s = (t_philo *)s;
	init_birth(&thrd);
	gettimeofday(&thrd.s->start, NULL);
	if (thrd.s->nr_of_philo == 1)
	{
		usleep(thrd.s->time_to_die * 1000);
		ts = timestamp(thrd.s);
		put_msg(ts, thrd.philo_nr, " died\n");
		thrd.s->death = 1;
		return (NULL);
	}
	if (pthread_create(&reaper, NULL, &to_die, &thrd))
	{
		thrd.s->err = THRERR;
		return (NULL);
	}
	philo_life(&thrd);
	pthread_join(reaper, NULL);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	s;
	int		i;

	if (argc != 5 && argc != 6)
		return (ARGERR);
	s.err = ft_init(argc, argv, &s);
	if (s.err)
		return (free_exit(&s, s.err));
	i = -1;
	while (++i < s.nr_of_philo)
	{
		if (pthread_create(&s.th[i], NULL, &philo_birth, &s))
			return (free_exit(&s, THRERR));
		pthread_detach(s.th[i]);
		usleep(100);
		s.philo_nr++;
	}
	while (!s.death && s.all_meals != s.nr_of_philo)
		usleep(1000);
	return (free_exit(&s, 0));
}
